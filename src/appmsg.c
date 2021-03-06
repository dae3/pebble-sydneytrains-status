#include <pebble.h>
#include "appmsg.h"
#include "linestatus.h"
#include "statusmenu.h"

static bool pkjs_ready = false;
extern void debug_dump_dict(DictionaryIterator *iter);

void appmsg_inbox_received(DictionaryIterator *iter, void *context) {
  Tuple *msgtype, *line_name, *line_status, *num_lines;

  msgtype = dict_find(iter, APPMSGKEY_MSGTYPE);
  if (msgtype == NULL) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "appmsg with no message type");
  } else {
    switch(msgtype->value->int8) {
    case APPMSGTYPE_REFRESH:
      num_lines = dict_find(iter, APPMSGKEY_NUMLINES);
      if (num_lines == NULL) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "got refresh appmsg without number of lines");
      } else {
	deleteLineStatus();
	initLineStatus(num_lines->value->int8);
      }
      break;
    case APPMSGTYPE_STATUS:

      break;
    case APPMSGTYPE_LINESTATUS:
      line_name = dict_find(iter, APPMSGKEY_LINENAME);
      line_status = dict_find(iter, APPMSGKEY_LINESTATUS);
      if (line_name == NULL || line_status == NULL) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "got linestatus message without line name or line status");
      } else {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "linestatus appmsg received %s %s", line_name->value->cstring, line_status->value->cstring);
	addLineStatus(line_name->value->cstring, line_status->value->cstring);
      }
      status_menu_refresh();
      break;
    case APPMSGTYPE_PKJSREADY:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "ready appmsg received");
      pkjs_ready = true;
      break;
      
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "appmsg with unknown message type %d", msgtype->value->int8);
      break;
    }
  }
}

void appmsg_inbox_dropped(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "appmsg inbox dropped: %d", reason);
}

void appmsg_outbox_sent(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "appmsg outbox sent");
  debug_dump_dict(iter);
}

void appmsg_outbox_failed(DictionaryIterator *iter, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "appmsg outbox failed: %d", reason);
}

void retrytimer(void *data) {
  appmsg_refreshstatus();
}

void appmsg_refreshstatus(void) {
  DictionaryIterator *dict;

  if (pkjs_ready) { 
    if (app_message_outbox_begin(&dict) == APP_MSG_OK) {
      dict_write_int8(dict, APPMSGKEY_MSGTYPE, APPMSGTYPE_REFRESH);
      //dict_write_end(dict);
      if (app_message_outbox_send() != APP_MSG_OK) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "Error sending appmsg");
      } else {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "refresh appmsg sent");
      }
    } else {
      APP_LOG(APP_LOG_LEVEL_ERROR, "Couldn't open appmsg outbox.");
    }
  } else {
    // not ready, wait and retry
    app_timer_register(500, retrytimer, NULL);
  }
}

void appmsg_init(void) {
  uint32_t dict_size_in, dict_size_out;

  Tuplet dummy_tuplets_out[] = {
    TupletInteger(APPMSGKEY_MSGTYPE, APPMSGTYPE_LINESTATUS),
    TupletCString(APPMSGKEY_LINENAME, "dummy line"),
    TupletCString(APPMSGTYPE_LINESTATUS, "dummy line status")
  };

  Tuplet dummy_tuplets_in[] = {
    TupletInteger(APPMSGKEY_MSGTYPE, APPMSGTYPE_STATUS),
    TupletCString(APPMSGKEY_STATUS, "dummy status")
  };

  dict_size_in = dict_calc_buffer_size_from_tuplets(dummy_tuplets_in, 3);
  dict_size_out = dict_calc_buffer_size_from_tuplets(dummy_tuplets_out, 2);

  app_message_register_inbox_received(appmsg_inbox_received);
  app_message_register_inbox_dropped(appmsg_inbox_dropped);
  app_message_register_outbox_sent(appmsg_outbox_sent);
  app_message_register_outbox_failed(appmsg_outbox_failed);

  if (app_message_open(dict_size_in, dict_size_out) == APP_MSG_OK) {

  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "app_message_open failed");
  }

}

void appmsg_deinit(void) {

}
