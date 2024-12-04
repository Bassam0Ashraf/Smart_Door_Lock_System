 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: header file for DC Motor driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/
#ifndef SRC_DC_MOTOR_H_
#define SRC_DC_MOTOR_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_IN1_PORT_ID                 	PORTD_ID
#define DC_MOTOR_IN1_PIN_ID                  	PIN6_ID

#define DC_MOTOR_IN2_PORT_ID                 	PORTD_ID
#define DC_MOTOR_IN2_PIN_ID                  	PIN7_ID

#define DC_MOTOR_ENABLE_PORT_ID                 PORTB_ID
#define DC_MOTOR_ENABLE_PIN_ID                  PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	STOP,CW,A_CW	// CW stand for Clockwise & A_CW stand for Anti-Clockwise.
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning.
 */
void DcMotor_Init(void);


/*
 * Description :
 * Function controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 * on the input duty cycle.
 */
void DcMotor_Rotate(DcMotor_State , uint8 speed);


#endif /* SRC_DC_MOTOR_H_ */
