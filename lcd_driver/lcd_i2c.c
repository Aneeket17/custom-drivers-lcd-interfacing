/*
This lcd library is designed to work with the I2C GPIO expander PCF8574* 
and compatible devices. It provides a simple interface for controlling an LCD 
display over I2C, allowing for easy integration into embedded systems.

PCF8574 pin mapping to LCD pins:
P0 -> RS        (LSB)
P1 -> RW
P2 -> E
P3 -> Backlight
P4 -> D4
P5 -> D5
P6 -> D6
P7 -> D7        (MSB)
*/

#include "lcd_i2c.h"
#include <stddef.h>

/* The project leaves the STM32F411 on its 16 MHz HSI reset clock. */
#define LCD_SYSCLK_HZ       16000000U
#define SYSTICK_BASEADDR    0xE000E010U
#define SYSTICK_CTRL_ENABLE (1U << 0)
#define SYSTICK_CTRL_CLKSOURCE (1U << 2)
#define SYSTICK_CTRL_COUNTFLAG (1U << 16)

typedef struct
{
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} LCD_SysTickRegDef;

#define LCD_SYSTICK ((LCD_SysTickRegDef *)SYSTICK_BASEADDR)

#define LCD_BACKLIGHT       0x08U
#define LCD_ENABLE          0x04U
#define LCD_REGISTER_SELECT 0x01U
#define LCD_I2C_TIMEOUT_MS  100U

static void LCD_DelayMs(uint32_t milliseconds)
{
    if (milliseconds == 0U)
    {
        return;
    }

    LCD_SYSTICK->LOAD = (LCD_SYSCLK_HZ / 1000U) - 1U;
    LCD_SYSTICK->VAL = 0U;
    LCD_SYSTICK->CTRL = SYSTICK_CTRL_ENABLE | SYSTICK_CTRL_CLKSOURCE;

    while (milliseconds > 0U)
    {
        while ((LCD_SYSTICK->CTRL & SYSTICK_CTRL_COUNTFLAG) == 0U)
        {
        }

        --milliseconds;
    }

    LCD_SYSTICK->CTRL = 0U;
}

static LCD_StatusTypeDef LCD_WriteExpander(LCD_HandleTypedef *lcd,
                                       uint8_t value)
{
    /* Send one output byte to the I2C GPIO expander. */
    // return I2C_MasterSendData(lcd->i2c, lcd->address, &value, 1U,
    //                                LCD_I2C_TIMEOUT_MS);
    return I2C_MasterSendData(lcd->i2c, &value, 1U, lcd->address, I2C_DISABLE_SR);
}

static LCD_StatusTypeDef LCD_WriteNibble(LCD_HandleTypedef *lcd,
                                      uint8_t nibble, uint8_t mode)
{
    /* Place the nibble on the upper data pins and preserve backlight/mode. */
    uint8_t value = (uint8_t)((nibble & 0xF0U) | lcd->backlight | mode);
    LCD_StatusTypeDef status = LCD_WriteExpander(lcd, value);

    if (status != LCD_OK)
    {
        return status;
    }

    /* Pulse Enable high, then low so the LCD latches this nibble. */
    status = LCD_WriteExpander(lcd, (uint8_t)(value | LCD_ENABLE));
    if (status != LCD_OK)
    {
        return status;
    }

    return LCD_WriteExpander(lcd, (uint8_t)(value & (uint8_t)~LCD_ENABLE));
}

static LCD_StatusTypeDef LCD_WriteByte(LCD_HandleTypedef *lcd, uint8_t value,
                                       uint8_t mode)
{
    /* In 4-bit mode, transmit the high nibble before the low nibble. */
    LCD_StatusTypeDef status = LCD_WriteNibble(lcd, value, mode);

    if (status != LCD_OK)
    {
        return status;
    }

    return LCD_WriteNibble(lcd, (uint8_t)(value << 4U), mode);
}

/*
Sends a command to the LCD, with special handling for clear and home commands that require extra execution time.
In 4 bit mode, the command is sent as two nibbles (high nibble first, then low nibble). The function returns LCD_OK if the command was sent successfully, or an error code if there was a problem with the I2C transmission.
*/
static LCD_StatusTypeDef LCD_WriteCommand(LCD_HandleTypedef *lcd,   
                                          uint8_t command)
{
    /* Send a command with RS low; clear/home need extra execution time. */
    LCD_StatusTypeDef status = LCD_WriteByte(lcd, command, 0U);

    if ((status == LCD_OK) && ((command == 0x01U) || (command == 0x02U)))
    {
        LCD_DelayMs(2U);
    }

    return status;
}

LCD_StatusTypeDef LCD_Init(LCD_HandleTypedef *lcd, I2C_HandleTypedef *i2c,
                           uint8_t address)
{
    LCD_StatusTypeDef status;

    /* Validate inputs and convert the 7-bit address to the HAL format. */
    if ((lcd == NULL) || (i2c == NULL) || (address > 0x7FU))
    {
        return LCD_ERROR;
    }

    lcd->i2c = i2c;
    lcd->address = (uint16_t)(address << 1U); // Shift left to match HAL I2C address format
    lcd->backlight = LCD_BACKLIGHT;

    /* Allow power-up to complete before entering the controller's 4-bit mode. */
    LCD_DelayMs(50U);

    /* Reset the LCD interface, then select 4-bit operation. */
    status = LCD_WriteNibble(lcd, 0x30U, 0U);
    if (status != LCD_OK)
    {
        return status;
    }
    LCD_DelayMs(5U);

    status = LCD_WriteNibble(lcd, 0x30U, 0U);
    if (status != LCD_OK)
    {
        return status;
    }
    LCD_DelayMs(1U);

    status = LCD_WriteNibble(lcd, 0x30U, 0U);
    if (status != LCD_OK)
    {
        return status;
    }

    status = LCD_WriteNibble(lcd, 0x20U, 0U);
    if (status != LCD_OK)
    {
        return status;
    }

    /* Configure two-line display, turn it off, clear it, and set entry mode. */
    status = LCD_WriteCommand(lcd, 0x28U);
    if (status != LCD_OK)
    {
        return status;
    }

    status = LCD_WriteCommand(lcd, 0x08U);
    if (status != LCD_OK)
    {
        return status;
    }

    status = LCD_Clear(lcd);
    if (status != LCD_OK)
    {
        return status;
    }

    status = LCD_WriteCommand(lcd, 0x06U);
    if (status != LCD_OK)
    {
        return status;
    }

    return LCD_WriteCommand(lcd, 0x0CU);
}

LCD_StatusTypeDef LCD_Clear(LCD_HandleTypedef *lcd)
{
    /* Reject an uninitialized handle before sending the clear-display command. */
    if ((lcd == NULL) || (lcd->i2c == NULL))
    {
        return LCD_ERROR;
    }

    return LCD_WriteCommand(lcd, 0x01U);
}

/*
For cursor positioning, the LCD controller uses DDRAM addresses that 
differ between the first and second lines. This function calculates the correct 
DDRAM address based on the specified row and column, then sends the 
corresponding command to the LCD. It returns LCD_OK if successful, or an error code 
if there was a problem with the I2C transmission or invalid coordinates.

To set the cursor at row 0, column 0, send row=0 and column=0. The command will be 0x80.
For row 1, column 0, the command is 0xC0.
*/
LCD_StatusTypeDef LCD_SetCursor(LCD_HandleTypedef *lcd, uint8_t row,
                                uint8_t column)
{
    /* DDRAM start addresses for the two rows of a standard 16x2 LCD. */
    static const uint8_t row_offsets[] = {0x00U, 0x40U};

    /* Validate the display coordinates before calculating the DDRAM address. */
    if ((lcd == NULL) || (lcd->i2c == NULL) || (row >= 2U) ||
        (column >= 16U))
    {
        return LCD_ERROR;
    }   

    return LCD_WriteCommand(lcd, (uint8_t)(0x80U | (row_offsets[row] + column)));
}

LCD_StatusTypeDef LCD_Print(LCD_HandleTypedef *lcd, const char *text)
{
    /* Data bytes use RS high; stop and return immediately on an I2C error. */
    if ((lcd == NULL) || (lcd->i2c == NULL) || (text == NULL))
    {
        return LCD_ERROR;
    }

    while (*text != '\0')
    {
        LCD_StatusTypeDef status =
            LCD_WriteByte(lcd, (uint8_t)*text, LCD_REGISTER_SELECT);

        if (status != LCD_OK)
        {
            return status;
        }
        ++text;
    }

    return LCD_OK;
}
