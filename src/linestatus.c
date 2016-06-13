#include <pebble.h>
#include "linestatus.h"

static LineStatus *status;
static int last_index = 0;

LineStatus *initLineStatus(int numlines) {
  status = (LineStatus*)calloc(numlines, sizeof(LineStatus));
  if (status == NULL)
    APP_LOG(APP_LOG_LEVEL_ERROR, "calloc of LineStatus array failed");

  return status;
}

void addLineStatus(const char *line_name, const char *line_status) {
  status[last_index].line_name = (char*)malloc(strlen(line_name));
  status[last_index].status = (char*)malloc(strlen(line_status));
  if (status[last_index].line_name == NULL || status[last_index].status == NULL) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "malloc for line status failed");
  } else {
    strncpy(status[last_index].line_name, line_name, strlen(line_name));
    strncpy(status[last_index].status, line_status, strlen(line_status));
    last_index++;
  }
}

void deleteLineStatus(void) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "deleteLinestatus in");

  for (last_index--; last_index >= 0; last_index--) {
    free(status[last_index].line_name);
    free(status[last_index].status);
  }

  free(status);
}

int getNumLines(void) {
  // last_index is incremented post add
  APP_LOG(APP_LOG_LEVEL_DEBUG, "getNumLines %d", last_index);
  return last_index;
}

LineStatus *getLineStatus(void) {
  return status;
}
