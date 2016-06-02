#include <pebble.h>
#include "linestatus.h"

static MenuLayer *menu;

uint16_t mcb_get_rows_in_section(MenuLayer *menu, uint16_t section, void *context) {
  return 5;
}

void mcb_draw_row(GContext *gcontext, const Layer *cell_layer, MenuIndex *cell_index, void *context) {
  char t[] = "xx";
  snprintf(t, strlen(t), "%d",cell_index->row);
  menu_cell_basic_draw(gcontext, cell_layer, t, "subtitle", NULL);
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


MenuLayer *status_menu_create(GRect bounds, Window *window, LineStatus *line_status) {

  menu = menu_layer_create(bounds);
  menu_layer_set_callbacks(menu, (void*)line_status, callbacks);
  layer_add_child(window_get_root_layer(window), menu_layer_get_layer(menu));
  menu_layer_set_click_config_onto_window(menu, window);
 
  return menu;
}

void status_menu_destroy(void) {
  menu_layer_destroy(menu);
}
