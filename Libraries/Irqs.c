/*
 * Irqs.c
 *
 *  Created on: Jan 5, 2023
 *      Author: fil
 */

#include "main.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if ( htim == &TICK_TIMER )
		System.tick_flags |= TICK10ms_FLAG;
}
