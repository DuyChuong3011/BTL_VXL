#include "i2c-lcd.h"

/**
 * @brief Low-level function to send data/commands to the LCD via I2C.
 * Handles splitting 8-bit data into two 4-bit nibbles (high and low).
 * @param data The byte (command or character) to send.
 * @param rs Register Select (0 for Command, 1 for Data).
 */
static void lcd_send(uint8_t data, uint8_t rs) {
    // Mask the upper 4 bits and lower 4 bits
    uint8_t data_u = data & 0xF0;          // Upper nibble
    uint8_t data_l = (data << 4) & 0xF0;   // Lower nibble
    uint8_t buf[4];
    // Prepare buffer with Backlight ON (Bit 3 usually) and Enable Pulse
    if (rs == 0) {
        // --- Sending Command (RS = 0) ---
        // Byte 0: Upper nibble + EN=1, RS=0, BL=1 (0x0C = 1100)
        buf[0] = data_u | 0x0C;
        // Byte 1: Upper nibble + EN=0, RS=0, BL=1 (0x08 = 1000) -> Latch data
        buf[1] = data_u | 0x08;
        // Byte 2: Lower nibble + EN=1, RS=0, BL=1
        buf[2] = data_l | 0x0C;
        // Byte 3: Lower nibble + EN=0, RS=0, BL=1 -> Latch data
        buf[3] = data_l | 0x08;
    }
    else {
        // --- Sending Data (RS = 1) ---
        // Byte 0: Upper nibble + EN=1, RS=1, BL=1 (0x0D = 1101)
        buf[0] = data_u | 0x0D;
        // Byte 1: Upper nibble + EN=0, RS=1, BL=1 (0x09 = 1001) -> Latch data
        buf[1] = data_u | 0x09;
        // Byte 2: Lower nibble + EN=1, RS=1, BL=1
        buf[2] = data_l | 0x0D;
        // Byte 3: Lower nibble + EN=0, RS=1, BL=1 -> Latch data
        buf[3] = data_l | 0x09;
    }
    // Transmit the 4-byte buffer to the LCD address via I2C
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, buf, 4, HAL_MAX_DELAY);
}
// Send a command byte to the LCD (RS = 0)
void lcd_send_cmd(char cmd) {
    lcd_send(cmd, 0);
}
// Send a data byte (character) to the LCD (RS = 1)
void lcd_send_data(char data) {
    lcd_send(data, 1);
}
/**
 * @brief Initialize the LCD in 4-bit mode.
 * Follows the standard HD44780 initialization sequence.
 */
void lcd_init(void) {
    HAL_Delay(50); // Wait for LCD to power up
    // Reset sequence (send 0x30 three times)
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    // Switch to 4-bit mode
    lcd_send_cmd(0x20); 
    HAL_Delay(5);
    // Function set: 4-bit mode, 2 lines, 5x8 font
    lcd_send_cmd(0x28);
    // Display control: Display ON, Cursor OFF, Blink OFF
    lcd_send_cmd(0x0C);
    // Entry mode: Increment cursor (move right), No display shift
    lcd_send_cmd(0x06);
    // Clear display
    lcd_send_cmd(0x01);
    HAL_Delay(5); // Wait for clear command to finish
}
// Print a string to the LCD at the current cursor position
void lcd_send_string(char *str) {
    while (*str) {
        lcd_send_data(*str++); // Send char and increment pointer
    }
}
// Clear the LCD screen and return cursor to home (0,0)
void lcd_clear(void) {
    lcd_send_cmd(0x01); // Command 0x01: Clear Display
    HAL_Delay(2);       // This command takes longer (~1.52ms)
}
/**
 * @brief Move the cursor to a specific row and column.
 * @param row Row index (0 or 1 for 16x2 LCD).
 * @param col Column index (0 to 15).
 */
void lcd_goto_XY(uint8_t row, uint8_t col) {
    // Base addresses for lines 1, 2, 3, 4
    // 0x80 = Line 1, 0xC0 = Line 2
    static uint8_t row_addr[] = {0x80, 0xC0, 0x94, 0xD4};
    // Send command to set DDRAM address
    lcd_send_cmd(row_addr[row] + col);
}