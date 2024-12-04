/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the Timer AVR driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "timer.h"
#include "avr/io.h" /* To use the Timer Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/interrupt.h>

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

/*The global variable used in callback operation*/
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                        Functions Definitions                                *
 *******************************************************************************/

/* TIMER 0 normal mode ISR */
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER 0 compare mode ISR */
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER 1 normal mode ISR */
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER 1 compare mode ISR */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER 2 normal mode ISR */
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER 2 compare mode ISR */
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/*
 * Description :
 *  Function to initialize the Timer driver.
 *  Setup timer ID,clock type and timer mode.
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	switch( Config_Ptr -> timer_ID )
	{

	/*******************************************************************************
	 *                                TIMER 0                                      *
	 *******************************************************************************/

	case TIMER_0 :

		/* Non-PWM mode FOC0 = 1 */
		TCCR0 |= ( 1 << FOC0 );

		/* Prescaler of F_CPU */
		TCCR0 = ( TCCR0 & 0xF8 ) | ( Config_Ptr -> timer_clock );	// (Prescaler) F8 = 1111 1000 (CS02,CS01,CS00)


		/* Normal mode (OVF) */
		if( Config_Ptr -> timer_mode == NORMAL )
		{
			/* To use normal mode (OVF) set these bits WGM01 and WGM00 by zero
			 * so we will leave it because as dataSheet initial value for all these bits zero. */

			/* Set initial value for TIMER 0 */
			TCNT0 = Config_Ptr -> timer_InitialValue;

			/* Enable TIMER0 Overflow Interrupt */
			TIMSK |= ( 1 << TOIE0 );
		}


		/* Compare mode (CTC) */
		else if ( Config_Ptr -> timer_mode == COMPARE )
		{
			/* Select compare mode (CTC) by set this bit WGM01 by one */
			TCCR0 |= ( 1 << WGM01 );

			/* Set initial value for TIMER 0 and compare value */
			TCNT0 = Config_Ptr -> timer_InitialValue;				// Initial value for TIMER 0.
			OCR0 = Config_Ptr -> timer_compare_MatchValue;			// Compare value for TIMER 0.

			/* Enable Timer 0 Compare Interrupt */
			TIMSK |= ( 1 << OCIE0 );
		}


		/* Fast PWM */
		else if( Config_Ptr -> timer_mode == FAST_PWM )
		{
			/* Select fast PWM mode by set these bits WGM00,WGM01 by one */
			TCCR0 |= ( 1 << WGM00 ) | ( 1 << WGM01 );

			/* Select mode of OC0 */
			TCCR0 = ( TCCR0 & 0xCF ) | ( (Config_Ptr -> output_compare) << 4 );	// (OC0) CF = 1100 1111 (COM01 , COM00)

			/* Set initial value for TIMER 0 and compare value */
			TCNT0 = Config_Ptr -> timer_InitialValue;				// Initial value for TIMER 0.
			OCR0 = Config_Ptr -> timer_compare_MatchValue;			// Compare value for TIMER 0.
		}
		break;

		/*******************************************************************************
		 *                                TIMER 1                                      *
		 *******************************************************************************/

	case TIMER_1 :

		/* Non-PWM mode FOC1A and FOC2A = 1 */
		TCCR1A = ( 1 << FOC1A ) | ( 1 << FOC1B );

		/* Prescaler of F_CPU */
		TCCR1B = ( TCCR1B & 0xF8 ) | ( Config_Ptr -> timer_clock );		// (Prescaler) F8 = 1111 1000 (CS02,CS01,CS00)


		/* Normal mode (OVF) */
		if( Config_Ptr -> timer_mode == NORMAL )
		{
			/* To use normal mode (OVF) set these bits WGM10,WGM11,WGM12 and WGM13 by zero
			 * so we will leave it because as dataSheet initial value for all these bits zero. */

			/* Set initial value for TIMER 1 */
			TCNT1 = Config_Ptr -> timer_InitialValue;

			/* Enable TIMER 1 Overflow Interrupt */
			TIMSK = ( 1 << TOIE1 );
		}


		/* Compare mode (CTC) */
		else if ( Config_Ptr -> timer_mode == COMPARE )
		{
			/* Select (mode number 4) compare mode (CTC) by set this bit WGM12 by one */
			TCCR1B |= ( 1 << WGM12 );


			/* Set initial value for TIMER 1 and compare value */
			TCNT1 = Config_Ptr -> timer_InitialValue;			// Initial value for TIMER 1.
			OCR1A = Config_Ptr -> timer_compare_MatchValue;		// Compare value for TIMER 1.

			/* Enable TIMER 1 Compare Interrupt */
			TIMSK = ( 1 << OCIE1A );
		}


		/* Fast PWM */
		else if ( Config_Ptr -> timer_mode == FAST_PWM )
		{
			/* We used (mode number 15) in dataSheet
			 * so we need to set these bits WGM10,WGM11,WGM12 and WGM13 by one. */
			TCCR1A |= ( 1 << WGM10 ) | ( 1 << WGM11 );
			TCCR1B |= ( 1 << WGM12 ) | ( 1 << WGM13 );

			/* Select mode of OC1A */
			TCCR1A  = ( TCCR1A & 0x3F ) | ( (Config_Ptr -> output_compare) << 6 );	// 3F = 0011 1111 (COM1A1,COM1A0)


			/* Set initial value for TIMER 1 and compare value */
			TCNT1 = Config_Ptr -> timer_InitialValue;			// Initial value for TIMER 1.
			OCR1A = Config_Ptr -> timer_compare_MatchValue;		// Compare value for TIMER 1.
		}

		break;

		/*******************************************************************************
		 *                                TIMER 2                                      *
		 *******************************************************************************/

	case TIMER_2 :

		/* Non-PWM mode FOC2 = 1 */
		TCCR2 |= ( 1 << FOC2 );

		/* Prescaler of F_CPU */
		TCCR2 = ( TCCR2 & 0xF8 ) | ( Config_Ptr -> timer_clock );	// (Prescaler) F8 = 1111 1000 (CS02,CS01,CS00)


		/* Normal mode (OVF) */
		if( Config_Ptr -> timer_mode == NORMAL )
		{
			/* To use normal mode (OVF) set these bits WGM21 and WGM20 by zero
			 * so we will leave it because as dataSheet initial value for all these bits zero. */

			/* Set initial value for TIMER 2 */
			TCNT2  = Config_Ptr -> timer_InitialValue;

			/* Enable TIMER 2 Overflow Interrupt */
			TIMSK |= ( 1 << TOIE2 );
		}


		/* Compare mode (CTC) */
		else if ( Config_Ptr -> timer_mode == COMPARE )
		{
			/* Select compare mode (CTC) by set this bit WGM21 by one */
			TCCR0 |= ( 1 << WGM21 );

			/* Set initial value for TIMER 2 and compare value */
			TCNT2 = Config_Ptr -> timer_InitialValue;				// Initial value for TIMER 2.
			OCR2  = Config_Ptr -> timer_compare_MatchValue;			// Compare value for TIMER 2.

			/* Enable Timer 2 Compare Interrupt */
			TIMSK |= ( 1 << OCIE2 );
		}


		/* Fast PWM */
		else if( Config_Ptr -> timer_mode == FAST_PWM )
		{
			/* Select fast PWM mode by set these bits WGM20,WGM21 by one */
			TCCR2 |= ( 1 << WGM20 ) | ( 1 << WGM21 );

			/* Select mode of OC2 */
			TCCR2 = ( TCCR2 & 0xCF ) | ( (Config_Ptr -> output_compare) << 4 );	// (OC2) CF = 1100 1111 (COM01 , COM00)

			/* Set initial value for TIMER 2 and compare value */
			TCNT2 = Config_Ptr -> timer_InitialValue;				// Initial value for TIMER 2.
			OCR2  = Config_Ptr -> timer_compare_MatchValue;			// Compare value for TIMER 2.
		}

		break;
	}
}



/*
 * Description :
 *  Function to disable the Timer via Timer_ID.
 */
void Timer_deInit(Timer_ID_Type timer_ID)
{
	switch( timer_ID )
	{
	case TIMER_0 :

		/* Clear all TIMER 0 registers */
		TCCR0 = TCNT0 = OCR0 = TIMSK = 0;
		break;

	case TIMER_1 :

		/* Clear all TIMER 1 registers */
		TCCR1A = TCCR1B = TIMSK = TCNT1 = OCR1A = 0;
		break;

	case TIMER_2 :

		/* Clear all TIMER 2 registers */
		TCCR2 = TCNT2 = OCR2 = TIMSK = 0;
		break;
	}
}


/*
 * Description :
 *  Function to set the Call Back function address to the required Timer.
 */
void Timer_setCallBack(void(*a_ptr)(void), Timer_ID_Type timer_ID )
{
	switch( timer_ID )
	{
	case TIMER_0 :

		/* Save the address of the Call back function in a global variable */
		g_callBackPtr = (volatile void (*)(void))a_ptr;
		break;

	case TIMER_1 :

		/* Save the address of the Call back function in a global variable */
		g_callBackPtr = (volatile void (*)(void))a_ptr;
		break;

	case TIMER_2 :

		/* Save the address of the Call back function in a global variable */
		g_callBackPtr = (volatile void (*)(void))a_ptr;
		break;
	}

}
