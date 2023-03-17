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
#include "sdr_error.h"
#include "main.h"
#include "init.h"

/* SDR Modules */
#include "led.h"


/*------------------------------------------------------------------------------
 Application entry point                                                      
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
 MCU Initialization                                                                  
------------------------------------------------------------------------------*/
HAL_Init          ();
SystemClock_Config();
GPIO_Init         ();


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
* END OF FILE                                                                  * 
*******************************************************************************/