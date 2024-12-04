/******************************************************************************
 *
 * Module: APPLICATION
 *
 * File Name: HMI_ECU.c
 *
 * Description: Source file for the Application layer of the HMI ECU
 *
 * Author: Bassam Ashraf
 *
 *******************************************************************************/

#include "HMI_ECU.h"

/*******************************************************************************
 *                                  Definitions                                *
 *******************************************************************************/

#define M1_HMI_READY		0x10
#define M2_CONTROL_READY 	0x20
#define Error_pass 			0x00
#define INITIALIZED_FLAG	0x01
#define SAVE 				0x02
#define END_SAVING 			0x03
#define CHECK_PASS 			0x04
#define UNLOCK_DOOR 		0x06
#define PEOPLE_IN			0x07

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint16 g_tick = 0;
uint8 g_counter_error =0;
uint8 g_return_flag=0;
uint8 g_people_status = 0;

/*******************************************************************************
 *                            FUNCTIONS DEFINITIONS                            *
 *******************************************************************************/

/* Function to calculate time */
void Calculate_time(void)
{
	g_tick++;
}


/* Function to create password */
void Create_Password()
{

	uint8 key = 0,pass=0,count_pass;

	sint32 new_pass = 0, re_pass = 0;

	/* First attempt to take password */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Enter Pass:");

	for(count_pass=0; count_pass<5; count_pass++)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(50);

		while(!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		LCD_displayStringRowColumn(1,count_pass,"*");
		_delay_ms(70);
		new_pass= new_pass*10 + key;
		_delay_ms(250);
	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Press =");
	while(key!='=')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(50);
	}

	/* Second attempt to take password */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Re-enter The");
	LCD_displayStringRowColumn(1,0,"Same Pass:");

	for(count_pass=0; count_pass<5; count_pass++)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(50);

		while(!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		LCD_displayStringRowColumn(1,count_pass+10,"*");
		_delay_ms(70);
		re_pass= re_pass*10 + key;
		_delay_ms(250);
	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Press =");
	while(key!='=')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(50);
	}


	if(re_pass == new_pass)
	{
		/* Send ACK to HMI ECU to know that we will
		 *start to save the new password */
		UART_sendByte(SAVE);
		for(count_pass=0;count_pass<5;count_pass++)
		{
			pass = re_pass % 10;
			/* wait ACK from control ECU that he is ready
			 * to receive password */
			while(UART_recieveByte()!= M2_CONTROL_READY);
			UART_sendByte(pass);
			re_pass /= 10;
		}

		/* Receive ACK from HMI ECU to know that password
		 *saved successful */
		while(UART_recieveByte()!= END_SAVING);
	}
	else
	{
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"NOT MATCHING");
		_delay_ms(500);
		/* start again to take password */
		Create_Password();
	}
}


/* Function to check the password */
void Check_Password(const Timer_ConfigType * Config_Ptr)
{
	sint32 pass=0;

	uint8 count_pass,key=0,pass_digit=0,error_pass=0;

	/* Attempt to take password to check if it match with
	 * the system password */
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Enter pass:");

	for(count_pass=0; count_pass<5; count_pass++)
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(50);

		while(!((key >= 0) && (key <= 9)))
		{
			key = KEYPAD_getPressedKey();
			_delay_ms(50);
		}
		LCD_displayStringRowColumn(1,count_pass,"*");
		_delay_ms(70);
		pass= pass*10 + key;
		_delay_ms(250);
	}
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Plz Press =");
	while(key!='=')
	{
		key=KEYPAD_getPressedKey();
		_delay_ms(50);
	}

	/* Send ACK to control ECU to
	 * start to check the password */
	UART_sendByte(CHECK_PASS);

	for(count_pass=0; count_pass<5; count_pass++)
	{
		pass_digit = pass % 10;
		UART_sendByte(pass_digit);

		/* Check if control ECU send ACK that password wrong */
		if(UART_recieveByte() == Error_pass)
		{
			error_pass ++;
		}
		pass /= 10;
	}

	if(error_pass != 0)
	{
		g_counter_error ++;
		UART_sendByte(g_counter_error);

		if(g_counter_error < 3)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"INCORRECT PASS");
			_delay_ms(500);
			Check_Password(Config_Ptr);
		}
		else
		{
			LCD_clearScreen();


			Timer_init(Config_Ptr);
			g_tick =0;					// Reset TIMER 1.
			while (g_tick != 60)		// wait 60 seconds.
			{
				LCD_displayStringRowColumn(0,0,"System LOCKED");
				LCD_displayStringRowColumn(1,0,"Wait for 1 min");
			}

			g_counter_error = 0;
			g_return_flag =1;
		}
	}
	else
	{
		UART_sendByte(4);
		g_counter_error = 0;
	}
}


/* Function to open door */
void Open_Door(const Timer_ConfigType * Config_Ptr)
{
	/* Send ACK to control ECU that we will start
	 * the prosses to unlock the door */
	UART_sendByte(UNLOCK_DOOR);

	LCD_clearScreen();
	Timer_init(Config_Ptr);
	g_tick =0;							// Reset TIMER 1.

	/* Display on LCD "opening door" */
	while(g_tick != 15)					// wait 15 seconds.
	{
		LCD_displayStringRowColumn(0,0,"Opening Door..");
	}

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Door Opened");
	g_tick =0;							// Reset TIMER 1.
	while(g_tick != 3);					// wait 3 seconds.


	/* wait ACK from control ECU to Check PIR sensor state */
	g_people_status = UART_recieveByte();

	if( g_people_status == PEOPLE_IN )
	{
		g_people_status = UART_recieveByte();
		/* Display on LCD "Wait for People to Enter" */
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "Wait for People");
		LCD_displayStringRowColumn(1, 3, "to Enter");
		g_people_status = UART_recieveByte();
		while( g_people_status == PEOPLE_IN )
		{
			/* Keep updating the PIR sensor state */
			g_people_status = UART_recieveByte();
		}

	}

	/* Display on LCD closing door */
	LCD_clearScreen();
	g_tick = 0;						// Reset TIMER 1.
	while(g_tick != 15)				// wait 15 seconds.
	{
		LCD_displayStringRowColumn(0,0,"Closing Door..");
	}
}


/* Function main menu */
void Main_menu(const Timer_ConfigType * Config_Ptr)
{
	uint8 key=0;				// Variable to take value of keypad button.

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");

	while((key != '+') && (key != '-'))
	{
		key = KEYPAD_getPressedKey();
		_delay_ms(50);
	}

	/* Check the password after press key '-' or '+' */
	Check_Password(Config_Ptr);
	UART_sendByte(g_return_flag);


	if(g_return_flag == 0)
	{
		UART_sendByte(key);
		if (key == '-')
		{
			/* Call function Create Password */
			Create_Password();

		}
		else
		{
			/* Call function Open Door */
			Open_Door(Config_Ptr);
		}
	}
	else
	{
		g_return_flag = 0;
	}

}


/*******************************************************************************
 *                     		  Main Program                                     *
 *******************************************************************************/

int main(void)
{

	/* Initialize LCD driver */
	LCD_init();

	/* Initialize UART driver */
	UART_ConfigType UART_Config={BIT_8 , DISABLE , BIT_1 , RATE_9600_bps};
	UART_init(&UART_Config);

	/* Initialize TIMER 1 driver */
	SREG |= (1<<7);						// Enable global interrupt.
	Timer_ConfigType Timer_Config = {0, 3500, TIMER_1, F_CPU_1024, COMPARE, DISCONNECTED };
	Timer_setCallBack(Calculate_time, TIMER_1);

	/* Send ACK to control ECU that HMI ECU ready after
	 * finish all Initialization for drivers */
	UART_sendByte(M1_HMI_READY);

	/* Create first password for the system */
	Create_Password();

	while(1)
	{

		Main_menu(& Timer_Config);

	}
	return 0;
}
