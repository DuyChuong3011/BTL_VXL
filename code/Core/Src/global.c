/*
 * global.c
 *
 *  Created on: Dec 7, 2025
 *      Author: nguye
 */


int mode=0; //Trạng thái của hệ thống

int red_time=5; //Thời gian đèn đỏ sáng
int green_time=3; //Thời gian đèn xanh sáng
int yellow_time=2; //Thời gian đèn vàng sáng

const int red_def=5; //Thời gian sáng đèn đỏ mặc định
const int green_def=3; //Thời gian sáng đèn xanh mặc định
const int yellow_def=2; //Thời gian sáng đèn vàng mặc định

int temp=0; //Biến tạm lưu số lần nhấn

int led_buffer[4]={0,0,0,0}; //Buffer dữ liệu in ra lcd

int status=0; //Trang thai của automode

int temp_red=0; //Biến tạm thời gian sáng đèn đỏ
int temp_green=0; //Biến tạm thời gian sáng đèn xanh
int temp_yellow=0; //Biến tạm thời gian sáng đèn vàng
