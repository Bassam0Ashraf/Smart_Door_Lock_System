 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for Buzzer driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#ifndef SRC_BUZZER_H_
#define SRC_BUZZER_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID                 PORTC_ID
#define BUZZER_PIN_ID                  PIN7_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the buzzer pin direction and turn off the buzzer.
 */
void Buzzer_init(void);


/*
 * Description :
 * Function activates the buzzer.
 */
void Buzzer_on(void);


/*
 * Description :
 * Function deactivates the buzzer.
 */
void Buzzer_off(void);


#endif /* SRC_BUZZER_H_ */
