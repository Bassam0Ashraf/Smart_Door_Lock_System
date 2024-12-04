 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the Buzzer driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "gpio.h"
#include "buzzer.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void)
{
	/* Configure buzzer pin as OUTPUT pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID , BUZZER_PIN_ID , PIN_OUTPUT);

	/* Turn OFF buzzer */
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);
}


/*
 * Description :
 * Function activates the buzzer.
 */
void Buzzer_on(void)
{
	/* Turn ON buzzer */
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_HIGH);
}


/*
 * Description :
 * Function deactivates the buzzer.
 */
void Buzzer_off(void)
{
	/* Turn OFF buzzer */
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);

}
