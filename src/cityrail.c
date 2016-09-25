#include <pebble.h>
#include "appmsg.h"
#include "linestatus.h"
#include "statusscreen.h"
#include "routes.h"

static Window *window;
static LineStatus *line_status;

static void init(void) {
  appmsg_init();

  window = statusscreen_create();
  window_stack_push(window, true);

  routes_load_routes();
}

static void deinit(void) {
  appmsg_deinit();
  deleteLineStatus();
  window_destroy(window);
  routes_deinit();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
