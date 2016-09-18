#include "routes.h"
#include "csv.h"
#include <pebble.h>

static int num_routes = 0;
static ResHandle route_txt;
static struct Route *all_routes;

static int csv_parse_fieldnum;
static int csv_parse_recnum;

void csv_cb1(void *p1, size_t s, void *p2) {
  switch (csv_parse_fieldnum++) {
  case CSV_FIELDNUM_ROUTEID:
    strncpy(all_routes[csv_parse_recnum].route_id, p1, MAX_ROUTEID);
    break;

  case CSV_FIELDNUM_ROUTE_SHORT_NAME:
    strncpy(all_routes[csv_parse_recnum].route_shortname, p1, MAX_ROUTESHORTNAME);
    break;

  case CSV_FIELDNUM_ROUTE_COLOUR:
    strncpy(all_routes[csv_parse_recnum].route_colour, p1, MAX_COLOUR);
    break;
  }
}

void csv_cb2(int i, void *p) {
  csv_parse_fieldnum = 0;
  csv_parse_recnum++;
}

void csv_count_cb(int i, void *p) { num_routes++; }


void routes_load_routes() {
  uint8_t *buf;
  size_t s,t;
  struct csv_parser parser;

  route_txt = resource_get_handle(RESOURCE_ID_ROUTES_TXT);
  s = resource_size(route_txt);
  buf = (uint8_t*)malloc(s);

  if (s == resource_load(route_txt, buf, s)) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "loaded routes.txt %d", s);
    
    if (csv_init(&parser, CSV_APPEND_NULL) != 0) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "csv_init() failed");
    } else {
      /* count records */
      csv_parse_recnum = 0; csv_parse_fieldnum = 0;
      t = csv_parse(&parser, buf, s, NULL, csv_count_cb, NULL);
      if (t < s) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "%s", csv_strerror(csv_error(&parser)));
      } else {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "parsed %d bytes found %d routes", t, num_routes);
	csv_fini(&parser, csv_cb1, csv_cb2, NULL);

	all_routes = calloc(num_routes, sizeof(struct Route));
	t = csv_parse(&parser, buf, s, csv_cb1, csv_cb2, NULL);
	if (t < s) {

	} else {
	  for (int i = 0; i < num_routes; i++) {
	    APP_LOG(APP_LOG_LEVEL_DEBUG, "%s %s %s", all_routes[i].route_id, all_routes[i].route_shortname, all_routes[i].route_colour);
	  }
	  csv_fini(&parser, csv_cb1, csv_cb2, NULL);
	}
	
      }
    }

  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Didn't load entire routes.txt");
  }
}

void routes_destroy() {
  if (all_routes != NULL) {
    free(all_routes);
  }
}
