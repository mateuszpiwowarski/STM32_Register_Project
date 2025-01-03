/*
 * software_timers.c
 *
 *  Created on: Jan 2, 2025
 *      Author: mateu
 */

#include "main.h"
#include "sys_clocks.h"
#include "software_timers.h"

void SoftTimerEvent(SoftTimer_t *Timer)
{
	if((GetSystemTick() - Timer->LastTick) > Timer->TimeToDelay)
	{
			if(Timer->TimeToDelay)
			{
				Timer->LastTick = GetSystemTick();
				if(Timer->Action)
				{
					Timer->Action();
				}
			}
	}
}

void SoftTimerAction(SoftTimer_t *Timer, void (*_Action)(void))
{
	Timer->Action = _Action;
}

void SoftTimerStart(SoftTimer_t *Timer, uint32_t Delay)
{
	if(Delay != 0)
	{
		Timer->TimeToDelay = Delay;
		Timer->LastTick = GetSystemTick();
	}
}

void SoftTimerStop(SoftTimer_t *Timer)
{
	Timer->TimeToDelay = 0;
}
