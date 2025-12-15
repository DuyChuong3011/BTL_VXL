#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

extern int mode; //Trạng thái của hệ thống

extern int red_time; //Thời gian đèn đỏ sáng
extern int green_time; //Thời gian đèn xanh sáng
extern int yellow_time; //Thời gian đèn vàng sáng

extern const int red_def; //Thời gian sáng đèn đỏ mặc định
extern const int green_def; //Thời gian sáng đèn xanh mặc định
extern const int yellow_def; //Thời gian sáng đèn vàng mặc định

extern int temp; //Biến tạm lưu số lần nhấn

extern int led_buffer[];

extern int status; //Trang thai của automode

extern int temp_red; //Biến tạm thời gian sáng đèn đỏ
extern int temp_green; //Biến tạm thời gian sáng đèn xanh
extern int temp_yellow; //Biến tạm thời gian sáng đèn vàng


#endif /* INC_GLOBAL_H_ */
