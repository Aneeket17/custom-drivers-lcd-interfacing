# STM32F411 I2C LCD

This project contains a bare-metal I2C driver and an LCD driver for an
HD44780-compatible character display connected through a PCF8574 I2C GPIO
expander. The example initializes a 16x2 LCD and displays:

```text
Hello, LCD!!
Custom drivers!
```
[View the LCD and STM32 photo](./lcd-stm32.jpg).

## Hardware

The example uses I2C1 on an STM32F411:

| STM32 pin | I2C signal | LCD backpack |
|-----------|------------|--------------|
| PB6       | I2C1_SCL   | SCL          |
| PB7       | I2C1_SDA   | SDA          |
| GND       | Ground     | GND          |
| 3.3 V or suitable supply | Power | VCC |

PB6 and PB7 are configured for alternate function 4 and open-drain operation.
The I2C bus requires pull-up resistors. Ensure the backpack's pull-up voltage
is safe for the STM32 pins, and connect the grounds together.

The example expects the LCD backpack's 7-bit I2C address to be `0x27`. If yours
is different, update `LCD_I2C_ADDRESS` in `src/main.c`.

## Build

Install CMake, Ninja, and the `arm-none-eabi` GCC toolchain, then run from the
project root:

```sh
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake
cmake --build build
```

The resulting firmware image is `build/custom-drivers-lcd-interfacing.elf`.

## Notes

- The LCD delay routine uses SysTick and currently assumes a 16 MHz system
  clock. Update the clock constant if the system clock configuration changes.
- Initialization and transfers use the project's custom drivers; the STM32 HAL
  is not required.
