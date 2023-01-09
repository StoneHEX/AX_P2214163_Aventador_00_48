/*
 * PowerStateMachine.h
 *
 *  Created on: Jan 5, 2023
 *      Author: fil
 */

#ifndef POWERSTATEMACHINE_H_
#define POWERSTATEMACHINE_H_

#define	BTN_POWER_ON_DELAY			5
#define	BTN_FORCE_POWER_OFF_DELAY	50
#define	EMERGENCY_POWER_OFF			80
#define	SM_POWER_STABILIZE			60

extern	void PowerStateMachine(void);


#endif /* POWERSTATEMACHINE_H_ */
