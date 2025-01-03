/*
 * sys.clocks.c
 *
 *  Created on: Dec 18, 2024
 *      Author: mateu
 */
#include "main.h"
#include "sys_clocks.h"

__IO uint32_t Tick;

void SystemClockHSE8(void)
{
// HSE On
		RCC->CR |= RCC_CR_HSEON;
// Wait for HSE
		while (!(RCC->CR & RCC_CR_HSERDY));


// Set HSE
	    RCC->CFGR &= ~(RCC_CFGR_SW);        // Wyzeruj pole SW[1:0]
	    RCC->CFGR |= RCC_CFGR_SW_0;       // Ustaw SW[1:0] na 01 (HSE)

// Wait for HSE
	    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_0);


}

void SystemClockPLL48(void)
{

// HSE On
	    RCC->CR |= RCC_CR_HSEON;

// Wait for HSE
	    while (!(RCC->CR & RCC_CR_HSERDY));

// HSE as PLL Source
	    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
	    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

// FLASH: 1 wait states for 48 MHz
	    FLASH->ACR &= ~(FLASH_ACR_LATENCY);
	    FLASH->ACR |= FLASH_ACR_LATENCY_1WS;

// Dividers PLL
	    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP);

	    RCC->PLLCFGR |= (4 << RCC_PLLCFGR_PLLM_Pos); // PLLM = 4
	    RCC->PLLCFGR |= (96 << RCC_PLLCFGR_PLLN_Pos); // PLLN = 96
	    RCC->PLLCFGR |= (0 << RCC_PLLCFGR_PLLP_Pos); // PLLP = 2


// PLL ENABLE
	    RCC->CR |= RCC_CR_PLLON;
	    while (!(RCC->CR & RCC_CR_PLLRDY)); // Poczekaj, aż PLL będzie gotowe

	    RCC->CFGR &= ~(RCC_CFGR_HPRE);
	    RCC->CFGR |=  RCC_CFGR_HPRE_DIV2;
	    RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
	    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

// Set PLL
	    RCC->CFGR &= ~(RCC_CFGR_SW);        // Wyzeruj pole SW[1:0]
	    RCC->CFGR |= RCC_CFGR_SW_PLL;       // Ustaw SW[1:0] na 01 (PLL)

// Wait for PLL
	    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

}


void SystemClockHSI16(void)
{

//	SystemClockHSE8();
	SystemClockPLL48();

	SysTick_Config(48000000 / 1000);

}

void SysTick_Handler(void)
{
	Tick++;
}

uint32_t GetSystemTick(void)
{
	return Tick;
}

// DELAY - WARNING! Blocking
void Delay(uint32_t Delay_ms)
{
	uint32_t StartTime = Tick;
	while(Tick < (StartTime + Delay_ms))
	{
		// Just Wait
	}
}








