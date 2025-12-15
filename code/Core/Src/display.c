#include "display.h"
#include "i2c-lcd.h"
#include "global.h"

void lcd_display(){ //Hàm in ra lcd

	//In 2 số đầu của buffer
	lcd_goto_XY(0, 0);
	lcd_send_data(led_buffer[0] + '0');
	lcd_send_data(led_buffer[1] + '0');

	//In 2 số sau của buffer
	lcd_goto_XY(1, 0);
	lcd_send_data(led_buffer[2] + '0');
	lcd_send_data(led_buffer[3] + '0');
}


//Hàm update buffer theo từng mode

void updateBuffer(){

	switch(mode){
	case 1:



		break;
	case 2:

		led_buffer[1]=temp%10; //Lấy số hàng đơn vị
		led_buffer[0]=temp/10; //Lấy số hàng chục

		//Hiển thị mode: 02
		led_buffer[3]=2;
		led_buffer[2]=0;

		break;
	case 3:

		led_buffer[1]=temp%10; //Lấy số hàng đơn vị
		led_buffer[0]=temp/10;  //Lấy số hàng chục

		//Hiển thị mode: 03
		led_buffer[3]=3;
		led_buffer[2]=0;

		break;
	case 4:

		led_buffer[1]=temp%10; //Lấy số hàng đơn vị
		led_buffer[0]=temp/10; //Lấy số hàng chục

		//Hiển thị mode: 04
		led_buffer[3]=4;
		led_buffer[2]=0;

		break;
	default:
		break;
	}


}
