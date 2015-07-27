/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %Anti-Pinch.c%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Wend Jun  22 14:31:03 2015 %
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
/*  1.0      | 22/07/2015  |                               | Mario Rivera     */
/* Add Anti-Pinch functionaliti.                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "Anti-Pinch.h"
//#include "typedefs.h"
//#include "Button.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */

enum direction
{
	OPEN = 5,
	CLOSED = 6
};

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


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
 *  Name                 :	Antti_Pinch
 *  Description          :	Checks if there's a button pressed. Return PRESSED or NON-PRESSED
 *  Parameters           :  T_UBYTE lub_channel
 *  Return               :	T_UBYTE
 *  Critical/explanation :  YES
 **************************************************************/
 
 T_UBYTE Anti_Pinch(Button lp_button, T_UBYTE lub_direction )
 {
 	if( lp_button.PushButton( lp_button.channel ) )
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