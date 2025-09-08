#ifndef TPMS_CONTROLLER_H
#define TPMS_CONTROLLER_H

#include <stdint.h>

// TPMS (Tire Pressure Monitoring System) controller

typedef struct {
    uint32_t tire_id;
    float pressure_psi;
    float temperature_c;
    uint8_t battery_level;
    uint32_t last_update_time;
} tpms_sensor_t;

// Function declarations
int tpms_init(void);
int tpms_update(void);
int tpms_get_pressure(uint32_t tire_id, float* pressure);
int tpms_get_temperature(uint32_t tire_id, float* temperature);
int tpms_check_alert_conditions(void);

#endif