#include <pebble.h>
#include "linestatus.h"

MenuLayer *status_menu_create(GRect bounds, Window *window);
void status_menu_destroy(void);
void status_menu_refresh(void);
