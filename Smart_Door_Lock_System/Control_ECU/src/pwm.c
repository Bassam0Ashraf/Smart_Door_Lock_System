 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the PWM driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the Timer Registers */
#include "pwm.h"
#include "gpio.h"
#include "timer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the PWM driver.
 */
void PWM_TIMER0_Initial(uint8 duty_cycle)
{
	/* Configure PB3/OC0 Pin as OUTPUT pin */
	GPIO_setupPinDirection(PORTB , PINB3 , PIN_OUTPUT);

	/* Configure which timer we will in PWM mode */
	Timer_ConfigType Timer_Configration = {0, ( duty_cycle * (TIMER0_MAX_STEPS/100) ), TIMER_0, F_CPU_64, FAST_PWM, NON_INVETING_MODE };
	Timer_init(&Timer_Configration);
}
