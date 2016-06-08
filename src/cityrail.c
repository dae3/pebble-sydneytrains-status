#include <pebble.h>
#include "appmsg.h"
#include "statusmenu.h"
#include "linestatus.h"

static Window *window;
static MenuLayer *statusmenu;
static LineStatus *line_status;

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  statusmenu = status_menu_create(bounds, window, line_status);
}


static void window_unload(Window *window) {
  status_menu_destroy();
}

static void init(void) {

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
      .load = window_load,
	.unload = window_unload,
	});
  window_stack_push(window, true);

  appmsg_init();


}

static void deinit(void) {
  appmsg_deinit();
  deleteLineStatus();
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
