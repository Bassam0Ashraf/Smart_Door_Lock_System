/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir.c
 *
 * Description: Source file for PIR Sensor driver.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "gpio.h"
#include "pir.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the PIR pin direction and turn off the PIR.
 */
void PIR_init(void)
{
	/* Configure PIR pin as INPUT pin */
	GPIO_setupPinDirection(PIR_PORT_ID , PIR_PIN_ID , PIN_INPUT);
}


/*
 * Description :
 * Function return PIR State.
 */
uint8 PIR_getState(void)
{
	/* If PIR sensor detect the motion then function PIR_getState will return LOGIC_HIGH */
	return GPIO_readPin(PIR_PORT_ID , PIR_PIN_ID);
}
