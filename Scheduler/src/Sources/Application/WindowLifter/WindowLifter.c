/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Implements a module that controls windows movement.     */
/* I have in this file a few function that help me implements Close, Open.    */
/* A states machine that helpe to move trough Automatic, Manual and Anti-Pinch*/
/* mode.                                                                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/07/2015  |                               | Mario Rivera     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */


/** Own headers */
#include "WindowLifter.h"
#include "typedefs.h"
#include "LED.h"
#include "Button.h"


/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

void Show_Leds( void );
void machine( void );
void Set_Direction( void );
void Set_Mode( void );

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

T_UBYTE rub_counter_Button_OK;
T_UBYTE rub_option_M_A;
T_UBYTE rub_Option_Direction;
T_UBYTE rub_start;

/* WORD RAM variables */
T_UWORD ruw_counter_M_A;
T_UWORD ruw_counter_Pinch;

/* LONG and STRUCTURE RAM variables */
Button B_OPEN,B_CLOSE,B_PINCH;

enum re_states
{
	MANUAL,
	AUTOMATIC,
	OPEN,
	CLOSED,
	STANDBY,
	PINCH
};

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
 void Task_1ms(void)
{
	if( rub_option_M_A == PINCH ){}
	else if( rub_counter_Button_OK )
	{
		if( B_OPEN.PushButton(B_OPEN.channel) ) 
		{
			ruw_counter_M_A++;
			rub_Option_Direction = OPEN;
			Led_ON(LED_OPEN);
			Led_OFF(LED_CLOSED);
		}
		else if( B_CLOSE.PushButton( B_CLOSE.channel) )
		{
			ruw_counter_M_A++;
			rub_Option_Direction = CLOSED;
			Led_ON(LED_CLOSED);
			Led_OFF(LED_OPEN);
		}
		else if( B_PINCH.PushButton(B_PINCH.channel) )
		{
			if( rub_Option_Direction == CLOSED )
			{
				ruw_counter_M_A = RESET_COUNTER;
				ruw_counter_Pinch = RESET_COUNTER;
				rub_option_M_A = PINCH;
				rub_Option_Direction = OPEN;
				Led_OFF(LED_CLOSED);
				Led_ON(LED_OPEN);
			}
		}
		else
			ruw_counter_M_A = RESET_COUNTER;
	}
	Set_Mode();
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_10ms	
 *  Description          : This function is call to check
 						   if was pressed a correct button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/

void Task_2P5ms(void)
{
	static T_UBYTE lub_Counter = 0;
    if( lub_Counter == 4 )
    {
    	rub_counter_Button_OK = 1;
    	lub_Counter = 0;	
    }
    else
    {
    	if( B_OPEN.PushButton(B_OPEN.channel) || B_CLOSE.PushButton( B_CLOSE.channel) || B_PINCH.PushButton( B_PINCH.channel) )
    	{
    		lub_Counter++;
    	}
		else
		{
			rub_counter_Button_OK = 0;
			lub_Counter = 0;
		}	
    }
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_10ms	
 *  Description          : This function is call when I need to know
 						   if was pressed a correct button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void Task_100ms_Machine(void )
{
	static T_UBYTE lub_Counter = RESET_COUNTER;
    
    lub_Counter++;
    
    if( lub_Counter == 10 )
    {
    	machine();
    	lub_Counter = RESET_COUNTER;	
    }
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Show_Leds	
 *  Description          : This function turn on or off a specific led.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation : YES
 **************************************************************/
void Show_Leds(void)
{
	if( rub_Option_Direction == OPEN )
			Led_OFF( rub_start );
	else if( rub_Option_Direction == CLOSED )
			Led_ON( rub_start );
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : machine	
 *  Description          : This function controls the mode that 
 						   the windows will move, Automatic, Manual
 						   Anti-Pinch or do not do anything(StandBy).
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void machine( void )
{
	switch( rub_option_M_A )
	{
		case MANUAL:
			Show_Leds();
			if( rub_counter_Button_OK )
				Set_Direction();
			else
				rub_option_M_A = STANDBY;
		break;
		case AUTOMATIC:
			Show_Leds();
			Set_Direction();
		break;
		case STANDBY:
		break;
		case PINCH:
			Show_Leds();
			Set_Direction();
			if( ruw_counter_Pinch >= _5000Mili )
				rub_option_M_A = STANDBY;	
		break;
		default:
		break;
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Direction	
 *  Description          : Indicate wich led has to off or on 
 						   and sets direction.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Set_Direction( void )
{

	if( rub_Option_Direction == OPEN )
	{
		if( rub_start < LED10 )
				rub_start++;
			else if( rub_start == LED10 )
			{
				rub_start = LED10;
				Led_OFF(LED_CLOSED);
				Led_OFF(LED_OPEN);
			}
	}
	else if( rub_Option_Direction == CLOSED )
	{
		if( rub_start > LED1)
				rub_start--;
			else if( rub_start == LED1 )
			{	
				rub_start = LED1;
				Led_OFF(LED_CLOSED);
				Led_OFF(LED_OPEN);
			}
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Mode	
 *  Description          : In this function I set a mode (Automatic, Anti-Pinch, Automatic or Manual
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation : YES
 **************************************************************/
void Set_Mode( void )
{
	if( rub_option_M_A == PINCH ){
		ruw_counter_Pinch++;
	}
	else
	{
		if( ruw_counter_M_A >= _10Mili && ruw_counter_M_A < _500Mili )
			rub_option_M_A = AUTOMATIC;
		else if( ruw_counter_M_A >= _500Mili )
		{
			rub_option_M_A = MANUAL;	
			Led_OFF(LED_CLOSED);
			Led_OFF(LED_OPEN);
		}
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : InitWindowLifter	
 *  Description          : This functions is called by the main.c
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void InitWindowLifter(void)//SchM_Background
{
	/*Initialize LEDS*/
	LED_Init(LED1);
	LED_Init(LED2);
	LED_Init(LED3);
	LED_Init(LED4);
	LED_Init(LED5);
	LED_Init(LED6);
	LED_Init(LED7);
	LED_Init(LED8);
	LED_Init(LED9);
	LED_Init(LED10);
	LED_Init(LED_CLOSED);
	LED_Init(LED_OPEN);
	
	/*Initialize Push buttons*/
	Button_Init(&B_OPEN,OPEN_PUSH);
	Button_Init(&B_CLOSE,CLOSED_PUSH);
	Button_Init(&B_PINCH,PINCH_PUSH);
	
	rub_start = LED1;
	rub_option_M_A = STANDBY;
	rub_counter_Button_OK = RESET_COUNTER;
	ruw_counter_M_A = RESET_COUNTER;
	Led_OFF(LED_CLOSED);
	Led_OFF(LED_OPEN);
}


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
