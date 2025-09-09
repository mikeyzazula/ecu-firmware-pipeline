#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <stdint.h>

// Display controller for digital dashboard
// Simulating the display systems you work with at PACCAR

typedef enum {
    DISPLAY_MODE_NORMAL,
    DISPLAY_MODE_DIAGNOSTIC,
    DISPLAY_MODE_ALERT,
    DISPLAY_MODE_OFF
} display_mode_t;

typedef struct {
    display_mode_t mode;
    uint8_t brightness;
    uint32_t uptime_seconds;
    uint8_t alert_active;
} display_state_t;

// Function declarations
int display_init(void);
int display_update(void);
int display_set_mode(display_mode_t mode);
int display_set_brightness(uint8_t brightness);
int display_show_tpms_data(void);

#endif