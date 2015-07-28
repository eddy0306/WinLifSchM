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
/*  3.0      | 24/07/2015  |                               | Mario Rivera     */
/*	It has been implemeted misra.											  */
/*  Implements when anti-pinch mode is detected only when the movement is CLOSE*/
/*============================================================================*/

/* Includes */


/** Own headers */
#include "WindowLifter.h"
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
 *							Check when anti-pinch is pressed and validate it.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
 void Button_Management_2P5ms(void)
{
	if( rub_option_M_A == (T_UBYTE)PINCH ){}
	else if( rub_counter_Button_OK )
	{
		/*Check if there's buttons combination between*/
		if( B_CLOSE.PushButton( B_CLOSE.channel) == (T_UBYTE)PRESSED && (B_OPEN.PushButton(B_OPEN.channel) == (T_UBYTE)PRESSED ))
		{
			ruw_counter_M_A = (T_UWORD)RESET_COUNTER;
			rub_Option_Direction = (T_UBYTE)STANDBY;
		}
		else if( B_OPEN.PushButton(B_OPEN.channel) == (T_UBYTE)PRESSED && (Anti_Pinch(B_PINCH,rub_Option_Direction )  == ANTI_PINCH_OK ))
		{
			/*Continue open the window. Do nothing and keeps down the window*/ 
			Indicator_Open( rub_start );
			ruw_counter_M_A++;/*counter to check mode(Automatic or Manual)*/
			rub_Option_Direction = (T_UBYTE)OPEN;
		}
		else if( (B_OPEN.PushButton(B_OPEN.channel)==(T_UBYTE)PRESSED) || (rub_Option_Direction == OPEN )) 
		{
			Indicator_Open( rub_start );
			ruw_counter_M_A++;/*counter to check mode(Automatic or Manual)*/
			rub_Option_Direction = (T_UBYTE)OPEN;	
		}
		else if( B_CLOSE.PushButton( B_CLOSE.channel)==(T_UBYTE)PRESSED && Anti_Pinch(B_PINCH,rub_Option_Direction)  != ANTI_PINCH_OK )
		{
			Indicator_Close( rub_start );
			ruw_counter_M_A++;/*counter to check mode(Automatic or Manual)*/
			rub_Option_Direction = (T_UBYTE)CLOSED;
		}
		else if( Anti_Pinch(B_PINCH,rub_Option_Direction )  == ANTI_PINCH_OK && rub_Option_Direction != OPEN )
		{
			ruw_counter_M_A = (T_UWORD)RESET_COUNTER;/*Reset counter mode*/
			ruw_counter_Pinch = (T_UWORD)RESET_COUNTER;/*Reset counter anti-pinch*/
			rub_option_M_A = (T_UBYTE)PINCH;/*Set state Pinch*/
			rub_Option_Direction = (T_UBYTE)OPEN;/*Set movement direction*/
		}
		else
		{
			ruw_counter_M_A = (T_UWORD)RESET_COUNTER;	
		}
	}
	else
	{
		/*Do nothing*/
	}
	Set_Mode();
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Check_Button_OK_2P5ms	
 *  Description          : This function is call to check
 *						   if any button is pressed and keeps pressed 
 *						   to send a valid button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/

void Check_Button_OK_2P5ms(void)
{   
    static T_UBYTE lub_Counter = (T_UBYTE)RESET_COUNTER;
	if( B_OPEN.PushButton(B_OPEN.channel) == (T_UBYTE)PRESSED || 
    		B_CLOSE.PushButton( B_CLOSE.channel) == (T_UBYTE)PRESSED || 
    		B_PINCH.PushButton( B_PINCH.channel) == (T_UBYTE)PRESSED )
    {
    		lub_Counter++;
    		if( lub_Counter ==  (T_UBYTE)CONFIGURATION_BUTTON_OK )
    		{
    			rub_counter_Button_OK = (T_UBYTE)BUTTON_OK;
    		}
    		else
    		{
		   		/*Do nothing*/
    		}
    }
	else
	{
		rub_counter_Button_OK = (T_UBYTE)RESET_COUNTER;
		lub_Counter = (T_UBYTE)RESET_COUNTER;
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Machine_Call_100ms	
 *  Description          : This function call windowLifter machine
 *						   each 400ms. There's a local counter
 +						   to check the condition is reached
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void Machine_Call_100ms(void )
{
	static T_UBYTE lub_Counter = (T_UBYTE)RESET_COUNTER;
    lub_Counter++;
    
    if( lub_Counter == (T_UBYTE)CONFIGURATION_TRANSITION )
    {
    	States_machine_WindowLifter();
    	lub_Counter = (T_UBYTE)RESET_COUNTER;	
    }
    
    else
    {
    	/*Do nothing*/
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
			/*State idle*/
			Indicator_StandBy();
		break;
		case AUTOMATIC:
			/*Move the window*/
			Window_movement(rub_Option_Direction,rub_start);
			/*Set the new direction*/
			Set_Direction();/*Check wich movement is(close or open)*/
		break;
		case MANUAL:
			/*Move the window*/
			Window_movement(rub_Option_Direction,rub_start);
			/*Button pressed is ok*/
			if( rub_counter_Button_OK )
			{
				Set_Direction();	
			}
			else
			{
				rub_option_M_A = (T_UBYTE)STANDBY;
				ruw_counter_M_A = (T_UWORD)RESET_COUNTER;
				rub_Option_Direction = (T_UBYTE)STANDBY;
			}
		break;
		case PINCH:
			/*Move the window*/
			Window_movement(rub_Option_Direction,rub_start);
			/*Set the new direction*/
			Set_Direction();
			if( ruw_counter_Pinch >= (T_UWORD)_5000Mili )
			{
				rub_option_M_A = (T_UBYTE)STANDBY;		
			}
			else
			{
				/*Do nothing*/
			}
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
void Set_Direction( void )
{
	if( rub_Option_Direction == (T_UBYTE)OPEN )
	{
		/*The movement is not finish in open*/
		if( rub_start < (T_UBYTE)TOP_LEVEL )
		{
			rub_start++;	
		}
		/*The movement is finish in open*/
		else if( rub_start == (T_UBYTE)TOP_LEVEL )
		{
			ruw_counter_M_A = (T_UWORD)RESET_COUNTER;
			rub_Option_Direction = (T_UBYTE)STANDBY;
			rub_start = (T_UBYTE)TOP_LEVEL;
			Indicator_StandBy();
		}
		else
		{
			/*Do nothing*/
		}
	}
	else if( rub_Option_Direction == (T_UBYTE)CLOSED )
	{
		/*The movement is not finish in close*/
		if( rub_start > (T_UBYTE)LOW_LEVEL)
		{
			rub_start--;	
		}
		/*The movement is finish in close*/
		else if( rub_start == (T_UBYTE)LOW_LEVEL )
		{	
			ruw_counter_M_A = (T_UWORD)RESET_COUNTER;  
			rub_Option_Direction = (T_UBYTE)STANDBY;
			rub_start = (T_UBYTE)LOW_LEVEL;
			Indicator_StandBy();
		}
		else
		{
			/*Do nothing*/
		}
	}
	else
	{
		/*Do nothing*/
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Mode	
 *  Description          : In this function sets mode Automatic, Anti-Pinch or Manual
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation : YES
 **************************************************************/
void Set_Mode( void )
{
	/*If the movement option is anti-pinch sum the counter anti-pinch*/
	if( rub_option_M_A == (T_UBYTE)PINCH ){
		ruw_counter_Pinch++;
	}
	else
	{
		/*Check counter button is between 10ms and 500ms to set automatic mode*/
		if( ruw_counter_M_A >= (T_UWORD)_10Mili && ruw_counter_M_A < (T_UWORD)_500Mili )
		{
			rub_option_M_A = (T_UBYTE)AUTOMATIC;	
		}
		/*Check counter button is more than 500ms and set manual mode*/
		else if( ruw_counter_M_A >= (T_UWORD)_500Mili )
		{
			rub_option_M_A = (T_UBYTE)MANUAL;	
		}
		/*Stop the movement*/ 
		else
		{
			rub_option_M_A = (T_UBYTE)STANDBY;	
		} 
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
	Button_Init(&B_OPEN,(T_UBYTE)OPEN_PUSH);
	Button_Init(&B_CLOSE,(T_UBYTE)CLOSED_PUSH);
	Button_Init(&B_PINCH,(T_UBYTE)PINCH_PUSH);
	/*Initialize globals window lifter variables*/
	rub_start = (T_UBYTE)LOW_LEVEL;
	rub_option_M_A = (T_UBYTE)STANDBY;
	rub_Option_Direction = (T_UBYTE)STANDBY;
	rub_counter_Button_OK = (T_UBYTE)RESET_COUNTER;
	ruw_counter_M_A = (T_UWORD)RESET_COUNTER;
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
