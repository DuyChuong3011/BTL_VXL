/*
 * auto.c
 *
 *  Created on: Dec 7, 2025
 *      Author: nguye
 */


#include "auto.h"
#include "software_timer.h"
#include "main.h"
#include "global.h"
#include "display.h"



void automode(){

	switch(status){
		case 0:
			temp_red=red_time;
			temp_green=green_time;
			temp_yellow=yellow_time;
			updateAutobuffer(temp_red, temp_green);
			setTimer3(1000);
			status=1;
			break;
		case 1: //RED1+GREEN2: GREEN_TIME
			lcd_display();


			HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, SET);
			HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, SET);

			HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, RESET);
			HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, SET);

			if(flag3 == 1){
				setTimer3(1000);
				temp_red-=1;
				temp_green-=1;
				updateAutobuffer(temp_red, temp_green);
			}

			if(temp_green <= 0){
				status = 2;
				temp_green=green_time;
				updateAutobuffer(temp_red, temp_yellow);
			}

			break;
		case 2: //RED1+YELLOW2: YELLOW_TIME
			lcd_display();
			HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, SET);
			HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, SET);

			HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, SET);
			HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, RESET);
			if(flag3 == 1){
				setTimer3(1000);
				temp_red-=1;
				temp_yellow-=1;
				updateAutobuffer(temp_red, temp_yellow);
			}

			if(temp_yellow <= 0 && temp_red <= 0){
				status = 3;
				temp_yellow=yellow_time; temp_red=red_time;
				updateAutobuffer(temp_green, temp_red);
			}

			break;
		case 3: //GREEN1+RED2: GREEN_TIME
			lcd_display();
			HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, RESET);
			HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, SET);

			HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, SET);
			HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, SET);

			if(flag3 == 1){
				setTimer3(1000);
				temp_red-=1;
				temp_green-=1;
				updateAutobuffer(temp_green, temp_red);
			}

			if(temp_green <= 0){
				status = 4;
				temp_green=green_time;
				updateAutobuffer(temp_yellow, temp_red);
			}

			break;
		case 4: //YELLOW1+RED2: YELLOW_TIME
			lcd_display();
			HAL_GPIO_WritePin(LED1A_GPIO_Port, LED1A_Pin, SET);
			HAL_GPIO_WritePin(LED1B_GPIO_Port, LED1B_Pin, RESET);

			HAL_GPIO_WritePin(LED2A_GPIO_Port, LED2A_Pin, SET);
			HAL_GPIO_WritePin(LED2B_GPIO_Port, LED2B_Pin, SET);

			if(flag3 == 1){
				setTimer3(1000);
				temp_red-=1;
				temp_yellow-=1;
				updateAutobuffer(temp_yellow, temp_red);
			}

			if(temp_yellow <= 0 && temp_red <= 0){
				status = 1;
				temp_yellow=yellow_time; temp_red=red_time;
				updateAutobuffer(temp_red, temp_green);
			}

			break;
		default:
			break;
	}


}


//Hàm update buffer của chế độ auto
void updateAutobuffer(int a, int b){
	led_buffer[0]=a/10; //Lấy số hàng chục của số a
	led_buffer[1]=a%10; //Lấy số hàng đơn vị của số a
	led_buffer[2]=b/10; //Lấy số hàng chục của số b
	led_buffer[3]=b%10; //Lấy số hàng đơn vị của số b
}
