#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include "tpms_controller.h"
#include "display_controller.h"

int main() {
    printf("ECU Firmware v1.0.0 Starting...\n");
    
    // Initialize controllers 
    tpms_init();
    display_init();
    
    // Main control loop
    while(1) {
        // Simulate ECU operations
        tpms_update();
        display_update();
        
        // Sleep to simulate timing (100ms cycle)
        usleep(100000);
    }
    
    return 0;
}