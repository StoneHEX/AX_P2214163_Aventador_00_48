/*
 * AppMain.h
 *
 *  Created on: Jan 5, 2023
 *      Author: fil
 */

#ifndef APPMAIN_H_
#define APPMAIN_H_

extern	TIM_HandleTypeDef htim3;
extern	TIM_HandleTypeDef htim6;

#define	OSC32K_TIMER	htim3
#define	OSC32K_CHANNEL	TIM_CHANNEL_4
#define	TICK_TIMER		htim6

#define	MCOMASK		(3 << 16 )
#define	ALTMODE		(2 << 16 )
#define	MCOSHIFT	16

typedef struct _SystemTypeDef
{
	uint8_t			system_flags;
	uint8_t			tick_flags;
	uint8_t 		buttons_flags;
	uint8_t 		led_flags;
	uint16_t		tick100ms_cntr;
	uint16_t		tick1Sec_cntr;
	uint8_t			power_state_machine;
	uint8_t			power_state_machine_delay;
	uint8_t			buttons_delay;
}SystemTypeDef;

/* system_flags */
#define	ADC1_FLAG				0x01
#define	USB_FLAG				0x02
#define	CHECK_BOARD_RESET		0x04
// not used						0x08
// not used						0x10
// not used						0x20
// not used						0x40
#define	USB_PRINTED_FLAG		0x80

/* tick_flags */
#define	TICK1Sec_FLAG			0x01
#define	TICK100ms_FLAG			0x02
#define	TICK10ms_FLAG			0x04
// not used						0x08
// not used						0x10
// not used						0x20
// not used						0x40
// not used						0x80

/* buttons_flags */
// not used						0x01
// not used						0x02
// not used						0x04
// not used						0x08
// not used						0x10
#define	BUTTON_FLAGS_BOARD_REC	0x20
#define	BUTTON_FLAGS_BOARD_RST	0x40
#define	BUTTON_FLAGS_BOARD_WKE	0x80

/* led_flags */
// not used						0x01
// not used						0x02
// not used						0x04
// not used						0x08
// not used						0x10
// not used						0x20
// not used						0x40
#define	LED_FLAGS_BOARD_ACTIVE	0x80

enum POWER_STATE
{
	IDLE,
	CHECK_FOR_PWRON_PRESSED,
	WAIT_POWER_STABILIZE,
	CHECK_FOR_SYS_RESET_HIGH,
	CHECK_FOR_PWRON_RELEASED,
	CHECK_FOR_BUTTONS,
	WAIT_FOR_PWRON_RELEASED,
};

extern	SystemTypeDef	System;

extern	void App_Init(void);
extern	void App_Loop(void);
extern	void CarrierPowerOn(void);
extern	void CarrierPowerOff(void);
extern	void BoardPowerOn(void);
extern	void BoardPowerOff(void);

#endif /* APPMAIN_H_ */
