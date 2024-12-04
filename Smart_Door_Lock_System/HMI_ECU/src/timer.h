/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the Timer AVR driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* All three timer ID */
typedef enum
{
	TIMER_0,
	TIMER_1,
	TIMER_2
}Timer_ID_Type;

/* All prescaler available for F_CPU */
typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024,
	EXTERNAL_CLOCK_FALLING_EDGE,
	EXTERNAL_CLOCK_RISING_EDGE
}Timer_ClockType;

/* All timer mode */
typedef enum
{
	NORMAL,
	COMPARE = 2,
	FAST_PWM
}Timer_ModeType;

/* All available mode for OC pin (used in fast PWM mode) */
typedef enum
{
	DISCONNECTED,
	NON_INVETING_MODE = 2,
	INVETING_MODE
}Timer_OutputComparePin;

/* Configurations of Timer */
typedef struct
{
	uint16 timer_InitialValue;
	uint16 timer_compare_MatchValue; 			/* It will be used in compare mode only */
	Timer_ID_Type timer_ID;			 			/* Which timer will be used */
	Timer_ClockType timer_clock;	 			/* Select prescaler of F-CPU */
	Timer_ModeType timer_mode;		 			/* To select timer mode */
	Timer_OutputComparePin output_compare;		/* Mode for OC pin (used in fast PWM mode) */
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 *  Function to initialize the Timer driver.
 *  Setup timer ID,clock type and timer mode.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr);

/*
 * Description :
 *  Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID_Type timer_type);

/*
 * Description :
 *  Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type a_timer_ID );


#endif /* SRC_TIMER_H_ */
