#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN_PAGE = 1,
    SCREEN_ID_TASK_PAGE = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *main_page;
    lv_obj_t *task_page;
    lv_obj_t *cnt_poo__leaf_pattern;
    lv_obj_t *cnt_poo_pattern;
    lv_obj_t *cnt_plant_pattern;
    lv_obj_t *lbl_time;
    lv_obj_t *kero;
    lv_obj_t *screenchange;
    lv_obj_t *screenchange_1;
    lv_obj_t *litter_icon;
    lv_obj_t *water_plants;
} objects_t;

extern objects_t objects;

void create_screen_main_page();
void tick_screen_main_page();

void create_screen_task_page();
void tick_screen_task_page();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/