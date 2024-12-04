 /******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "gpio.h"
#include "dcmotor.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function initializes the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning.
 */
void DcMotor_Init(void)
{
	/* Configure pins of DC motor as OUTPUT */
	GPIO_setupPinDirection(DC_MOTOR_ENABLE_PORT_ID , DC_MOTOR_ENABLE_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID , DC_MOTOR_IN1_PIN_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID , DC_MOTOR_IN2_PIN_ID , PIN_OUTPUT);

	/* Stop the DC motor */
	GPIO_writePin(DC_MOTOR_IN1_PORT_ID , DC_MOTOR_IN1_PIN_ID , LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_IN2_PORT_ID , DC_MOTOR_IN2_PIN_ID , LOGIC_LOW);
}


/*
 * Description :
 * Function controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 * on the input duty cycle.
 */
void DcMotor_Rotate(DcMotor_State state , uint8 speed)
{
	PWM_TIMER0_Initial(speed);
	switch(state)
	{
	case STOP:
		/* Stop the DC motor */
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID , DC_MOTOR_IN1_PIN_ID , LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID , DC_MOTOR_IN2_PIN_ID , LOGIC_LOW);
		break;
	case CW:
		/* DC motor rotate Clock wise */
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID , DC_MOTOR_IN1_PIN_ID , LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID , DC_MOTOR_IN2_PIN_ID , LOGIC_HIGH);
		break;
	case A_CW:
		/* DC motor rotate anti-clock wise */
		GPIO_writePin(DC_MOTOR_IN1_PORT_ID , DC_MOTOR_IN1_PIN_ID , LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_IN2_PORT_ID , DC_MOTOR_IN2_PIN_ID , LOGIC_LOW);
		break;
	}
}
