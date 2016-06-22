#include <pebble.h>
#include "linestatus.h"

static Window *window;
static StatusBarLayer *status_bar;
static ScrollLayer *scroll_layer;
static const int CIRCLEDIAMETER = 30;
static const int CIRCLEOFFSET = 15;
static const int NUMCIRCLES = 50;


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
    fill_color.argb = color_sequence[i % 4];
    graphics_context_set_fill_color(ctx, fill_color);

    GPoint p = GPoint(x, y);
    graphics_fill_circle(ctx, p, CIRCLEDIAMETER/2);

    graphics_context_set_stroke_color(ctx, GColorBlack);
    graphics_draw_circle(ctx, p, (CIRCLEDIAMETER+5)/2);

    GRect bbox = GRect(p.x-CIRCLEDIAMETER/2, p.y-CIRCLEDIAMETER/2, CIRCLEDIAMETER, CIRCLEDIAMETER);
    //graphics_draw_rect(ctx, bbox);

    char lname[3];
    snprintf(lname, 3, "%d", i);
    graphics_draw_text(ctx, lname, font, bbox, GTextOverflowModeWordWrap,
		       GTextAlignmentCenter, NULL);

    x += ((CIRCLEDIAMETER + CIRCLEOFFSET));
    if ((x + CIRCLEDIAMETER/2) > bounds.origin.x + bounds.size.w) {
      x = bounds.origin.x + (CIRCLEDIAMETER/2) + CIRCLEOFFSET;
      y += (CIRCLEDIAMETER + CIRCLEOFFSET);
    }
  }
  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, y + CIRCLEDIAMETER/2 + CIRCLEOFFSET));
}

/* static void draw(Layer *layer, GContext *ctx) { */
/*   GRect bounds = layer_get_bounds(layer); */
/*   int xmid = bounds.origin.x + (bounds.size.w/2); */
/*   int ytop = bounds.origin.y + (CIRCLEDIAMETER/2); */
/*   GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_09); */
/*   GColor8 fill_color; */

/*   for (int i = 0; i < NUMCIRCLES; i++) { */
/*     fill_color.argb = color_sequence[i % 4]; */
/*     graphics_context_set_fill_color(ctx, fill_color); */
/*     GPoint p = GPoint(xmid, ytop + (CIRCLEDIAMETER*i) + CIRCLEOFFSET); */
/*     graphics_fill_circle(ctx, p, CIRCLEDIAMETER/2); */

/*     GRect bbox = GRect(p.x-CIRCLEDIAMETER/2, p.y-CIRCLEDIAMETER/2, CIRCLEDIAMETER, CIRCLEDIAMETER); */
/*     graphics_draw_rect(ctx, bbox); */

/*     char lname[2]; */
/*     snprintf(lname, 2, "%d", i); */
/*     graphics_draw_text(ctx, lname, font, bbox, GTextOverflowModeWordWrap, */
/* 		       GTextAlignmentCenter, NULL); */
/*   } */
/* } */

// window event handlers
static void load(struct Window *w) {
  Layer *wr = window_get_root_layer(window);

  // content sub-layer
  GRect content_layer_frame = GRect(0, 0, layer_get_bounds(wr).size.w, (CIRCLEDIAMETER + CIRCLEOFFSET) * NUMCIRCLES);
  Layer *content_layer = layer_create(content_layer_frame);
  layer_set_update_proc(content_layer, draw);

  // scroll layer
  scroll_layer = scroll_layer_create(layer_get_bounds(wr));
  scroll_layer_add_child(scroll_layer, content_layer);
  scroll_layer_set_content_size(scroll_layer, content_layer_frame.size);
  scroll_layer_set_click_config_onto_window(scroll_layer, w);
  layer_add_child(wr, (Layer*)scroll_layer);
  
  // status bar layer
  status_bar = status_bar_layer_create();
  status_bar_layer_set_colors(status_bar, GColorBlack, GColorWhite);
  layer_add_child(wr, (Layer*)status_bar);
}

static void unload(struct Window *w) {
  status_bar_layer_destroy(status_bar);
  scroll_layer_destroy(scroll_layer);
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

  /* if (++color_index > 2) */
  /*   color_index = 0; */
  /* layer_mark_dirty(window_get_root_layer(window)); */

  /* APP_LOG(APP_LOG_LEVEL_DEBUG, "select. color index %d", color_index); */
  APP_LOG(APP_LOG_LEVEL_DEBUG, "select");
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
