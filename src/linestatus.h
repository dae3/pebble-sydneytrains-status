#pragma once
#include <pebble.h>

typedef struct LineStatus {
  char *line_name;
  char *status;
  GColor status_color;
} LineStatus;

LineStatus *initLineStatus(int numlines);
void addLineStatus(const char *line_name, const char *line_status);
void deleteLineStatus(void);
int getNumLines(void);
LineStatus *getLineStatus(void);

/* TODO remove typedef and refactor dependencies */
typedef struct status_color_table {
  const char *status;
  const uint8_t color;
} status_color_table;

static status_color_table color_table[] = {
  { "Good service", GColorGreenARGB8 },
  { "Delays", GColorRedARGB8 },
  { "Major delays", GColorRedARGB8 },
  { "Trackwork", GColorYellowARGB8 }
};

static const uint8_t UNKNOWN_STATUS_COLOR = GColorYellowARGB8;
static const int NUM_COLOR_TABLE_ENTRIES = 3;
