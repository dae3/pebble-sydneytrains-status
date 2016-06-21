#include <pebble.h>
#include "linestatus.h"

static Window *window;
static StatusBarLayer *status_bar;
static ScrollLayer *scroll_layer;

// drawing
static uint8_t color_sequence[] =  { GColorRedARGB8, GColorBlueARGB8, GColorGreenARGB8, GColorBlackARGB8, GColorYellowARGB8 };
static int color_index = 0;

static void draw(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(layer);
  int xmid = bounds.origin.x + (bounds.size.w/2);
  int ytop = bounds.origin.y + (bounds.size.h/2);

  GColor8 fill_color;
  static int diam = 20;

  for (int i = 0; i < 4; i++) {
    fill_color.argb = color_sequence[i];
    graphics_context_set_fill_color(ctx, fill_color);
    GPoint p = GPoint(xmid, ytop + (diam*i*2));
    graphics_fill_circle(ctx, p, diam);
  }
}

// window event handlers
static void load(struct Window *w) {
  Layer *wr = window_get_root_layer(window);
  scroll_layer = scroll_layer_create(layer_get_bounds(wr));
  layer_set_update_proc((Layer*)scroll_layer, draw);
  layer_add_child(wr, (Layer*)scroll_layer);
  GSize sls = { .w = layer_get_bounds(wr).size.w, .h = 25*5 };
  scroll_layer_set_content_size(scroll_layer, sls);
  scroll_layer_set_click_config_onto_window(scroll_layer, w);

  status_bar = status_bar_layer_create();
  status_bar_layer_set_colors(status_bar, GColorBlack, GColorWhite);
  layer_add_child(wr, (Layer*)status_bar);
}

static void unload(struct Window *w) {
  status_bar_layer_destroy(status_bar);
}

static void appear(struct Window *w) {

}

static void disappear(struct Window *w) {

}

// click event handlers
static void upclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
}

static void downclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
}

static void selectclick(ClickRecognizerRef rec, void *context) {

  if (++color_index > 2)
    color_index = 0;
  layer_mark_dirty(window_get_root_layer(window));

  APP_LOG(APP_LOG_LEVEL_DEBUG, "select. color index %d", color_index);
}

static void backclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "back");
  window_stack_pop(true);
}


static void clickconfigprovider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, upclick);
  window_single_click_subscribe(BUTTON_ID_DOWN, downclick);
  window_single_click_subscribe(BUTTON_ID_SELECT, selectclick);
  window_single_click_subscribe(BUTTON_ID_BACK, backclick);
}


Window *statusscreen_create(void) {
  window = window_create();
  window_set_window_handlers(window, (struct WindowHandlers){ .load = load, .unload = unload, .appear = appear, .disappear = disappear });
  window_set_click_config_provider(window, clickconfigprovider);

  return window;
}

void statusscreen_destroy(void) {
  unload(window);
}
