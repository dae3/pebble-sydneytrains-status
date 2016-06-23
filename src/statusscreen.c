#include <pebble.h>
#include "linestatus.h"

static Window *window;
static StatusBarLayer *status_bar;
static Layer *content_layer;
static ScrollLayer *scroll_layer;

static const int CIRCLEDIAMETER = 30;
static const int CIRCLEOFFSET = 15;
static const int NUMCIRCLES = 9;
static const int STATUSCIRCLEOFFSET = 7;
static const int STATUSCIRCLESIZE = 3;
static const int TEXTYFUDGE = -1.5;

// drawing
static uint8_t color_sequence[] =  { GColorRedARGB8, GColorBlueARGB8, GColorGreenARGB8, GColorBlackARGB8, GColorYellowARGB8 };

static void draw(Layer *layer, GContext *ctx) {
  GRect status_bar_bounds = layer_get_bounds((Layer*)status_bar);
  GRect bounds = layer_get_bounds(layer);
  int x = bounds.origin.x + (CIRCLEDIAMETER/2) + CIRCLEOFFSET;
  int y = bounds.origin.y + (CIRCLEDIAMETER/2) + CIRCLEOFFSET + status_bar_bounds.size.h;
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  GColor8 fill_color;

  for (int i = 0; i < NUMCIRCLES; i++) {
    fill_color.argb = color_sequence[i % 5];
    graphics_context_set_fill_color(ctx, fill_color);

    // main circle
    GPoint p = GPoint(x, y);
    graphics_fill_circle(ctx, p, CIRCLEDIAMETER/2);

    // status ring
    graphics_context_set_stroke_width(ctx, STATUSCIRCLESIZE);
    graphics_context_set_stroke_color(ctx, GColorRed);
    if (i%2 == 0)
      graphics_draw_circle(ctx, p, (CIRCLEDIAMETER + STATUSCIRCLEOFFSET)/2);

    // line name text
    GRect bbox = GRect(p.x-CIRCLEDIAMETER/2, p.y-CIRCLEDIAMETER/2+TEXTYFUDGE, CIRCLEDIAMETER, CIRCLEDIAMETER);
    char lname[3];
    snprintf(lname, 3, "T%d", i);
    graphics_context_set_text_color(ctx, gcolor_legible_over(fill_color));
    graphics_draw_text(ctx, lname, font, bbox, GTextOverflowModeWordWrap,
		       GTextAlignmentCenter, NULL);

    // make grid layout
    x += ((CIRCLEDIAMETER + CIRCLEOFFSET));
    if ((x + CIRCLEDIAMETER/2) > bounds.origin.x + bounds.size.w) {
      x = bounds.origin.x + (CIRCLEDIAMETER/2) + CIRCLEOFFSET;
      y += (CIRCLEDIAMETER + CIRCLEOFFSET);
    }
  }
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, y));
}

// click event handlers
static void upclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
}

static void downclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
}

static void selectclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "select");
}

static void backclick(ClickRecognizerRef rec, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "back");
  window_stack_pop(true);
}


static void clickconfigprovider(void *context) {
  /*
    up and down handled by the ScrollLayer
    window_single_click_subscribe(BUTTON_ID_UP, upclick);
    window_single_click_subscribe(BUTTON_ID_DOWN, downclick);
 */
  window_single_click_subscribe(BUTTON_ID_SELECT, selectclick);
  window_single_click_subscribe(BUTTON_ID_BACK, backclick);
}

static void scrolllayercallback(struct ScrollLayer *layer, void *context) {
  // do nothing, just need this to override the back and select behaviour
}
 
// window event handlers
static void load(struct Window *w) {
  Layer *wr = window_get_root_layer(window);

  // content sub-layer
  GRect content_layer_frame = GRect(0, 0, layer_get_bounds(wr).size.w, (CIRCLEDIAMETER + CIRCLEOFFSET) * NUMCIRCLES);
  content_layer = layer_create(content_layer_frame);
  layer_set_update_proc(content_layer, draw);

  // scroll layer
  scroll_layer = scroll_layer_create(layer_get_bounds(wr));
  scroll_layer_add_child(scroll_layer, content_layer);
  scroll_layer_set_content_size(scroll_layer, content_layer_frame.size);
  scroll_layer_set_click_config_onto_window(scroll_layer, w);
  layer_add_child(wr, (Layer*)scroll_layer);

  scroll_layer_set_callbacks(scroll_layer, (struct ScrollLayerCallbacks) { .click_config_provider = clickconfigprovider, .content_offset_changed_handler = scrolllayercallback });  
  // status bar layer
  status_bar = status_bar_layer_create();
  status_bar_layer_set_colors(status_bar, GColorBlack, GColorWhite);
  layer_add_child(wr, (Layer*)status_bar);
}

static void unload(struct Window *w) {
  status_bar_layer_destroy(status_bar);
  layer_destroy(content_layer);
  scroll_layer_destroy(scroll_layer);
}

static void appear(struct Window *w) {

}

static void disappear(struct Window *w) {

}


Window *statusscreen_create(void) {
  window = window_create();
  window_set_window_handlers(window, (struct WindowHandlers){ .load = load, .unload = unload, .appear = appear, .disappear = disappear });
  return window;
}

void statusscreen_destroy(void) {
  unload(window);
}
