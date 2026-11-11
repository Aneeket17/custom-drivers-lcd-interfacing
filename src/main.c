#include <string.h>

#include "lcd_i2c.h"
#include "dht11.h"
#include "stm32f411xx_gpio_driver.h"

#define LCD_I2C_ADDRESS 0x27U
#define GPIO_AF4_I2C    4U
#define DATA_PIN        8U

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

static void ConfigureDHT11Pin(GPIO_HandleTypedef *gpio, uint8_t pin)
{
	gpio->pGPIOx = GPIOA;
	gpio->GPIO_PinConfig.PinNumber = pin;
	gpio->GPIO_PinConfig.PinMode = GPIO_MODE_OUT;
	gpio->GPIO_PinConfig.PinOPType = GPIO_OUT_TYPE_PP;
	gpio->GPIO_PinConfig.PinSpeed = GPIO_SPEED_LOW;
	gpio->GPIO_PinConfig.PinPuPdControl = GPIO_PIN_NO_PUPD;

	GPIO_Init(gpio);
}

void I2C_ApplicationEventCallback(I2C_HandleTypedef *i2c, uint8_t event)
{
    (void)i2c;
    (void)event;
}

static I2C_StatusTypeDef LCD_I2C_Init(I2C_HandleTypedef *i2c)
{
    if (i2c == NULL)
    {
        return I2C_ERROR;
    }

    i2c->pI2Cx = I2C1;
    i2c->I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
    i2c->I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
    i2c->I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

    I2C_StatusTypeDef status = I2C_Init(i2c);
    if (status != I2C_OK)
    {
        return status;
    }

    I2C_PeripheralControl(i2c->pI2Cx, ENABLE);
    return I2C_OK;
}

int main(void)
{
    GPIO_HandleTypedef scl;
    GPIO_HandleTypedef sda;
	GPIO_HandleTypedef dht11;
    I2C_HandleTypedef i2c;
	TIM_HandleTypedef timer;
	LCD_HandleTypedef lcd;
    LCD_StatusTypeDef lcd_status;
	DHT11_StatusTypeDef dht11_status;

    memset(&scl, 0, sizeof(scl));
    memset(&sda, 0, sizeof(sda));
    memset(&i2c, 0, sizeof(i2c));
    memset(&timer, 0, sizeof(timer));
    memset(&lcd, 0, sizeof(lcd));
	memset(&dht11, 0, sizeof(dht11));

    ConfigureI2CPin(&scl, GPIO_PIN_6); /* PB6: I2C1_SCL */
    ConfigureI2CPin(&sda, GPIO_PIN_7); /* PB7: I2C1_SDA */
    ConfigureDHT11Pin(&dht11, DATA_PIN);

    if (LCD_I2C_Init(&i2c) != I2C_OK)
    {
        while (1)
        {
        }
    }

    lcd_status = LCD_Init(&lcd, &i2c, LCD_I2C_ADDRESS);
    if (lcd_status != LCD_OK)
    {
        while (1)
        {
        }
    }

    timer.pTIMx = TIM2;
    timer.Config.TimerClockHz = 16000000U;
    timer.Config.CounterFrequencyHz = 1000000U;
    timer.Config.Period = 0xFFFFFFFFU;
    if ((TIM_BaseInit(&timer) != TIM_OK) ||
        (TIM_Start(&timer) != TIM_OK))
    {
        while (1)
        {
        }
    }

    // lcd_status = LCD_SetCursor(&lcd, 0U, 0U);
    // if (lcd_status == LCD_OK)
    // {
    //     lcd_status = LCD_Print(&lcd, "Hello, LCD!!");
    // }
	// lcd_status = LCD_SetCursor(&lcd, 1U, 0U);
    // if (lcd_status == LCD_OK)
    // {
    //     lcd_status = LCD_Print(&lcd, "Custom drivers!");
    // }
    // if (lcd_status != LCD_OK)
    // {
    //     while (1)
    //     {
    //     }
    // }

	dht11_status = DHT11_Start(&dht11, &timer);
	if(dht11_status != DHT11_OK)
	{
		lcd_status = LCD_SetCursor(&lcd, 0U, 0U);
		if (lcd_status == LCD_OK)
		{
			lcd_status = LCD_Print(&lcd, "DHT11 Error!");
		}
		if (lcd_status != LCD_OK)
		{
			while (1)
			{
			}
		}
	}
	lcd_status = LCD_Print(&lcd, "DHT11 Intlzd!");
	if (lcd_status != LCD_OK)
	{
		while (1)
		{
		}
	}

    while (1)
    {
    }
}
