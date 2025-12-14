/*
 * set.c
 *
 *  Created on: Dec 14, 2025
 *      Author: nguye
 */
#include "set.h"
#include "button.h"
#include "global.h"
#include "auto.h"
#include "software_timer.h"
#include "display.h"
#include "i2c-lcd.h"

// Helper function to turn off all traffic LEDs
void allLedoff() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_10, RESET);
}
int flagforledblinky = 1;
// Handle LED blinking effects for configuration modes (2, 3, 4)
void ledblinky() {
	// Turn off LEDs once before starting the blinking sequence
	if(flagforledblinky == 0) {
		allLedoff();
		flagforledblinky = 1;
		setTimer1(250); // Set blink frequency (250ms)
	}
	switch(mode) {
        case 2: { // Mode 2: Adjust Red Light Time
            if(flag1 == 1) { // Timer interrupt flag
                // Toggle LEDs associated with Red Light adjustment
                HAL_GPIO_TogglePin(LED1A_GPIO_Port, LED1A_Pin);
                HAL_GPIO_TogglePin(LED1B_GPIO_Port, LED1B_Pin);
                HAL_GPIO_TogglePin(LED2A_GPIO_Port, LED2A_Pin);
                HAL_GPIO_TogglePin(LED2B_GPIO_Port, LED2B_Pin);
                setTimer1(250);
            }
        }
        break;
        case 3: { // Mode 3: Adjust Green Light Time
            if(flag1 == 1) {
                // Toggle LEDs associated with Green Light adjustment
                HAL_GPIO_TogglePin(LED1B_GPIO_Port, LED1B_Pin);
                HAL_GPIO_TogglePin(LED2B_GPIO_Port, LED2B_Pin);
                setTimer1(250);
            }
        }
        break;
        case 4: {// Mode 4: Adjust Yellow Light Time
            if(flag1 == 1) {
                // Toggle LEDs associated with Yellow Light adjustment
                HAL_GPIO_TogglePin(LED1A_GPIO_Port, LED1A_Pin);
                HAL_GPIO_TogglePin(LED2A_GPIO_Port, LED2A_Pin);
                setTimer1(250);
            }
        }
        break;
        default: {}
        break;
	}
}
int modecase5 = 1; // Sub-state for Manual Mode (Mode 5)
int temp_flag = 0; // Flag to update LCD only once when switching manual states
// Main function to handle system modes and user inputs.
void setmode() {
    // --- Button 4 Logic: Enter Manual Mode or Toggle Flow ---
	if(button4pressed() == 1) {
		lcd_clear();
		mode = 5;       // Switch to Mode 5 (Manual Control)
		++modecase5; // Toggle traffic direction logic
		temp_flag = 1;  // Trigger LCD update
		if(modecase5 >= 3) modecase5 = 1; // Loop between state 1 and 2
	}
    // --- Button 1 Logic: Cycle through Modes 1 to 4 ---
	if(button1pressed() == 1) {
		++mode;
		if(mode >= 5) {
            mode = 1; // Wrap around from Mode 4 to Mode 1
        }
		flagforledblinky = 0; // Reset blink flag for new mode
		lcd_clear();
        // Load current time values into temporary variable for editing
		switch(mode) {
            case 2: {
                temp = red_time;
            }
            break;
            case 3: {
                temp = green_time;
            }
            break;
            case 4: {
                temp = yellow_time;
            }
            break;
            default: {}
            break;
		}
		status = 0; // Reset internal status
		modecase5 = 1; // Reset manual mode state
	}
	// --- Main State Machine based on Current Mode ---
	switch(mode) {
        case 0: {
            mode = 1; // Default to Mode 1 on startup
        }
        break;
        case 1: { // --- Mode 1: Automatic Operation ---
            // Safety Check: Ensure Red time = Green time + Yellow time
            if(red_time != green_time + yellow_time) {
                // Reset to default values if logic is invalid
                red_time = red_def;       // 5s
                green_time = green_def;   // 3s
                yellow_time = yellow_def; // 2s
            }
            automode(); // Run the automatic traffic light sequence
        }
        break;
        case 2: { // --- Mode 2: Adjust Red Light Duration ---
            ledblinky();    // Blink LEDs to indicate mode
            updateBuffer(); // Prepare data for LCD
            lcd_display();  // Show current temp value on LCD
            // Button 2: Increase duration (1 -> 99 -> 1)
            if(button2pressed() == 1) {
                ++temp;
                if(temp > 99) {
                    temp = 1;
                }
            }
            // Button 3: Save the adjusted value
            if(button3pressed() == 1) {
                red_time = temp;
            }
        }
        break;
        case 3: { // --- Mode 3: Adjust Green Light Duration ---
            ledblinky();
            updateBuffer();
            lcd_display();
            // Button 2: Increase duration (1 -> 99 -> 1)
            if(button2pressed() == 1) {
                ++temp;
                if(temp > 99) {
                    temp = 1;
                }
            }
            // Button 3: Save the adjusted value
            if(button3pressed() == 1) {
                green_time = temp;
            }
        }
        break;
        case 4: { // --- Mode 4: Adjust Yellow Light Duration ---
            ledblinky();
            updateBuffer();
            lcd_display();
            // Button 2: Increase duration (1 -> 99 -> 1)
            if(button2pressed() == 1) {
                ++temp;
                if(temp > 99) {
                    temp = 1;
                }
            }
            // Button 3: Save the adjusted value
            if(button3pressed() == 1) {
                yellow_time = temp;
            }
        }
        break;
        case 5: { // --- Mode 5: Manual Control ---
            switch(modecase5) {
                case 1: {
                    // State 1: Manual control configuration A (e.g., Lane 1 RED, Lane 2 GREEN)
                    HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, SET);
                    HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, SET);
                    HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, RESET);
                    HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, SET);

                    if(temp_flag == 1) {
                        // Update LCD info for manual state 1
                        lcd_goto_XY(0, 0);
                        lcd_send_string("RED");
                        lcd_goto_XY(1, 0);
                        lcd_send_string("GREEN");
                        temp_flag = 0;
                    }
                }
                break;
                case 2: {
                    // State 2: Manual control configuration B (e.g., Lane 1 GREEN, Lane 2 RED)
                    HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, RESET);
                    HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, SET);
                    HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, SET);
                    HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, SET);

                    if(temp_flag == 1) {
                        // Update LCD info for manual state 2
                        lcd_goto_XY(0, 0);
                        lcd_send_string("GREEN");
                        lcd_goto_XY(1, 0);
                        lcd_send_string("RED");
                        temp_flag = 0;
                    }
                }
                break;
                default: {}
                break;
            }
        }
        break;
        default: {}
        break;
	}
}