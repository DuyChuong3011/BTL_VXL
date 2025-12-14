/*
 * software_timer.c
 *
 *  Created on: Dec 14, 2025
 *      Author: nguye
 */
#include "software_timer.h"
#include "main.h"

// --- Global Variables for Timer Counters ---
int timer_counter1 = 0;
int timer_counter2 = 0;
int timer_counter3 = 0;
int timer_counter4 = 0;
// timer_run() is called every 10ms
int timer_cycle = 10;
// --- Timer Flags (1 = Expired/Ready, 0 = Running/Idle) ---
int flag1 = 0;
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
// Setup Timer 1
void setTimer1(int n) {
    // Convert ms to ticks (e.g., 1000ms / 10ms = 100 ticks)
	timer_counter1 = n / timer_cycle;
	flag1 = 0; // Reset flag to indicate timer is running
}
// Setup Timer 2
void setTimer2(int n) {
	timer_counter2 = n / timer_cycle;
	flag2 = 0;
}
// Setup Timer 3
void setTimer3(int n) {
	timer_counter3 = n / timer_cycle;
	flag3 = 0;
}
// Setup Timer 4
void setTimer4(int n) {
	timer_counter4 = n / timer_cycle;
	flag4 = 0;
}
// Update logic for Timer 1
void timer_run1(){
	if(timer_counter1 > 0) {
		--timer_counter1; // Decrement tick
		if(timer_counter1 < 1) {
			flag1 = 1; // Timer expired, raise flag
		}
	}
}
// Update logic for Timer 2
void timer_run2() {
	if(timer_counter2 > 0) {
		--timer_counter2;
		if(timer_counter2 < 1) {
			flag2 = 1;
		}
	}
}
// Update logic for Timer 3
void timer_run3() {
	if(timer_counter3 > 0) {
		--timer_counter3;
		if(timer_counter3 < 1) {
			flag3 = 1;
		}
	}
}

// Update logic for Timer 4
void timer_run4() {
	if(timer_counter4 > 0) {
		--timer_counter4;
		if(timer_counter4 < 1) {
			flag4 = 1;
		}
	}
}
/**
 * @brief Master timer function.
 * This function should be called inside a hardware Timer Interrupt Service Routine (ISR)
 * (e.g., HAL_TIM_PeriodElapsedCallback) running every 'timer_cycle' ms (10ms).
 */
void timer_run() {
	timer_run1();
	timer_run2();
	timer_run3();
	timer_run4();
}