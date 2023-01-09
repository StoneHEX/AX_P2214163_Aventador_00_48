/*
 * PowerStateMachine.c
 *
 *  Created on: Jan 5, 2023
 *      Author: fil
 */

#include "main.h"

void PowerStateMachine(void)
{
	switch(System.power_state_machine)
	{
	case	IDLE:
		HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
		System.buttons_delay = BTN_POWER_ON_DELAY;
		BoardPowerOff();
		CarrierPowerOff();
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_RESET)
			System.power_state_machine = CHECK_FOR_PWRON_PRESSED;
		break;
	case	CHECK_FOR_PWRON_PRESSED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_RESET)
		{
			if ( System.buttons_delay != 0 )
			{
				System.buttons_delay --;
				if ( System.buttons_delay == 0 )
				{
					System.power_state_machine = WAIT_POWER_STABILIZE;
					System.power_state_machine_delay = SM_POWER_STABILIZE;
					BoardPowerOn();
				}
			}
		}
		else
		{
			System.buttons_delay = BTN_POWER_ON_DELAY;
		}
		break;
	case	WAIT_POWER_STABILIZE:
		if ( System.power_state_machine_delay != 0 )
		{
			System.power_state_machine_delay --;
		}
		else
		{
			HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_RESET);
			System.power_state_machine = CHECK_FOR_SYS_RESET_HIGH;
			System.power_state_machine_delay = EMERGENCY_POWER_OFF;
		}
		break;
	case	CHECK_FOR_SYS_RESET_HIGH:
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_RESET)
		{
			if ( System.power_state_machine_delay != 0 )
			{
				System.power_state_machine_delay --;
			}
			else
			{
				// No reset arrived within EMERGENCY_POWER_OFF time, shutdown
				HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
				BoardPowerOff();
				System.power_state_machine = WAIT_FOR_PWRON_RELEASED;
			}
		}
		else
		{
			System.system_flags  |= CHECK_BOARD_RESET;
			System.power_state_machine = CHECK_FOR_PWRON_RELEASED;
		}
		break;
	case	CHECK_FOR_PWRON_RELEASED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_SET)
		{
			System.buttons_delay = BTN_FORCE_POWER_OFF_DELAY;
			System.power_state_machine = CHECK_FOR_BUTTONS;
		}
		break;
	case	CHECK_FOR_BUTTONS:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_RESET)
		{
			System.buttons_delay --;
			if ( System.buttons_delay == 0 )
			{
				/* User requested shutdown */
				System.system_flags  &= ~CHECK_BOARD_RESET;
				HAL_GPIO_WritePin(POWER_EN__GPIO_Port, POWER_EN__Pin,GPIO_PIN_SET);
				CarrierPowerOff();
				BoardPowerOff();
				System.power_state_machine = WAIT_FOR_PWRON_RELEASED;
			}
		}
		else
		{
			System.buttons_delay = BTN_FORCE_POWER_OFF_DELAY;
		}
		/* Reset low from board */
		if ( HAL_GPIO_ReadPin(SYS_RESET__GPIO_Port, SYS_RESET__Pin) == GPIO_PIN_RESET)
		{
			System.system_flags &= ~CHECK_BOARD_RESET;
			CarrierPowerOff();
			BoardPowerOff();
			System.power_state_machine = IDLE;
		}
		break;
	case	WAIT_FOR_PWRON_RELEASED:
		if ( HAL_GPIO_ReadPin(BRD_WAKE__GPIO_Port, BRD_WAKE__Pin) == GPIO_PIN_SET)
			System.power_state_machine = IDLE;
		break;
	default:
		System.power_state_machine = IDLE;
		break;
	}
}
