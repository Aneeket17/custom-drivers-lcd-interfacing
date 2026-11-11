#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f411xx_i2c_driver.h"

typedef enum 
{
  LCD_OK       = 0x00U,
  LCD_ERROR    = 0x01U,
  LCD_BUSY     = 0x02U,
  LCD_TIMEOUT  = 0x03U
} LCD_StatusTypeDef;

typedef struct
{
    I2C_HandleTypedef *i2c;
    uint16_t address;
    uint8_t backlight;
} LCD_HandleTypedef;

LCD_StatusTypeDef LCD_Init(LCD_HandleTypedef *lcd, I2C_HandleTypedef *i2c,
                           uint8_t address);
LCD_StatusTypeDef LCD_Clear(LCD_HandleTypedef *lcd);
LCD_StatusTypeDef LCD_SetCursor(LCD_HandleTypedef *lcd, uint8_t row,
                                uint8_t column);
LCD_StatusTypeDef LCD_Print(LCD_HandleTypedef *lcd, const char *text);
void LCD_DelayMs(uint32_t milliseconds);
#endif
