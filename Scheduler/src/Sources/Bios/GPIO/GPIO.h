/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %GPIO.h%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Edgar Mosqueda Cardenas %
* %date_created:    Thu jul 16 13:43:01 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : It's changing defines where are pins as output for      */
/*		      the leds and declare news defines as input for the      */
/*                    button.                                                 */
/*		         						      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 16/07/2015  | SAR/SIF/SCN_xxx               | Edgar Mosqueda   */
/* Integration under Continuus                                              */
/*============================================================================*/

#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/* Includes */
#include "typedefs.h"
/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */

/* Exported types and constants */
/* ---------------------------- */

#define OPEN_PUSH				64
#define CLOSED_PUSH				65
#define PINCH_PUSH				66

//PORT C
#define LED1       				34
#define LED2        				35
#define LED3        				36
#define LED4        				37
#define LED5        				38
#define LED6        				39
#define LED7        				40
#define LED8        				41
#define LED9        				42
#define LED10        				43
#define LED_OPEN      				44
#define LED_CLOSED     				45


#define GPIO_INPUT				0
#define GPIO_OUTPUT				1

#define GPIO_OPEN_DRAIN_DISABLE			0
#define GPIO_OPEN_DRAIN_ENABLE			1



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

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */
/* Indicator LEDs handling */

/** Set LED */ 
#define LED_ON(channel)                     (SIU.GPDO[channel].B.PDO =  1)
/** Clear LED */ 
#define LED_OFF(channel)                    (SIU.GPDO[channel].B.PDO =  0)
/** Toggle LED */ 
#define LED_TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 

/** button */
#define PUSH_PRESSED(channel)		    ( SIU.GPDI[channel].R )


/* Functions prototypes */

void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain);
void vfnGPIO_Output(uint8_t channel, uint8_t logical_value);
void vfnGPIO_Input(uint8_t channel, uint8_t logical_value);
void vfnGPIO_LED_Init(void);
void vfnGPIO_PUSH_Init(void);
/* Functions macros */


/* Exported defines */

#endif /* _GPIO_H */

/*******************************************************************************/
