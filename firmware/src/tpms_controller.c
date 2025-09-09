#include "tpms_controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TIRES 4
#define MIN_PRESSURE_PSI 30.0
#define MAX_PRESSURE_PSI 40.0
#define ALERT_LOW_PRESSURE 32.0
#define ALERT_HIGH_PRESSURE 38.0

static tpms_sensor_t tire_sensors[MAX_TIRES];
static int system_initialized = 0;

int tpms_init(void) {
    printf("[TPMS] Initializing Tire Pressure Monitoring System\n");
    
    // Initialize tire sensors with default values
    for(int i = 0; i < MAX_TIRES; i++) {
        tire_sensors[i].tire_id = i + 1;
        tire_sensors[i].pressure_psi = 35.0 + (rand() % 5); // 35-39 PSI
        tire_sensors[i].temperature_c = 20.0 + (rand() % 10); // 20-29°C
        tire_sensors[i].battery_level = 80 + (rand() % 20); // 80-99%
        tire_sensors[i].last_update_time = time(NULL);
    }
    
    system_initialized = 1;
    printf("[TPMS] System initialized successfully\n");
    return 0;
}

int tpms_update(void) {
    if (!system_initialized) return -1;
    
    // Simulate sensor readings (small random variations)
    for(int i = 0; i < MAX_TIRES; i++) {
        // Simulate slight pressure variations
        float variation = (rand() % 100 - 50) / 100.0; // ±0.5 PSI
        tire_sensors[i].pressure_psi += variation;
        
        // Keep within realistic bounds
        if(tire_sensors[i].pressure_psi < MIN_PRESSURE_PSI) 
            tire_sensors[i].pressure_psi = MIN_PRESSURE_PSI;
        if(tire_sensors[i].pressure_psi > MAX_PRESSURE_PSI) 
            tire_sensors[i].pressure_psi = MAX_PRESSURE_PSI;
        
        tire_sensors[i].last_update_time = time(NULL);
    }
    
    // Check for alert conditions
    tpms_check_alert_conditions();
    
    return 0;
}

int tpms_get_pressure(uint32_t tire_id, float* pressure) {
    if (!system_initialized || tire_id < 1 || tire_id > MAX_TIRES || !pressure) {
        return -1;
    }
    
    *pressure = tire_sensors[tire_id - 1].pressure_psi;
    return 0;
}

int tpms_get_temperature(uint32_t tire_id, float* temperature) {
    if (!system_initialized || tire_id < 1 || tire_id > MAX_TIRES || !temperature) {
        return -1;
    }
    
    *temperature = tire_sensors[tire_id - 1].temperature_c;
    return 0;
}

int tpms_check_alert_conditions(void) {
    static int alert_count = 0;
    
    for(int i = 0; i < MAX_TIRES; i++) {
        if(tire_sensors[i].pressure_psi < ALERT_LOW_PRESSURE) {
            printf("[TPMS] ALERT: Tire %d low pressure: %.1f PSI\n", 
                   tire_sensors[i].tire_id, tire_sensors[i].pressure_psi);
            alert_count++;
        }
        else if(tire_sensors[i].pressure_psi > ALERT_HIGH_PRESSURE) {
            printf("[TPMS] ALERT: Tire %d high pressure: %.1f PSI\n", 
                   tire_sensors[i].tire_id, tire_sensors[i].pressure_psi);
            alert_count++;
        }
    }
    
    return alert_count;
}