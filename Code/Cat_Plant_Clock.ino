/*
* @ File:   Cat_Plant_Clock.ino
* @ Description: Custom Wi-Fi desktop tracker with UI layout control
*/

#define FNK0114B_2P8_240x320_ST7789 1
#include "display.h"      // Freenove's display driver
#include <WiFi.h>
#include "time.h"
#include "ui.h"           // EEZ Studio core header
#include "screens.h"      // Grants access to your page/container objects

// --- Wi-Fi Credentials ---
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// --- Time Sync Configuration ---
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;    // Mountain Standard Time (Edmonton)
const int   daylightOffset_sec = 3600; // 1 hour for Daylight Saving Time

// --- Tracker States ---
int litterDays = 0;
int plantDays = 0;
int lastDayValue = -1;

Display screen; // Freenove display engine instance

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  // Turn on the CYD screen using the manufacturer's logic
  screen.init(); 

  // Build your visual UI layout
  ui_init(); 

  // Start Wi-Fi connection
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" Connected!");

  // Sync internal clock with internet time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  // Keep Freenove touch and LVGL graphics rendering engine ticking
  screen.routine(); 

  // Check time and rollover events once a second
  static unsigned long lastTimeCheck = 0;
  if (millis() - lastTimeCheck > 1000) {
    lastTimeCheck = millis();
    
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        return; 
    }

    // 1. Update your clock layout string
    char timeText[6];
    strftime(timeText, sizeof(timeText), "%H:%M", &timeinfo);
    lv_label_set_text(objects.lbl_time, timeText); // Updates your 96pt label

    // 2. Midnight Rollover Check
    if (lastDayValue == -1) {
        lastDayValue = timeinfo.tm_mday; 
    } 
    else if (timeinfo.tm_mday != lastDayValue) {
        lastDayValue = timeinfo.tm_mday;
        litterDays++;
        plantDays++;
        update_background_color();
    }
  }
  delay(5); // Smooth background performance breathing room
}

// --- Background Pattern Swapping Logic ---
void update_background_color() {
    bool litterAlert = (litterDays >= 4);
    bool plantAlert = (plantDays >= 14);
    
    // Grab explicit references to your generated UI components
    lv_obj_t* homeScreen = objects.main_page; 
    lv_obj_t* plantPattern = objects.cnt_plant_pattern;
    lv_obj_t* pooPattern = objects.cnt_poo_pattern;
    lv_obj_t* combinedPattern = objects.cnt_poo__leaf_pattern;

    // Reset layout by hiding all patterns first
    lv_obj_add_flag(plantPattern, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(pooPattern, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(combinedPattern, LV_OBJ_FLAG_HIDDEN);

    if (litterAlert && plantAlert) {
        // RED ALERT: Show combined pattern
        lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0xFF0000), LV_PART_MAIN);
        lv_obj_clear_flag(combinedPattern, LV_OBJ_FLAG_HIDDEN);
    } 
    else if (plantAlert) {
        // GREEN ALERT: Show leaves pattern
        lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0x00FF00), LV_PART_MAIN);
        lv_obj_clear_flag(plantPattern, LV_OBJ_FLAG_HIDDEN);
    } 
    else if (litterAlert) {
        // YELLOW ALERT: Show poo pattern
        lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0xFFFF00), LV_PART_MAIN);
        lv_obj_clear_flag(pooPattern, LV_OBJ_FLAG_HIDDEN);
    } 
    else {
        // DEFAULT PINK: Everything is clean
        lv_obj_set_style_bg_color(homeScreen, lv_color_hex(0xFFC0CB), LV_PART_MAIN);
    }
}

// --- Navigation Button Remappings ---
extern "C" {

  void action_btn_go_to_tasks(lv_event_t * e) {
      lv_scr_load_anim(objects.task_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  }

  void action_btn_go_to_home(lv_event_t * e) {
      lv_scr_load_anim(objects.main_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  }

  void action_btn_reset_litter(lv_event_t * e) {
      litterDays = 0;
      update_background_color();
      lv_scr_load_anim(objects.main_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  }

  void action_btn_reset_plants(lv_event_t * e) {
      plantDays = 0;
      update_background_color();
      lv_scr_load_anim(objects.main_page, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false);
  }

}