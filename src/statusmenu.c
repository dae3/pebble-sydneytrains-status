#include <pebble.h>
#include "linestatus.h"
#include "appmsg.h"

static MenuLayer *menu;

uint16_t mcb_get_rows_in_section(MenuLayer *menu, uint16_t section, void *context) {
  return getNumLines();
}

void mcb_draw_row(GContext *gcontext, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
  LineStatus *ls = getLineStatus();
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "mcb_draw_row");
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "mcb_draw_row %s %s", ls[cell_index->row].line_name, ls[cell_index->row].status);
  menu_cell_basic_draw(gcontext, cell_layer,
		       ls[cell_index->row].line_name,
		       ls[cell_index->row].status,
		       NULL);
}

void mcb_select_row(MenuLayer *menu, MenuIndex *cell_index, void *context) {

}

void mcb_selection_will_change(struct MenuLayer *menu, MenuIndex *new_index, MenuIndex old_index, void *context) {

}

void mcb_draw_background(GContext *gcontext, const Layer *background_layer, bool highlight, void *contextt) {

}

static MenuLayerCallbacks callbacks = {
  .get_num_rows = mcb_get_rows_in_section,
  .draw_row = mcb_draw_row,
  .select_click = mcb_select_row,
  .selection_will_change = mcb_selection_will_change,
  .draw_background = mcb_draw_background
};


MenuLayer *status_menu_create(GRect bounds, Window *window) {

  APP_LOG(APP_LOG_LEVEL_DEBUG, "status_menu_create");

  menu = menu_layer_create(bounds);
  menu_layer_set_callbacks(menu, NULL, callbacks);
  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu));
  menu_layer_set_click_config_onto_window(menu, window);
 
  appmsg_refreshstatus();

  return menu;
}

void status_menu_destroy(void) {
  menu_layer_destroy(menu);
}

void status_menu_refresh(void) {
  menu_layer_reload_data(menu);
}
