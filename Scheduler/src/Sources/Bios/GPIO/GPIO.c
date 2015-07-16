/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      Edgar Mosqueda Cardenas %
* %date_created:    Thu July 16  14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT :It have added more leds as outputs and buttons as inputs.*/	
/*                   it have to start all variables that it have to use the   */
/*		     app						      */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 16/07/2015  |                               | Edgar Mosqueda   */
/* Integration under Continuus CM                                             */
/*============================================================================*/


/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */


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
 
void vfnGPIO_Init_channel(uint8_t channel, uint8_t input_output, uint8_t Open_drain)
{
    if (input_output == GPIO_OUTPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.OBE = 1;					/* Output buffer enable */
    	if (Open_drain == GPIO_OPEN_DRAIN_ENABLE)
    	{
    		SIU.PCR[channel].B.ODE = 1;				/* Open drain option enable */	
    	}
    	else
    	{	
    		SIU.PCR[channel].B.ODE = 0;				/* Push-pull option enable */	
    	}
    }
    else if (input_output == GPIO_INPUT)
    {
    	SIU.PCR[channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[channel].B.IBE = 1;					/* Input buffer enable */	
    }

}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
void vfnGPIO_Output(uint8_t channel, uint8_t logical_value)
{
    SIU.GPDO[channel].B.PDO  = logical_value;  		/* Drive the logical output value to the pin */

}

void vfnGPIO_Input(uint8_t channel, uint8_t logical_value)
{
    SIU.GPDI[channel].B.PDI  = logical_value;  		/* Drive the logical input value to the pin */

}


/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
void vfnGPIO_LED_Init(void)
{	
	/* Data Port C initialization */
	vfnGPIO_Init_channel(LED1,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);
	vfnGPIO_Output (LED1, 1);
	vfnGPIO_Init_channel(LED2,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED2, 1);
	vfnGPIO_Init_channel(LED3,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED3, 1);
	vfnGPIO_Init_channel(LED4,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED4, 1);
	vfnGPIO_Init_channel(LED5,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED5, 1);
	vfnGPIO_Init_channel(LED6,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE); 
	vfnGPIO_Output (LED6, 1);
	vfnGPIO_Init_channel(LED7,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED7, 1);
	vfnGPIO_Init_channel(LED8,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE); 
	vfnGPIO_Output (LED8, 1);
	vfnGPIO_Init_channel(LED9,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE); 
	vfnGPIO_Output (LED9, 1);
	vfnGPIO_Init_channel(LED10,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	vfnGPIO_Output (LED10, 1);
	vfnGPIO_Init_channel(LED_OPEN,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);
	vfnGPIO_Output (LED_OPEN, 1);
	vfnGPIO_Init_channel(LED_CLOSED,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);
	vfnGPIO_Output (LED_CLOSED, 1);
	
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 

void vfnGPIO_PUSH_Init(void)
{
	vfnGPIO_Init_channel(OPEN_PUSH,GPIO_INPUT,GPIO_OPEN_DRAIN_ENABLE);
	vfnGPIO_Input(OPEN_PUSH, 1);
	vfnGPIO_Init_channel(CLOSED_PUSH,GPIO_INPUT,GPIO_OPEN_DRAIN_ENABLE);
	vfnGPIO_Input(CLOSED_PUSH, 1);
	vfnGPIO_Init_channel(PINCH_PUSH,GPIO_INPUT,GPIO_OPEN_DRAIN_ENABLE);
	vfnGPIO_Input(PINCH_PUSH, 1);
	
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
