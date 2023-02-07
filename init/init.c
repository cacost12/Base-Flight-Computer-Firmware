/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
* 		init.c                                                                 *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Contains initialization routines for MCU core and peripherals          *
*                                                                              *
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Project Includes                                                               
------------------------------------------------------------------------------*/
#include "sdr_pin_defines_A0007.h"
#include "main.h"
#include "init.h"


/*------------------------------------------------------------------------------
 Global Variables 
------------------------------------------------------------------------------*/
#ifndef BLINK
	extern I2C_HandleTypeDef  hi2c1;   /* Baro sensor    */
	extern SPI_HandleTypeDef  hspi2;   /* External flash */
	extern TIM_HandleTypeDef  htim4;   /* Buzzer Timer   */
	extern UART_HandleTypeDef huart6;  /* USB            */
#endif


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   * 
*       SystemClock_Config                                                     *
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Initializes the microcontroller clock. Enables peripheral clocks and   *
*       sets prescalers                                                        *
*                                                                              *
*******************************************************************************/
void SystemClock_Config
	(
	void
	)
{
/* Init structs */
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

/* Supply configuration update enable */
HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

/* Configure the main internal regulator output voltage */
__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

while( !__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY) ) 
	{
	/* Wait for PWR_FLAG_VOSRDY flag */
	}

/* Initializes the RCC Oscillators according to the specified parameters 
   in the RCC_OscInitTypeDef structure. */
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
RCC_OscInitStruct.PLL.PLLM       = 2;
RCC_OscInitStruct.PLL.PLLN       = 16;
RCC_OscInitStruct.PLL.PLLP       = 2;
RCC_OscInitStruct.PLL.PLLQ       = 2;
RCC_OscInitStruct.PLL.PLLR       = 2;
RCC_OscInitStruct.PLL.PLLRGE     = RCC_PLL1VCIRANGE_3;
RCC_OscInitStruct.PLL.PLLVCOSEL  = RCC_PLL1VCOWIDE;
RCC_OscInitStruct.PLL.PLLFRACN   = 0;
if ( HAL_RCC_OscConfig( &RCC_OscInitStruct ) != HAL_OK )
	{
	Error_Handler();
	}

/* Initializes the CPU, AHB and APB buses clocks */
RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK    |
                                   RCC_CLOCKTYPE_SYSCLK  |
								   RCC_CLOCKTYPE_PCLK1   |
								   RCC_CLOCKTYPE_PCLK2   |
								   RCC_CLOCKTYPE_D3PCLK1 |
								   RCC_CLOCKTYPE_D1PCLK1;
RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV1;
RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
if ( HAL_RCC_ClockConfig( &RCC_ClkInitStruct, FLASH_LATENCY_1 ) != HAL_OK )
	{
	Error_Handler();
	}
} /* SystemClock_Config */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       GPIO_Init                                                              * 
*                                                                              *
* DESCRIPTION:                                                                 * 
*       Initializes all GPIO pins and sets alternate functions                 *
*                                                                              *
*******************************************************************************/
void GPIO_Init
	(
	void
	)
{
/* Init Struct */
GPIO_InitTypeDef GPIO_InitStruct = {0};

/* GPIO Ports Clock Enable */
__HAL_RCC_GPIOA_CLK_ENABLE();

/*--------------------------- LED MCU PINS -----------------------------------*/

/*Configure GPIO pin Output Level */
HAL_GPIO_WritePin( STATUS_GPIO_PORT, 
                   STATUS_B_PIN |
                   STATUS_G_PIN |
                   STATUS_R_PIN    , 
                   GPIO_PIN_RESET );

/*Configure GPIO pins : PA9 PA10 PA11 */
GPIO_InitStruct.Pin   = STATUS_B_PIN |
                        STATUS_G_PIN |
					    STATUS_R_PIN;
GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
GPIO_InitStruct.Pull  = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init( STATUS_GPIO_PORT, &GPIO_InitStruct);

} /* GPIO_Init */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/