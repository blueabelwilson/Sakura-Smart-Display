#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_btn_go_to_tasks(lv_event_t * e);
extern void action_btn_go_to_home(lv_event_t * e);
extern void action_btn_reset_litter(lv_event_t * e);
extern void action_btn_reset_plants(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/