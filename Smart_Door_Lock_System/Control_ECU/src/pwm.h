 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for PWM driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/
#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include "std_types.h"	// Standard data types.

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TIMER0_MAX_STEPS			256

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the PWM driver.
 */
void PWM_TIMER0_Initial(uint8 duty_cycle);

#endif /* SRC_PWM_H_ */
