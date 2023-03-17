/*******************************************************************************
*
* FILE: 
*       main.h
*
* DESCRIPTION: 
*		Flashes the onboard rgb led in order to verify that the flight computer 
*       board and programmer are functioning correctly 
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------
Includes                                                                    
------------------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"


/*------------------------------------------------------------------------------
Macros  
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Exported functions prototypes                                             
------------------------------------------------------------------------------*/

void HAL_TIM_MspPostInit
	(
	TIM_HandleTypeDef *htim
	);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
