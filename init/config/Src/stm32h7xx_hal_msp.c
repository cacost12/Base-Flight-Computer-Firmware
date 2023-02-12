/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
*       stm32h7xx_hal_msp.c                                                    *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Contains implementation of MSP initialization and de-initialization    *
*                routines                                                      *
*                                                                              *
*******************************************************************************/


/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/
#include "main.h"


/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_MspInit                                                            *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the Global MSP                                             *
*                                                                              *
*******************************************************************************/
void HAL_MspInit
	(
	void
	)
{
__HAL_RCC_SYSCFG_CLK_ENABLE();

} /* HAL_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspInit                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the UART MSP                                               *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspInit
	(
	UART_HandleTypeDef* huart
	)
{
/* Initialization Structs */
GPIO_InitTypeDef         GPIO_InitStruct     = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* USB UART */
if( huart->Instance == USART6 )
	{
	/* Initializes the peripherals clock */
	PeriphClkInitStruct.PeriphClockSelection  = RCC_PERIPHCLK_USART6;
	PeriphClkInitStruct.PLL2.PLL2M            = 2;
	PeriphClkInitStruct.PLL2.PLL2N            = 16;
	PeriphClkInitStruct.PLL2.PLL2P            = 2;
	PeriphClkInitStruct.PLL2.PLL2Q            = 4;
	PeriphClkInitStruct.PLL2.PLL2R            = 2;
	PeriphClkInitStruct.PLL2.PLL2RGE          = RCC_PLL2VCIRANGE_3;
	PeriphClkInitStruct.PLL2.PLL2VCOSEL       = RCC_PLL2VCOWIDE;
	PeriphClkInitStruct.PLL2.PLL2FRACN        = 0;
	PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PLL2;
	if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
		{
		Error_Handler();
		}

	/* Peripheral clock enable */
	__HAL_RCC_USART6_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/* USART6 GPIO Configuration
	PC6     ------> USART6_TX
	PC7     ------> USART6_RX */
	GPIO_InitStruct.Pin       = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART6;
	HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
	}
} /* HAL_UART_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspDeInit                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
*       DeInitializes the UART MSP                                             *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspDeInit
	(
	UART_HandleTypeDef* huart
	)
{
/* USB Uart */
if( huart->Instance == USART6 )
	{
	/* Peripheral clock disable */
	__HAL_RCC_USART6_CLK_DISABLE();

	/* USART6 GPIO Configuration
	PC6     ------> USART6_TX
	PC7     ------> USART6_RX */
	HAL_GPIO_DeInit( GPIOC, GPIO_PIN_6 | GPIO_PIN_7 );
	}
} /* HAL_UART_MspDeInit */


/*******************************************************************************
* END OF FILE                                                                  * 
*******************************************************************************/