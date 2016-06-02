#include <pebble.h>
#include "appmsg.h"

void appmsg_init(void) {
  uint32_t dict_size_in, dict_size_out;

  Tuplet dummy_tuplets_out[] = {
    TupletInteger(APPMSGKEY_MSGTYPE, APPMSGTYPE_LINESTATUS),
    TupletCString(APPMSGKEY_LINENAME, "dummy line"),
    TupletInteger(APPMSGTYPE_LINESTATUS, LINESTATUS_UNKNOWN)
  };

  Tuplet dummy_tuplets_in[] = {
    TupletInteger(APPMSGKEY_MSGTYPE, APPMSGTYPE_STATUS),
    TupletCString(APPMSGKEY_STATUS, "dummy status")
  };

  dict_size_in = dict_calc_buffer_size_from_tuplets(dummy_tuplets_in, 3);
  dict_size_out = dict_calc_buffer_size_from_tuplets(dummy_tuplets_out, 2);

  if (app_message_open(dict_size_in, dict_size_out) == APP_MSG_OK) {

  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "app_message_open failed");
  }

}

void appmsg_deinit(void) {

}
