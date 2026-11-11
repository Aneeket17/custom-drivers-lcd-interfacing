# STM32F411 LCD and DHT11 Drivers

Bare-metal drivers for an HD44780-compatible character LCD with a PCF8574 I2C
expander, a DHT11 sensor, and STM32F411 general-purpose timers. The example
uses the LCD to report whether the DHT11 startup handshake succeeds. It does
not yet read or display temperature and humidity values.

[View the LCD and STM32 photo](./lcd-stm32.jpg).

## Hardware connections

### I2C LCD

| STM32F411 | Signal | LCD backpack |
|-----------|--------|--------------|
| PB6       | I2C1 SCL | SCL |
| PB7       | I2C1 SDA | SDA |
| GND       | Ground | GND |
| Suitable supply | Power | VCC |

PB6/PB7 use alternate function 4 and open-drain mode. The I2C bus needs
pull-ups; ensure the pull-up voltage is safe for the STM32 and connect grounds.
The example assumes the backpack's 7-bit address is `0x27`. Change
`LCD_I2C_ADDRESS` in `src/main.c` if needed.

### DHT11

| STM32F411 | DHT11 |
|-----------|-------|
| PA8       | DATA |
| Suitable supply | VCC |
| GND       | GND |

Use the required DATA pull-up for your sensor/module and ensure its logic
voltage is safe for the STM32 input.

## Timer configuration

The timer driver supports base-timer operations on TIM2-TIM5. This example
uses TIM2 as a free-running 32-bit counter at 1 MHz for DHT11 timing. It
assumes a 16 MHz TIM2 input clock (the reset HSI clock with APB1 prescaled by
1). Update `TimerClockHz` in `src/main.c` if the clock tree changes.

The LCD delay routine uses SysTick and separately assumes a 16 MHz system
clock.

## Build

Install CMake, Ninja, and the `arm-none-eabi` GCC toolchain. From the project
root, run:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake
cmake --build build
```

The firmware image is `build/custom-drivers-lcd-interfacing.elf`.
