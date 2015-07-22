/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %Button.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  | 				               | Mario Rivera     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/** MCU derivative information */
#include "MCU_derivative.h"
#include "typedefs.h"
#include "Button.h"
#include "GPIO.h"


T_UBYTE Button_Pressed( T_UBYTE Channel );

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

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


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
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
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


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
 *  Name                 :	Button_Init
 *  Description          :	This function init chanel and button as output
 *  Parameters           :  Button *lp_button, T_UBYTE lub_channel
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void Button_Init( Button *lp_button, T_UBYTE lub_channel )
{
	lp_button->channel = lub_channel;
	lp_button->PushButton = &Button_Pressed;
	GPIO_Init_channel(lp_button->channel,INPUT,GPIO_OPEN_DRAIN_ENABLE);
	GPIO_Input(lp_button->channel, LOGICAL_VALUE_INT);
}


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Button_Pressed
 *  Description          :	Checks if there's a button pressed. Return PRESSED or NON-PRESSED
 *  Parameters           :  T_UBYTE lub_channel
 *  Return               :	T_UBYTE
 *  Critical/explanation :  YES
 **************************************************************/
 
 T_UBYTE Button_Pressed( T_UBYTE lub_channel )
 {
 	if( PULL_DOWN( lub_channel ) )
 		return PRESSED;
 	else
 		return NON_PRESSED;
 }

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Antti_Pinch
 *  Description          :	Checks if there's a button pressed. Return PRESSED or NON-PRESSED
 *  Parameters           :  T_UBYTE lub_channel
 *  Return               :	T_UBYTE
 *  Critical/explanation :  YES
 **************************************************************/
 
 T_UBYTE Anti_Pinch(Button lp_button, T_UBYTE lub_direction )
 {
 	if( lp_button.PushButton(lp_button.channel) )
	{
		if( lub_direction == CLOSED )
		{
			return PRESSED;
		}
		else
			return NON_PRESSED;
	}
	else
		return NON_PRESSED;
 }