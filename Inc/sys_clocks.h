/*
 * sys_clocks.h
 *
 *  Created on: Dec 18, 2024
 *      Author: mateu
 */

#ifndef SYS_CLOCKS_H_
#define SYS_CLOCKS_H_

void SystemClockHSI16(void);
uint32_t GetSystemTick(void);

// DELAY - WARNING! Blocking
void Delay(uint32_t Delay_ms);

#endif /* SYS_CLOCKS_H_ */
