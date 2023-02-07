/*******************************************************************************
*
* FILE: 
*       main.c
*
* DESCRIPTION: 
*		Flashes the onboard rgb led in order to verify that the flight computer 
*       board and programmer are functioning correctly 
*
*******************************************************************************/


/*------------------------------------------------------------------------------
Standard Includes                                                                     
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Project Includes                                                                     
------------------------------------------------------------------------------*/

/* Pin definitions and main prototypes */
#include "sdr_pin_defines_A0007.h"
#include "main.h"
#include "init.h"

/* SDR Modules */
#include "led.h"


/*------------------------------------------------------------------------------
Global Variables                                                                  
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Typedefs                                                                  
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Application entry point                                                      
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
Local Variables
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
MCU Initialization                                                                  
------------------------------------------------------------------------------*/
HAL_Init();
SystemClock_Config();
GPIO_Init();

/*------------------------------------------------------------------------------
Event Loop                                                                  
------------------------------------------------------------------------------*/
while (1)
	{
	/* Loop over 8 basic rgb led settings */
	for ( uint8_t i = 0; i < 8; ++i )
		{
		/* Start with LED off */
		if ( i == 0 )
			{
			led_reset();
			}
		else
			{
			/* Cycle through solid RGB colors */
			led_set_color( i );
			}

		/* Hold till next time period */
		HAL_Delay( 500 );
        }
	}

} /* main.c */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       Error_Handler                                                          * 
*                                                                              *
* DESCRIPTION:                                                                 * 
* 		This function is executed in case of error occurrence                  *
*                                                                              *
*******************************************************************************/
void Error_Handler
	(
	void
	)
{
__disable_irq();
while (1)
	{
	}
} /* Error_Handler */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed
	(
	uint8_t *file, 
	uint32_t line
	)
{
} /* assert_failed */
#endif /* USE_FULL_ASSERT */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/
