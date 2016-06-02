#include <pebble.h>
#include "linestatus.h"

static LineStatus status[];

LineStatus *initLineStatus(int numlines) {
  status = calloc(sizeof(LineStatus), numlines);
  if (status == NULL)
    APP_LOG(APP_LOG_LEVEL_ERROR, "calloc of LineStatus array failed");

  return status;
}

void addLineStatus(const char *line_name, int status_code) {
  
}

void deleteLineStatus(void) {
  LineStatus *cur, *next;

  APP_LOG(APP_LOG_LEVEL_DEBUG, "deleteLinestatus in");

  cur = first;
  while (cur != NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "deletelinestatus freeing line %s", cur->line_name);
    free(cur->line_name);
    next = cur->next;
    free(cur);
    cur = next;
  }
}
