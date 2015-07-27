/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %Window.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Fri Jun  24 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  |                               | Mario Rivera     */
/* Integration programming layer.                                             */
/* Add window movement to make it independent.                                */
/* Add standby,open and close indicators.	                                  */
/* Add initWindow to initialize the window and implements in windowLifter.    */
/*============================================================================*/

#ifndef TEMPLATE_H                               /* To avoid double inclusion */
#define TEMPLATE_H

/* Includes */
/* -------- */
#include "typedefs.h"


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */

enum direction
{
	OPEN = 5,
	CLOSED = 6
};
/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void Init_Window(void);
extern void Window_movement( T_UBYTE lub_Direction, T_UBYTE lub_level );
extern void Indicator_StandBy(void);
extern void Indicator_Close( T_UBYTE lub_level );
extern void Indicator_Open( T_UBYTE lub_level );
/* Functions macros */


/* Exported defines */


#endif


