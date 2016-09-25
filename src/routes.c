#include "routes.h"
#include "csv.h"
#include <pebble.h>

static int num_routes = 0;
static ResHandle route_txt;
static struct Route *all_routes;

struct parse_counts {
  int fieldnum;
  int recnum;
};

void csv_cb1(void *p1, size_t s, void *p2) {
  struct parse_counts *pc = (struct parse_counts*)p2;

  switch (pc->fieldnum++) {
  case CSV_FIELDNUM_ROUTEID:
    strncpy(all_routes[pc->recnum].route_id, p1, MAX_ROUTEID);
    break;

  case CSV_FIELDNUM_ROUTE_SHORT_NAME:
    strncpy(all_routes[pc->recnum].route_shortname, p1, MAX_ROUTESHORTNAME);
    break;

  case CSV_FIELDNUM_ROUTE_LONG_NAME:
    strncpy(all_routes[pc->recnum].route_longname, p1, MAX_ROUTELONGNAME);
    break;

  case CSV_FIELDNUM_ROUTE_COLOUR:
    strncpy(all_routes[pc->recnum].route_colour, p1, MAX_COLOUR);
    break;
  }
}

void csv_cb2(int i, void *p) {
  struct parse_counts* pc = (struct parse_counts*) p;

  pc->fieldnum = 0;
  pc->recnum++;
}

void csv_count_cb(int i, void *p) { num_routes++; }


void routes_load_routes() {
  struct parse_counts parse_counts = {0, 0};
  uint8_t *buf;
  size_t s,t;
  struct csv_parser parser;

  route_txt = resource_get_handle(RESOURCE_ID_ROUTES_TXT);
  s = resource_size(route_txt);
  buf = (uint8_t*)malloc(s);
  /* TODO catch malloc fail */

  if (s == resource_load(route_txt, buf, s)) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "loaded routes.txt %d", s);
    
    if (csv_init(&parser, CSV_APPEND_NULL) != 0) {
      APP_LOG(APP_LOG_LEVEL_ERROR, "csv_init() failed");
    } else {
      /* count records */
      t = csv_parse(&parser, buf, s, NULL, csv_count_cb, NULL);
      csv_fini(&parser, csv_cb1, csv_cb2, NULL);
      if (t < s) {
	APP_LOG(APP_LOG_LEVEL_ERROR, "%s", csv_strerror(csv_error(&parser)));
      } else {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "parsed %d bytes found %d routes", t, num_routes);

	all_routes = calloc(num_routes, sizeof(struct Route));
	t = csv_parse(&parser, buf, s, csv_cb1, csv_cb2, &parse_counts);
	csv_fini(&parser, csv_cb1, csv_cb2, NULL);
	if (t < s) {
	  /* TODO error handling */
	}
      }
    }
  } else {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Didn't load entire routes.txt");
  }

  free(buf);
}

void routes_deinit() {
  if (all_routes != NULL) {
    free(all_routes);
  }
}

/* interface functions */
int routes_num_routes(void) { return num_routes; }

/* struct of particular route details; 0 == OK, -1 error */
int routes_get_route_details(char *route_id, struct Route *route_details) {
  int ret = -1;

  for (int i = 0; i < num_routes; i++) {
    if (strncmp(route_id, all_routes[i].route_id, MAX_ROUTEID) == 0) {
      strncpy(route_details->route_id, route_id, MAX_ROUTEID);
      strncpy(route_details->route_shortname, all_routes[i].route_shortname, MAX_ROUTESHORTNAME);
      strncpy(route_details->route_longname, all_routes[i].route_longname, MAX_ROUTELONGNAME);
      strncpy(route_details->route_colour, all_routes[i].route_colour, MAX_COLOUR);
      ret = 0;
      break;
    }
  }
    return ret;
}
  
