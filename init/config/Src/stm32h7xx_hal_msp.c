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
*       HAL_I2C_MspInit                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the I2C MSP                                                *
*                                                                              *
*******************************************************************************/
void HAL_I2C_MspInit
	(
	I2C_HandleTypeDef* hi2c
	)
{
/* Initialization Structs */
GPIO_InitTypeDef         GPIO_InitStruct     = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* Barometric pressure sensor I2C interface */
if( hi2c->Instance == I2C1 )
	{
	/* Initializes the peripherals clock */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
	PeriphClkInitStruct.PLL3.PLL3M           = 2;
	PeriphClkInitStruct.PLL3.PLL3N           = 16;
	PeriphClkInitStruct.PLL3.PLL3P           = 2;
	PeriphClkInitStruct.PLL3.PLL3Q           = 2;
	PeriphClkInitStruct.PLL3.PLL3R           = 4;
	PeriphClkInitStruct.PLL3.PLL3RGE         = RCC_PLL3VCIRANGE_3;
	PeriphClkInitStruct.PLL3.PLL3VCOSEL      = RCC_PLL3VCOWIDE;
	PeriphClkInitStruct.PLL3.PLL3FRACN       = 0;
	PeriphClkInitStruct.I2c123ClockSelection = RCC_I2C123CLKSOURCE_PLL3;
	if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
		{
		Error_Handler();
		}

	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* I2C1 GPIO Configuration
	PB6     ------> I2C1_SCL
	PB7     ------> I2C1_SDA */
	GPIO_InitStruct.Pin       = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );

	/* Peripheral clock enable */
	__HAL_RCC_I2C1_CLK_ENABLE();
	}
} /* HAL_I2C_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_I2C_MspDeInit                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*       DeInitializes the I2C MSP                                              *
*                                                                              *
*******************************************************************************/
void HAL_I2C_MspDeInit
	(
	I2C_HandleTypeDef* hi2c
	)
{
/* Barometric pressure sensor I2C DeInitialization */
if( hi2c->Instance == I2C1 )
	{
	/* Peripheral clock disable */
	__HAL_RCC_I2C1_CLK_DISABLE();

	/* I2C1 GPIO Configuration
	PB6     ------> I2C1_SCL
	PB7     ------> I2C1_SDA */
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);
	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);
	}
} /* HAL_I2C_MspDeInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_SPI_MspInit                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the SPI MSP                                                *
*                                                                              *
*******************************************************************************/
void HAL_SPI_MspInit
	(
	SPI_HandleTypeDef* hspi
	)
{
/* Initialization structs */
GPIO_InitTypeDef         GPIO_InitStruct     = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* Flash SPI initialization */
if( hspi->Instance == SPI2 )
	{
	/* Initializes the peripherals clock */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2;
	PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL;
	if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
		{
		Error_Handler();
		}

	/* Peripheral clock enable */
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* SPI2 GPIO Configuration
	PB13     ------> SPI2_SCK
	PB14     ------> SPI2_MISO
	PB15     ------> SPI2_MOSI */
	GPIO_InitStruct.Pin       = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init( GPIOB, &GPIO_InitStruct );
	}
} /* HAL_SPI_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_SPI_MspDeInit                                                      *
*                                                                              *
* DESCRIPTION:                                                                 *
*       De-Initializes the SPI MSP                                             *
*                                                                              *
*******************************************************************************/
void HAL_SPI_MspDeInit
	(
	SPI_HandleTypeDef* hspi
	)
{
/* Flash SPI DeInitialization */
if( hspi->Instance == SPI2 )
	{
	/* Peripheral clock disable */
	__HAL_RCC_SPI2_CLK_DISABLE();

	/* SPI2 GPIO Configuration
	PB13     ------> SPI2_SCK
	PB14     ------> SPI2_MISO
	PB15     ------> SPI2_MOSI */
	HAL_GPIO_DeInit( GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15 );
	}
} /* HAL_SPI_MspDeInit */


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