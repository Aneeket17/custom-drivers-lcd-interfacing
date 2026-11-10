#include <string.h>

#include "lcd_i2c.h"
#include "stm32f411xx_gpio_driver.h"

#define LCD_I2C_ADDRESS 0x27U
#define GPIO_AF4_I2C    4U

static void ConfigureI2CPin(GPIO_HandleTypedef *gpio, uint8_t pin)
{
    gpio->pGPIOx = GPIOB;
    gpio->GPIO_PinConfig.PinNumber = pin;
    gpio->GPIO_PinConfig.PinMode = GPIO_MODE_ALTFN;
    gpio->GPIO_PinConfig.PinOPType = GPIO_OUT_TYPE_OD;
    gpio->GPIO_PinConfig.PinSpeed = GPIO_SPEED_HIGH;
    gpio->GPIO_PinConfig.PinPuPdControl = GPIO_PIN_PU;
    gpio->GPIO_PinConfig.PinAltFuncMode = GPIO_AF4_I2C;

    GPIO_Init(gpio);
}

void I2C_ApplicationEventCallback(I2C_HandleTypedef *i2c, uint8_t event)
{
    (void)i2c;
    (void)event;
}

int main(void)
{
    GPIO_HandleTypedef scl;
    GPIO_HandleTypedef sda;
    I2C_HandleTypedef i2c;
    LCD_HandleTypedef lcd;
    LCD_StatusTypeDef status;

    memset(&scl, 0, sizeof(scl));
    memset(&sda, 0, sizeof(sda));
    memset(&i2c, 0, sizeof(i2c));
    memset(&lcd, 0, sizeof(lcd));

    ConfigureI2CPin(&scl, GPIO_PIN_6); /* PB6: I2C1_SCL */
    ConfigureI2CPin(&sda, GPIO_PIN_7); /* PB7: I2C1_SDA */

    i2c.pI2Cx = I2C1;
    status = LCD_Init(&lcd, &i2c, LCD_I2C_ADDRESS);
    if (status != LCD_OK)
    {
        while (1)
        {
        }
    }

    status = LCD_SetCursor(&lcd, 0U, 0U);
    if (status == LCD_OK)
    {
        status = LCD_Print(&lcd, "Hello, LCD!!");
    }
	status = LCD_SetCursor(&lcd, 1U, 0U);
    if (status == LCD_OK)
    {
        status = LCD_Print(&lcd, "Custom drivers!");
    }

    if (status != LCD_OK)
    {
        while (1)
        {
        }
    }

    while (1)
    {
    }
}
