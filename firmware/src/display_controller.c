#include "display_controller.h"
#include "tpms_controller.h"
#include <stdio.h>
#include <time.h>

static display_state_t display_state;
static int system_initialized = 0;
static time_t start_time;

int display_init(void) {
    printf("[DISPLAY] Initializing Digital Display Controller\n");
    
    display_state.mode = DISPLAY_MODE_NORMAL;
    display_state.brightness = 75; // 75% brightness
    display_state.uptime_seconds = 0;
    display_state.alert_active = 0;
    
    start_time = time(NULL);
    system_initialized = 1;
    
    printf("[DISPLAY] Display system ready\n");
    return 0;
}

int display_update(void) {
    if (!system_initialized) return -1;
    
    // Update uptime
    display_state.uptime_seconds = time(NULL) - start_time;
    
    // Check for alerts and update display accordingly
    int alert_count = tpms_check_alert_conditions();
    if (alert_count > 0) {
        display_state.mode = DISPLAY_MODE_ALERT;
        display_state.alert_active = 1;
    } else if (display_state.alert_active) {
        display_state.mode = DISPLAY_MODE_NORMAL;
        display_state.alert_active = 0;
    }
    
    // Show current information (every 10 seconds)
    static time_t last_display_update = 0;
    if (time(NULL) - last_display_update >= 10) {
        display_show_tpms_data();
        last_display_update = time(NULL);
    }
    
    return 0;
}

int display_set_mode(display_mode_t mode) {
    if (!system_initialized) return -1;
    
    display_state.mode = mode;
    printf("[DISPLAY] Mode changed to %d\n", mode);
    return 0;
}

int display_set_brightness(uint8_t brightness) {
    if (!system_initialized || brightness > 100) return -1;
    
    display_state.brightness = brightness;
    printf("[DISPLAY] Brightness set to %d%%\n", brightness);
    return 0;
}

int display_show_tpms_data(void) {
    if (!system_initialized) return -1;
    
    printf("\n[DISPLAY] === Tire Pressure Status ===\n");
    for(int i = 1; i <= 4; i++) {
        float pressure, temperature;
        if(tpms_get_pressure(i, &pressure) == 0 && 
           tpms_get_temperature(i, &temperature) == 0) {
            printf("[DISPLAY] Tire %d: %.1f PSI, %.1f°C\n", 
                   i, pressure, temperature);
        }
    }
    printf("[DISPLAY] System Uptime: %ld seconds\n", display_state.uptime_seconds);
    printf("[DISPLAY] ============================\n\n");
    
    return 0;
}