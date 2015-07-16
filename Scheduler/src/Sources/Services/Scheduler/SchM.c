/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %template.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:    Fri Jan  9 14:38:03 2004 %
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
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include    "SchM.h"
#include    "PIT.h"
#include    "MemAlloc.h"
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
const SchConfigType *rp_SchM_Config;


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
SchControlType SchM_Control;
SchTaskControlType *SchM_TaskControlPtr;


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
 *  Name                 :	SchM_Init
 *  Description          :
 *  Parameters           :  SchConfigType *SchM_Config 
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void SchM_Init( const SchConfigType *SchM_Config )
{
	T_UBYTE lub_counter_task;
	PIT_device_init();
    PIT_channel_configure(PIT_CHANNEL_0 , SchM_OsTick);
    rp_SchM_Config = SchM_Config;
	SchM_TaskControlPtr = (SchTaskControlType*)MemAlloc(rp_SchM_Config->SchNumberOfTask*sizeof(SchTaskControlType));
	for(lub_counter_task = 0; lub_counter_task < rp_SchM_Config->SchNumberOfTask; lub_counter_task++)
	{
		SchM_TaskControlPtr[lub_counter_task].SchTaskState = TASK_STATE_SUSPENDED; 
		SchM_TaskControlPtr[lub_counter_task].TaskFunctionControlPtr = rp_SchM_Config->SchTaskTable[lub_counter_task].TaskFunctionPtr;
	}
	SchM_Control.SchStatus = SCH_INIT;
	SchM_Control.SchCounter = 0;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Stop
 *  Description          :
 *  Parameters           :  void
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

void SchM_Stop(void)
{
	PIT_channel_stop(PIT_CHANNEL_0);
	SchM_Control.SchStatus = SCH_HALTED;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Start
 *  Description          :
 *  Parameters           :  void
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void SchM_Start(void)
{
	PIT_channel_start(PIT_CHANNEL_0);
	SchM_Control.SchStatus = SCH_RUNNING;
	SchM_Background();
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_OsTick
 *  Description          :
 *  Parameters           :  void
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void SchM_OsTick(void)
{
	T_UBYTE lub_counter_task;
	T_UBYTE lub_maskResult;
	SchM_Control.SchCounter++;
	for(lub_counter_task = 0; lub_counter_task < rp_SchM_Config->SchNumberOfTask; lub_counter_task++)
	{
		lub_maskResult = rp_SchM_Config->SchTaskTable[lub_counter_task].SchTaskMask & SchM_Control.SchCounter;
		if( lub_maskResult == rp_SchM_Config->SchTaskTable[lub_counter_task].SchTaskOffset )
		{
			SchM_TaskControlPtr[lub_counter_task].SchTaskState = TASK_STATE_READY;
		}
		else
		{
			//Do nothing
		}
	}
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	SchM_Background
 *  Description          :
 *  Parameters           :  void
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void SchM_Background(void)
{
	T_UBYTE lub_counter_task;
	for(;;)
	{
		for(lub_counter_task = 0; lub_counter_task < rp_SchM_Config->SchNumberOfTask; lub_counter_task++)
		{
			if( SchM_TaskControlPtr[lub_counter_task].SchTaskState == TASK_STATE_READY )
			{
				//SchM_Control.SchStatus = SCH_RUNNING;
				SchM_TaskControlPtr[lub_counter_task].SchTaskState = TASK_STATE_RUNNING;
				SchM_TaskControlPtr[lub_counter_task].TaskFunctionControlPtr();
				//SchM_Control.SchStatus = SCH_INIT;
				SchM_TaskControlPtr[lub_counter_task].SchTaskState = TASK_STATE_SUSPENDED;
				
			}
			else
			{
				//Do nothing
			}
		}
	}
}

