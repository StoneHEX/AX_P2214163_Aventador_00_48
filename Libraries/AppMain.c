/*
 * AppMain.c
 *
 *  Created on: Jan 5, 2023
 *      Author: fil
 */

#include "main.h"

__attribute__ ((aligned (4)))	SystemTypeDef				System;


static void disable_mco(void)
{
	uint32_t	moder;
	moder = GPIOA->MODER;
	moder &= ~MCOMASK;  	// pin PA8(bits 17:16) as Input 	(00)
	GPIOA->MODER = moder;
}

static void enable_mco(void)
{
	uint32_t	moder;
	moder = GPIOA->MODER;
	moder &= ~MCOMASK;  	// pin PA8(bits 17:16) as Input 	(00)
	moder |= ALTMODE;
	GPIOA->MODER = moder;
}

void CarrierPowerOn(void)
{
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&OSC32K_TIMER, OSC32K_CHANNEL);
	System.led_flags |= LED_FLAGS_BOARD_ACTIVE;
	enable_mco();
}

void CarrierPowerOff(void)
{
	disable_mco();
	HAL_TIM_PWM_Stop(&OSC32K_TIMER, OSC32K_CHANNEL);
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_RESET);
	System.led_flags &= ~LED_FLAGS_BOARD_ACTIVE;
}

void BoardPowerOn(void)
{
	HAL_GPIO_WritePin(ON_5V_MODULE_GPIO_Port, ON_5V_MODULE_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(SLEEP_WAKE_GPIO_Port, SLEEP_WAKE_Pin,GPIO_PIN_SET);		//temporary for hw rev 0, external inverting mosfet
}

void BoardPowerOff(void)
{
	HAL_GPIO_WritePin(ON_5V_MODULE_GPIO_Port, ON_5V_MODULE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(SLEEP_WAKE_GPIO_Port, SLEEP_WAKE_Pin,GPIO_PIN_RESET);		//temporary for hw rev 0, external inverting mosfet
}

void App_Init(void)
{
	HAL_GPIO_WritePin(CARRIER_PWR_ENABLE_GPIO_Port, CARRIER_PWR_ENABLE_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);			//external inverting mosfet
	HAL_GPIO_WritePin(SLEEP_WAKE_GPIO_Port, SLEEP_WAKE_Pin,GPIO_PIN_RESET);		//temporary for hw rev 0,external inverting mosfet
	HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET); 	// active low
	HAL_TIM_Base_Start_IT(&TICK_TIMER);
}

uint8_t CheckTimer(void)
{
uint8_t	ret_val = 0;
	if (( System.tick_flags &TICK10ms_FLAG ) == TICK10ms_FLAG)
	{
		ret_val = 1;
		System.tick_flags &= ~TICK10ms_FLAG;
		System.tick1Sec_cntr++;
		if ( System.tick1Sec_cntr > 95 )
		{
			System.tick1Sec_cntr = 0;
			System.tick_flags |= TICK1Sec_FLAG;
		}
		if ( System.tick1Sec_cntr > 99 )
		{
			System.tick1Sec_cntr = 0;
			System.tick_flags |= TICK1Sec_FLAG;
		}

		if ((System.system_flags & CHECK_BOARD_RESET) == CHECK_BOARD_RESET)
		{
			if (( System.tick1Sec_cntr == 70 ) || ( System.tick1Sec_cntr == 90 ))
				HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_RESET);
			else
				HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET);
		}
		else
		{
			if ( System.tick1Sec_cntr >= 95 )
				HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_RESET);
			else
				HAL_GPIO_WritePin(SEQUENCER_ACTIVE_GPIO_Port, SEQUENCER_ACTIVE_Pin,GPIO_PIN_SET);
		}

	}
	return ret_val;
}

uint8_t	shdn_debounce = 0;

void App_Loop(void)
{
	if (CheckTimer() != 0 )
	{
		PowerStateMachine();
	}

	if ((System.system_flags & CHECK_BOARD_RESET) == CHECK_BOARD_RESET)
	{
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_SET)
		{
			CarrierPowerOn();
			if ( HAL_GPIO_ReadPin(SHUTDOWN_REQUEST__GPIO_Port, SHUTDOWN_REQUEST__Pin) == GPIO_PIN_RESET)
			{
				shdn_debounce++;
				if ( shdn_debounce > 10 )
				{
					CarrierPowerOff();
					BoardPowerOff();
				}
			}
			else
				shdn_debounce = 0;
		}
		else
		{
			CarrierPowerOff();
		}
	}
	else
		CarrierPowerOff();
}
