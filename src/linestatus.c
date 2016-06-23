#include <pebble.h>
#include "linestatus.h"

static LineStatus *status;
static int last_index;

GColor lookup_color_for_status(const char *status) {
  GColor ret;
  ret.argb = UNKNOWN_STATUS_COLOR;

  for (int i = 0; i < NUM_COLOR_TABLE_ENTRIES; i++) {
    if (strcmp(status, color_table[i].status) == 0) {
      ret.argb = color_table[i].color;
      break;
    }
  }

  return(ret);
}

LineStatus *initLineStatus(int numlines) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "initLineStatus %d", numlines);
  status = (LineStatus*)calloc(numlines, sizeof(LineStatus));
  last_index = 0;
  if (status == NULL)
    APP_LOG(APP_LOG_LEVEL_ERROR, "calloc of LineStatus array failed");

  return status;
}

void addLineStatus(const char *line_name, const char *line_status) {
 
 status[last_index].line_name = (char*)malloc(strlen(line_name)+1);
 status[last_index].status = (char*)malloc(strlen(line_status)+1);
 
 if (status[last_index].line_name == NULL || status[last_index].status == NULL) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "malloc for line status failed");
  } else {
    strcpy(status[last_index].line_name, line_name);
    strcpy(status[last_index].status, line_status);
    status[last_index].status_color = lookup_color_for_status(line_status);
    last_index++;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "addLineStatus %s %s", line_name, line_status);
  }
}

void deleteLineStatus(void) {
  int i;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "deleteLinestatus in");

  for (i = 0; i < last_index; i++) {
    free(status[i].line_name);
    free(status[i].status);
  }

  if (status != NULL)
    free(status);
}

int getNumLines(void) {
  // last_index is incremented post add
  return last_index;
}

LineStatus *getLineStatus(void) {
  return status;
}
