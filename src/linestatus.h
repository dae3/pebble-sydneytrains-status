#pragma once
#include <pebble.h>

typedef struct LineStatus {
  char *line_name;
  char *status;
} LineStatus;

LineStatus *initLineStatus(int numlines);
void addLineStatus(const char *line_name, const char *line_status);
void deleteLineStatus(void);
int getNumLines(void);
LineStatus *getLineStatus(void);
