#include <pebble.h>
#include "linestatus.h"

MenuLayer *status_menu_create(GRect bounds, Window *window, LineStatus *line_status);
void status_menu_destroy(void);
