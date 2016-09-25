#include <pebble.h>


/*
  To retrieve current routes data: (replacing XXXX with login token (use t2.js)
  curl -v  -H "Authorization: Bearer XXXXXXXXXX" https://api.transport.nsw.gov.au/v1/gtfs/schedule/sydneytrains > schedules.zip
  schedules.zip/routes.txt
  "route_id","agency_id","route_short_name","route_long_name","route_desc","route_type","route_url","route_color","route_text_color"
*/

#define MAX_ROUTEID 8
#define MAX_ROUTESHORTNAME 3
#define MAX_ROUTELONGNAME 50
#define MAX_COLOUR 6

#define CSV_FIELDNUM_ROUTEID 0
#define CSV_FIELDNUM_AGENCYID 1
#define CSV_FIELDNUM_ROUTE_SHORT_NAME 2
#define CSV_FIELDNUM_ROUTE_LONG_NAME 3
#define CSV_FIELDNUM_ROUTE_DESC 4
#define CSV_FIELDNUM_ROUTE_TYPE 5
#define CSV_FIELDNUM_ROUTE_URL 6
#define CSV_FIELDNUM_ROUTE_COLOUR 7
#define CSV_FIELDNUM_ROUTE_TEXT_COLOUR 8

struct Route {
  char route_id[MAX_ROUTEID+1];
  char route_shortname[MAX_ROUTESHORTNAME+1];
  char route_longname[MAX_ROUTELONGNAME+1];
  char route_colour[MAX_COLOUR+1];
} ;

int routes_num_routes();
void routes_load_routes();
int routes_get_route_details(char *route_id, struct Route *route_details);
void routes_deinit();
