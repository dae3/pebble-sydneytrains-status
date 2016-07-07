#include "routes.h"
#include <pebble.h>

static int num_routes = 0;
static ResHandle route_txt;
static Route **all_routes;

void routes_load_routes() {
  uint8_t *buf;
  Route *r;
  size_t s;

  route_txt = resource_get_handle(RESOURCE_ID_ROUTES_TXT);
  s = resource_size(route_txt)
  buf = (uint8_t*)malloc(s);

  if (s == resource_load(route_txt, buf, s)) {
    
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Didn't load entire routes.txt");
  }
}
