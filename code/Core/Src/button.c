#include "button.h"
#include "main.h"

struct inforbutton{
	int key1;
	int key2;
	int key3;
	int flag;
	int key4;
	int time;
};

struct inforbutton button1 = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, 0, NORMAL_STATE, 200};
struct inforbutton button2 = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, 0, NORMAL_STATE, 200};
struct inforbutton button3 = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, 0, NORMAL_STATE, 200};
struct inforbutton button4 = {NORMAL_STATE, NORMAL_STATE, NORMAL_STATE, 0, NORMAL_STATE, 200};

void getkeyinput1(){
	button1.key1 = button1.key2;
	button1.key2 = button1.key3;
	button1.key3 = HAL_GPIO_ReadPin(button1_GPIO_Port, button1_Pin);

	if(button1.key1 == button1.key2 && button1.key2 == button1.key3)
	{
		if(button1.key3 != button1.key4)
		{
			button1.key4 = button1.key3;
			if(button1.key3 == PRESSED_STATE)
			button1.flag = 1;
		}
		else{
			button1.time--;
			if(button1.time <= 0)
			{
				button1.time = 200;
				if(button1.key3 == PRESSED_STATE)
					button1.flag=1;
			}
		}
	}
}

void getkeyinput2(){
	button2.key1 = button2.key2;
	button2.key2 = button2.key3;
	button2.key3 = HAL_GPIO_ReadPin(button2_GPIO_Port, button2_Pin);

	if(button2.key1 == button2.key2 && button2.key2 == button2.key3)
	{
		if(button2.key3 != button2.key4)
		{
			button2.key4 = button2.key3;
			if(button2.key3 == PRESSED_STATE)
			button2.flag = 1;
		}
		else{
			button2.time--;
			if(button2.time <= 0)
			{
				button2.time = 200;
				if(button2.key3 == PRESSED_STATE)
				button2.flag=1;
			}
		}
	}
}

void getkeyinput3(){
	button3.key1 = button3.key2;
	button3.key2 = button3.key3;
	button3.key3 = HAL_GPIO_ReadPin(button3_GPIO_Port, button3_Pin);

	if(button3.key1 == button3.key2 && button3.key2 == button3.key3)
	{
		if(button3.key3 != button3.key4)
		{
			button3.key4 = button3.key3;
			if(button3.key3 == PRESSED_STATE)
			button3.flag = 1;
		}
		else{
			button3.time--;
			if(button3.time <= 0)
			{
				button3.time = 200;
				if(button3.key3 == PRESSED_STATE)
				button3.flag=1;
			}
		}
	}
}

void getkeyinput4(){
	button4.key1 = button4.key2;
	button4.key2 = button4.key3;
	button4.key3 = HAL_GPIO_ReadPin(button4_GPIO_Port, button4_Pin);

	if(button4.key1 == button4.key2 && button4.key2 == button4.key3)
	{
		if(button4.key3 != button4.key4)
		{
			button4.key4 = button4.key3;
			if(button4.key3 == PRESSED_STATE)
			button4.flag = 1;
		}
		else{
			button4.time--;
			if(button4.time <= 0)
			{
				button4.time = 200;
				if(button4.key3 == PRESSED_STATE)
				button4.flag=1;
			}
		}
	}
}

void getkeyinput(){
	getkeyinput1();
	getkeyinput2();
	getkeyinput3();
	getkeyinput4();
}

int button1pressed(){
	if(button1.flag == 1)
	{
		button1.flag=0;
		return 1;
	}
	else return 0;
}
int button2pressed(){
	if(button2.flag == 1)
	{
		button2.flag=0;
		return 1;
	}
	else return 0;
}
int button3pressed(){
	if(button3.flag == 1)
	{
		button3.flag=0;
		return 1;
	}
	else return 0;
}
int button4pressed(){
	if(button4.flag == 1)
	{
		button4.flag=0;
		return 1;
	}
	else return 0;
}
