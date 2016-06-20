#include <pebble.h>
#include "linestatus.h"

const char * key_as_string[] = {
  "type",
  "linename",
  "linestatus",
  "status",
  "numlines"
};

void debug_dump_ls(LineStatus *ls) {
  int j = getNumLines();
  for (int i = 0; i < j; i++) {
    APP_LOG(
	    APP_LOG_LEVEL_DEBUG,
	    "debug_dump_ls '%s' '%s'",
	    ls[i].line_name,
	    ls[i].status
	    );
  }
}

void debug_dump_dict(DictionaryIterator *iter) {
   Tuple *tuple;
    
  tuple = dict_read_first(iter);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple key %ld %s", tuple->key, key_as_string[tuple->key]);

  while (tuple != NULL) {
    switch (tuple->type) {
    case TUPLE_BYTE_ARRAY:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple bytes");
      break;
    case TUPLE_CSTRING:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple string %s", tuple->value->cstring);
      break;
    case TUPLE_INT:
      switch (tuple->length) {
      case 1:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple int length %d val %d", tuple->length, tuple->value->int8);
	break;
      case 2:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple int length %d val %d", tuple->length, tuple->value->int16);
	break;
      case 3:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple int length %d val %ld", tuple->length, tuple->value->int32);
	break;
      }
    case TUPLE_UINT:
      switch (tuple->length) {
      case 1:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple uint length %d val %d", tuple->length, tuple->value->uint8);
	break;
      case 2:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple uint length %d val %d", tuple->length, tuple->value->uint16);
	break;
      case 3:
	APP_LOG(APP_LOG_LEVEL_DEBUG, "tuple uint length %d val %ld", tuple->length, tuple->value->uint32);
	break;
      }
    }
    tuple = dict_read_next(iter);
    }
}
