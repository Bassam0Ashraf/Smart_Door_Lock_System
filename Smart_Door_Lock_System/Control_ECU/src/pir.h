/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir.h
 *
 * Description: Source file for PIR Sensor driver.
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#ifndef SRC_PIR_H_
#define SRC_PIR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PIR_PORT_ID                 PORTC_ID
#define PIR_PIN_ID                  PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the PIR pin direction and turn off the PIR.
 */
void PIR_init(void);

/*
 * Description :
 * Function return PIR State.
 */
uint8 PIR_getState(void);

#endif /* SRC_PIR_H_ */
