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
/*----------------------------------------------------------------------------*/
/*  2.0      | 22/07/2015  |                               | Mario Rivera     */
/*  Fix managment button  when occurs transition automatic to manual.         */
/*  Fix bugs when turn on led indicator close when te window is totally close.*/
/*  Fix bugs when turn on led indicator open when the window is totally open. */
/*  3.0      | 24/07/2015  |                               | Mario Rivera     */
/*  Fix managment button  combination. 								          */
/*  It has been implemented programming layer in window to make it independent.*/
/*============================================================================*/

/* Includes */


/** Own headers */
#include "WindowLifter.h"
#include "typedefs.h"
#include "Window.h"
#include "Button.h"
#include "Anti-Pinch.h"


/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */
void States_machine_WindowLifter( void );
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
	MANUAL = 0,
	AUTOMATIC = 1,
	STANDBY = 2,
	PINCH = 3,
	BLOCK = 4
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
 *  Name                 : Button_Management_1ms	
 *  Description          : This function controlls button. Check if
 *						   there's any push button and combination button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
 void Button_Management_1ms(void)
{
	if( rub_option_M_A == PINCH ){}
	else if( rub_counter_Button_OK )
	{
		/*Check if there's buttons combination */
		if( B_CLOSE.PushButton( B_CLOSE.channel) && B_OPEN.PushButton(B_OPEN.channel) )
		{
			ruw_counter_M_A = RESET_COUNTER;
		}
		else if( B_OPEN.PushButton(B_OPEN.channel) ) 
		{
			Indicator_Open( rub_start );
			ruw_counter_M_A++;/*counter to check mode(Automatic or Manual)*/
			rub_Option_Direction = OPEN;
		}
		else if( B_CLOSE.PushButton( B_CLOSE.channel) && Anti_Pinch(B_PINCH,rub_Option_Direction)  != ANTI_PINCH_OK )
		{
			Indicator_Close( rub_start );
			ruw_counter_M_A++;/*counter to check mode(Automatic or Manual)*/
			rub_Option_Direction = CLOSED;
		}
		else if( Anti_Pinch(B_PINCH,rub_Option_Direction )  == ANTI_PINCH_OK )
		{
			ruw_counter_M_A = RESET_COUNTER;/*Reset counter mode*/
			ruw_counter_Pinch = RESET_COUNTER;/*Reset counter anti-pinch*/
			rub_option_M_A = PINCH;/*Set state Pinch*/
			rub_Option_Direction = OPEN;/*Set movement direction*/
		}
		else
			ruw_counter_M_A = RESET_COUNTER;
	}
	Set_Mode();//call in tasks
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Check_Button_OK_2P5ms	
 *  Description          : This function is call to check
 *						   if any button is pressed and keeps pressed.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/

void Check_Button_OK_2P5ms(void)
{   
    static T_UBYTE lub_Counter = 0;
	if( B_OPEN.PushButton(B_OPEN.channel) || 
    		B_CLOSE.PushButton( B_CLOSE.channel) || 
    		B_PINCH.PushButton( B_PINCH.channel) )
    {
    		lub_Counter++;
    		if( lub_Counter == 4 )
    		{
    			rub_counter_Button_OK = 1;
    		}
    		else
    		{
		   /*Do nothing*/
    		}
    }
	else
	{
		rub_counter_Button_OK = 0;
		lub_Counter = 0;
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Machine_Call_100ms	
 *  Description          : This function call windowLifter machine
 *						   each 400ms.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void Machine_Call_100ms(void )
{
	static T_UBYTE lub_Counter = RESET_COUNTER;
    lub_Counter++;
    
    if( lub_Counter == 10 )
    {
    	States_machine_WindowLifter();
    	lub_Counter = RESET_COUNTER;	
    }
}

/* Inline functions */

/* ---------------- */
/**************************************************************
 *  Name                 : States_machine_WindowLifter	
 *  Description          : Check states and do actios for each state.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void States_machine_WindowLifter( void )
{
	switch( rub_option_M_A )
	{
		case STANDBY:
			Indicator_StandBy();
		break;
		case AUTOMATIC:
			Window_movement(rub_Option_Direction,rub_start);
			Set_Direction();//Check wich movement is(close or open)
		break;
		case MANUAL:
			Window_movement(rub_Option_Direction,rub_start);
			if( rub_counter_Button_OK )/*Button pressed is ok*/
				Set_Direction();
			else
			{
				rub_option_M_A = STANDBY;
				ruw_counter_M_A = RESET_COUNTER;
				rub_Option_Direction = STANDBY;
			}
		break;
		case PINCH:
			//Call antiPinch functionality
			Window_movement(rub_Option_Direction,rub_start);
			Set_Direction();
			if( ruw_counter_Pinch >= _5000Mili )
				rub_option_M_A = STANDBY;	
		break;
		case BLOCK:
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
 *  Critical/explanation :  YES
 **************************************************************/
void Set_Direction( void )//Direction movement
{
	if( rub_Option_Direction == OPEN )
	{
		if( rub_start < TOP_LEVEL )
				rub_start++;
		else if( rub_start == TOP_LEVEL )
		{
			rub_Option_Direction = STANDBY;
			rub_start = TOP_LEVEL;
			Indicator_StandBy();
		}
	}
	else if( rub_Option_Direction == CLOSED )
	{
		if( rub_start > LOW_LEVEL)
				rub_start--;
		else if( rub_start == LOW_LEVEL )
		{	
			rub_Option_Direction = STANDBY;
			rub_start = LOW_LEVEL;
			Indicator_StandBy();
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
		}
		else 
			rub_option_M_A = STANDBY;
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : InitWindowLifter	
 *  Description          : This functions is called by the main.c
 *						   to initialize windowlifter
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void InitWindowLifter(void)//SchM_Background
{
	/*Initialize window*/
	Init_Window();
	
	/*Initialize Push buttons*/
	Button_Init(&B_OPEN,OPEN_PUSH);
	Button_Init(&B_CLOSE,CLOSED_PUSH);
	Button_Init(&B_PINCH,PINCH_PUSH);
	
	rub_start = LOW_LEVEL;
	rub_option_M_A = STANDBY;
	rub_Option_Direction = CLOSED;
	rub_counter_Button_OK = RESET_COUNTER;
	ruw_counter_M_A = RESET_COUNTER;
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
