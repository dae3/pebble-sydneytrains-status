#include <pebble.h>


/*
  curl -v  -H "Authorization: Bearer XXXXXXXXXX" https://api.transport.nsw.gov.au/v1/gtfs/schedule/sydneytrains > schedules.zip
  schedules.zip/routes.txt
  "route_id","agency_id","route_short_name","route_long_name","route_desc","route_type","route_url","route_color","route_text_color"
*/

#define MAX_ROUTEID 8
#define MAX_ROUTESHORTNAME 3
#define MAX_COLOUR 6

typedef struct Route {
  char route_id[MAX_ROUTEID]
  char route_shortname[MAX_ROUTESHORTNAME]
  char route_colour[MAX_COLOUR]
} Route;
