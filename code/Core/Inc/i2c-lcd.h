#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

#include "stm32f1xx_hal.h"   // Đổi theo dòng STM32 của bạn

extern I2C_HandleTypeDef hi2c1;  // I2C bạn dùng trong CubeMX

#define LCD_ADDR (0x21 << 1)  // thay 0x27 bằng địa chỉ PCF8574 của bạn

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_clear(void);
void lcd_goto_XY(uint8_t row, uint8_t col);

#endif /* INC_I2C_LCD_H_ */
