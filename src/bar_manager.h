#ifndef BAR_MANAGER_H
#define BAR_MANAGER_H
#include <stdint.h>

#define TIMER_CALLBACK(name) void name(CFRunLoopTimerRef timer, void *context)
typedef TIMER_CALLBACK(timer_callback);

#define SHELL_TIMER_CALLBACK(name) void name(CFRunLoopTimerRef timer, void *context)
typedef SHELL_TIMER_CALLBACK(shell_timer_callback);


struct bar_manager {
  bool any_bar_hidden;
  bool frozen;
  bool sleeps;
  bool picky_redraw;
  bool topmost;
  bool font_smoothing;
  uint32_t window_level;
  CFRunLoopTimerRef refresh_timer;
  CFRunLoopTimerRef shell_refresh_timer;
  struct bar **bars;
  int bar_count;
  struct bar_item **bar_items;
  struct bar_item default_item;
  int bar_item_count;
  char position;
  char display;
  uint32_t margin;
  uint32_t blur_radius;
  int y_offset;
  bool shadow;

  struct background background;
  struct custom_events custom_events;
};

int bar_manager_get_item_index_for_name(struct bar_manager* bar_manager, char* name);
void bar_manager_custom_events_trigger(struct bar_manager* bar_manager, char* name);


struct bar_item* bar_manager_create_item(struct bar_manager* bar_manager);
void bar_manager_remove_item(struct bar_manager* bar_manager, struct bar_item* bar_item);
void bar_manager_move_item(struct bar_manager* bar_manager, struct bar_item* item, struct bar_item* reference, bool before);
void bar_manager_handle_notification(struct bar_manager* bar_manager, char* context);

void bar_manager_serialize(struct bar_manager* bar_manager, FILE* rsp);

void bar_manager_update(struct bar_manager* bar_manager, bool forced);
void bar_manager_update_space_components(struct bar_manager* bar_manager, bool forced);
bool bar_manager_set_background_blur(struct bar_manager* bar_manager, uint32_t radius);
bool bar_manager_set_position(struct bar_manager* bar_manager, char pos);
bool bar_manager_set_spaces(struct bar_manager* bar_manager, bool value);
bool bar_manager_set_spaces_for_all_displays(struct bar_manager* bar_manager, bool value);
bool bar_manager_set_display(struct bar_manager* bar_manager, char display);
bool bar_manager_set_hidden(struct bar_manager* bar_manager, uint32_t sid, bool hidden);
bool bar_manager_set_topmost(struct bar_manager* bar_manager, bool topmost);
bool bar_manager_set_shadow(struct bar_manager* bar_manager, bool shadow);
bool bar_manager_set_font_smoothing(struct bar_manager* bar_manager, bool smoothing);
void bar_manager_sort(struct bar_manager* bar_manager, struct bar_item** ordering, uint32_t count);

struct bar_item* bar_manager_get_item_by_point(struct bar_manager* bar_manager, CGPoint point, uint32_t adid);
uint32_t bar_manager_get_center_length_for_bar(struct bar_manager* bar_manager, struct bar* bar);

void bar_manager_freeze(struct bar_manager* bar_manager);
void bar_manager_unfreeze(struct bar_manager* bar_manager);

void bar_manager_display_changed(struct bar_manager* bar_manager);
void bar_manager_refresh(struct bar_manager* bar_manager, bool forced);
void bar_manager_resize(struct bar_manager* bar_manager);
void bar_manager_begin(struct bar_manager* bar_manager);
void bar_manager_init(struct bar_manager* bar_manager);

void bar_manager_handle_mouse_entered(struct bar_manager* bar_manager, struct bar_item* bar_item);
void bar_manager_handle_mouse_exited(struct bar_manager* bar_manager);
void bar_manager_handle_front_app_switch(struct bar_manager* bar_manager);
void bar_manager_handle_space_change(struct bar_manager* bar_manager);
void bar_manager_handle_display_change(struct bar_manager* bar_manager);
void bar_manager_handle_system_woke(struct bar_manager* bar_manager);
void bar_manager_handle_system_will_sleep(struct bar_manager* bar_manager);

struct bar_item* bar_manager_get_item_by_point(struct bar_manager* bar_manager, CGPoint point, uint32_t sid);

#endif
