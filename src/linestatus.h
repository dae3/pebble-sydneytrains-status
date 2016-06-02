#pragma once
#include <pebble.h>

enum LineStatusCode {
  SC_GOODSERVICE = 0,
  SC_DELAYS,
  SC_MAJORDELAYS,
  SC_TRACKWORK
};

typedef struct LineStatus {
  char *line_name;
  int status;
  struct LineStatus *next;
} LineStatus;

LineStatus *initLineStatus(int numlines);
void addLineStatus(const char *line_name, int status_code);
void deleteLineStatus(void);
