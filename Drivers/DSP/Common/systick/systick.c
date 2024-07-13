/* Use systick timer to delay */
#include "systick.h"

//#define SYSCLK 72 // Match MCU System clock 72M
#define SYSTICK_LOAD (SystemCoreClock/1000000U)

/**
 * @brief  Microsecond delay
 * @param  Delay specifies the delay time length, in microseconds.
 * @retval None
 */
void Delay_us(uint32_t Delay) {
	if (Delay > 0) {
		SysTick->LOAD = SYSTICK_LOAD * Delay;		 // Set systick reload value
		SysTick->VAL = 0x00;				  // Set SysTick Current Value to 0
		SysTick->CTRL = 0x00000005;	// Set SysTick clock source to use processor clock and enable timer
		while (!(SysTick->CTRL & 0x00010000)) // Wait for the timer to count to 0
		{
		}
//		SysTick->CTRL = 0x00000004; // Disable timer
	}
}

/**
 * @brief  Millisecond delay
 * @param  Delay specifies the delay time length, in milliseconds.
 * @retval None
 */
void Delay_ms(uint32_t Delay) {
	if (Delay > 0) {
		while (Delay--) {
			Delay_us(1000);
		}
	}
}

/**
 * @brief  Second delay
 * @param  Delay specifies the delay time length, in seconds.
 * @retval None
 */
void Delay_s(uint32_t Delay) {
	if (Delay > 0) {
		while (Delay--) {
			Delay_ms(1000);
		}
	}
}
