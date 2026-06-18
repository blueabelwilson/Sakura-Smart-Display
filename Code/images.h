#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_cats_icon;
extern const lv_img_dsc_t img_leaf_pat;
extern const lv_img_dsc_t img_plants_icon;
extern const lv_img_dsc_t img_poo_leaf_pat;
extern const lv_img_dsc_t img_poo_pat;
extern const lv_img_dsc_t img_wing;
extern const lv_img_dsc_t img_kero;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[7];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/