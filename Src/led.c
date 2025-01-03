/*
 * led.c
 *
 *  Created on: Dec 19, 2024
 *      Author: mateu
 */
#include "main.h"
#include "led.h"

// LED2 LD2 on PA5
// 1 - On
// 0 - Off

void LED_LD2_Init(void)
{
	// LD2 on PA5
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;


//    // Ustaw PA5 jako wyjście
//    GPIOA->MODER &= ~(GPIO_MODER_MODE5); // Wyzeruj bity MODER5[1:0]
//    GPIOA->MODER |= GPIO_MODER_MODE5_0;  // Ustaw tryb wyjścia (01)

	GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	GPIOA->MODER |= GPIO_MODER_MODE5_0;

//	GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5); // After reset is ok

//	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);

//	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

__attribute__((always_inline)) inline void LED_LD2_On(void)
{
//	GPIOA->ODR |= GPIO_ODR_OD5;
	GPIOA->BSRR = GPIO_BSRR_BS5;
}

__attribute__((always_inline)) inline void LED_LD2_Off(void)
{
//	GPIOA->ODR |= ~(GPIO_ODR_OD5);
	GPIOA->BSRR = GPIO_BSRR_BR5;
}

__attribute__((always_inline)) inline void LED_LD2_Toggle(void)
{
	GPIOA->ODR ^= GPIO_ODR_OD5;
}
