/*
 * software_timers.h
 *
 *  Created on: Jan 2, 2025
 *      Author: mateu
 */

#ifndef SOFTWARE_TIMERS_H_
#define SOFTWARE_TIMERS_H_

typedef struct
{
	uint32_t TimeToDelay;
	uint32_t LastTick;
	void (*Action)(void);
} SoftTimer_t;

void SoftTimerEvent(SoftTimer_t *Timer);
void SoftTimerAction(SoftTimer_t *Timer, void (*Action)(void));
void SoftTimerStart(SoftTimer_t *Timer, uint32_t Delay);
void SoftTimerStop(SoftTimer_t *Timer);

#endif /* SOFTWARE_TIMERS_H_ */
