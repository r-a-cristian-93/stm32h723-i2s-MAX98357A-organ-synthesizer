#include <stdint.h>
#include <led.h>
#include "stm32h7xx_hal.h"

#define GPIOE_MODER          *((volatile uint32_t *)0x58021000)
#define GPIOE_OTYPER         *((volatile uint32_t *)0x58021004)
#define GPIOE_OSPEEDR        *((volatile uint32_t *)0x58021008)
#define GPIOE_PUPDR          *((volatile uint32_t *)0x5802100C)
#define GPIOE_ODR            *((volatile uint32_t *)0x58021014)
#define GPIOE_RCC_AHB4ENR    *((volatile uint32_t *)0x580244E0)

void inline ledInit()
{
	GPIOE_RCC_AHB4ENR |= 1 << 4;
	GPIOE_MODER &= ~(3 << 6);  // Clear bits 6 and 7
	GPIOE_MODER |= (1 << 6);   // Set bit 6
	GPIOE_OTYPER &= ~(1 << 3);
	GPIOE_OSPEEDR |= (3 << 6);
	GPIOE_PUPDR &= ~(3 << 6);
}

void inline ledOn()
{
	GPIOE_ODR |= 1 << 3;
}

void inline ledOff()
{
	GPIOE_ODR &= ~(1 << 3);
}

void inline ledToggle()
{
	GPIOE_ODR ^= 1 << 3;
}

void inline ledBlink(uint32_t millis)
{
	static uint32_t tickStart = 0;
	uint32_t nowTicks = HAL_GetTick();

	if (nowTicks - tickStart > millis)
	{
		ledToggle();
		tickStart = nowTicks;
	}
}
