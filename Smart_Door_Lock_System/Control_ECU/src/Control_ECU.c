/******************************************************************************
 *
 * Module: APPLICATION
 *
 * File Name: Control_ECU.c
 *
 * Description: Source file for the Application layer of the CONTROL ECU
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "Control_ECU.h"

/*******************************************************************************
 *                                  Definitions                                *
 *******************************************************************************/

#define M1_HMI_READY 		0x10
#define M2_CONTROL_READY 	0x20
#define Error_pass 			0x00
#define INITIALIZED_FLAG 	0x01
#define SAVE 				0x02
#define END_SAVING 			0x03
#define CHECK_PASS 			0x04
#define CONTINUE_PASS 		0x05
#define UNLOCK_DOOR 		0x06
#define PEOPLE_IN			0x07
#define PEOPLE_OUT			0x08

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint16 g_tick = 0;			// Variable to count the time.

/*******************************************************************************
 *                            FUNCTIONS DEFINITIONS                            *
 *******************************************************************************/

/* Function to calculate time */
void Calculate_time(void)
{
	g_tick ++;

}

/* Function to Receive password */
void Receive_Password(void)
{
	/* wait for ACK from HMI ECU to
	 * start save the password */
	while(UART_recieveByte()!= SAVE);
	uint8 pass,count_pass;
	for(count_pass=5; count_pass>0; count_pass--)
	{
		/* send ACK to HMI ECU that control ECU
		 * ready to receive password */
		UART_sendByte(M2_CONTROL_READY);
		pass = UART_recieveByte();
		EEPROM_writeByte((0x0311+count_pass), pass);
		_delay_ms(70);
	}
	/* Send ACK to HMI ECU to let him know that password
	 *saved successful */
	UART_sendByte(END_SAVING);
}

/* Function to check the password */
void Check_Password(const Timer_ConfigType * Config_Ptr)
{
	/* wait ACK from HMI ECU to
	 * start to check the password */
	while(UART_recieveByte()!= CHECK_PASS);

	/* Check password if it the same password of the system or not */
	uint8 pass=0,pass_saved=0,error,count_pass;
	for(count_pass=5; count_pass>0; count_pass--)
	{
		pass = UART_recieveByte();		// Receive password.

		EEPROM_readByte((0x0311+count_pass), &pass_saved);
		if(pass != pass_saved)			// Compare password it with system password.
		{
			/* Send ACK to HMI ECU that the password wrong */
			UART_sendByte(Error_pass);
		}
		else
		{
			/* Send ACK to HMI ECU that the password correct */
			UART_sendByte(CONTINUE_PASS);
		}
	}
	/* Receive number of wrong attempt from HMI ECU */
	error = UART_recieveByte();
	if(error < 3)
	{
		/* Check password again if was the password wrong for less 3 times */
		Check_Password(Config_Ptr);
	}
	else if(error == 3)
	{
		Timer_init(Config_Ptr);
		g_tick =0;					// Reset TIMER 1.
		while (g_tick != 60)		// wait 60 seconds.
		{
			/* Activate the buzzer */
			Buzzer_on();
		}
	}
}

/* Function to open door */
void Open_door(const Timer_ConfigType * Config_Ptr)
{
	/* wait ACK from HMI ECU to
	* start to unlock the door */
	while(UART_recieveByte()!= UNLOCK_DOOR);
	uint8 PIR_State = FALSE ;	// Variable to know the state of PIR sensor
	/* Initialize Timer 1 */
	Timer_init(Config_Ptr);


	/* Turn ON motor clockwise (opening door) */
	DcMotor_Rotate( CW , 100 );
	g_tick =0;					// Reset TIMER 1.
	while(g_tick != 15);		// wait 15 seconds.


	/* Turn OFF motor for 3 sec before closing */
	DcMotor_Rotate( STOP , 0 );
	g_tick =0;					// Reset TIMER 1.
	while(g_tick != 3);			// wait 3 seconds.


	/* Check PIR sensor*/
	PIR_State = PIR_getState();
	while(PIR_State)
	{
		/* Send ACK to HMI ECU that there are
		 * people entering through the door */
		UART_sendByte(PEOPLE_IN);
		PIR_State = PIR_getState();
		//UART_sendByte(PEOPLE_IN);
	}
	/* Send ACK to HMI ECU that there aren't
	 * people anymore entering through the door */
	UART_sendByte(PEOPLE_OUT);



	/* Turn ON motor Anti-clockwise (closing door) */
	DcMotor_Rotate( A_CW , 100 );
	g_tick =0;					// Reset TIMER 1.
	while(g_tick != 15);		// wait 15 seconds.


	/* Turn OFF motor (door closed) */
	DcMotor_Rotate( STOP , 0 );

}

/* Function main menu */
void Main_menu(const Timer_ConfigType * Config_Ptr)
{
	/* Call function Check_Password */
	Check_Password(Config_Ptr);

	if(UART_recieveByte() == 0)
	{
		if(UART_recieveByte() == '-')
		{
			/* Call function Check_Password */
			Receive_Password();
		}
		else
		{

			Open_door(Config_Ptr);
		}
	}

	else
	{
		Buzzer_off();
	}
}


/*******************************************************************************
 *                     		  Main Program                                     *
 *******************************************************************************/

int main(void)
{
	/* Initialize DC-motor driver */
	DcMotor_Init();

	/* Initialize PIR sensor driver */
	PIR_init();

	/* Initialize buzzer driver */
	Buzzer_init();

	/* Initialize UART driver */
	UART_ConfigType UART_Config={BIT_8 , DISABLE , BIT_1 , RATE_9600_bps};
	UART_init(&UART_Config);

	/* Initialize TWI (I2C) driver */
	TWI_ConfigType TWI_Config = {ADDRESS_1 , RATE_400_Kbps};
	EEPROM_init(& TWI_Config);

	/* Initialize TIMER 1 driver */
	SREG |= (1<<7);						// Enable global interrupt.
	Timer_ConfigType Timer_Config = {0, 3500, TIMER_1, F_CPU_1024, COMPARE, DISCONNECTED };
	Timer_setCallBack(Calculate_time, TIMER_1);

	/* wait ACK from HMI ECU that tell he is ready after
	 * finish all Initialization for drivers */
	while(UART_recieveByte()!= M1_HMI_READY);

	/* Receive first password for the system */
	Receive_Password();


	while(1)
	{

		Main_menu(& Timer_Config);

	}
	return 0;
}
