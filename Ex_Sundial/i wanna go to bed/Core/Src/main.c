/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <math.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ACC_READ 0x32
#define ACC_WRITE 0x33
#define MAX_CHAR 1000

#define ACC_SENS 0x27

#define MAG_READ 0x3C
#define MAG_WRITE 0x3D

#define LSM303AGR_BlockUpdate_Continuous ((uint8_t)0x00) /*!< Continuous Update */

#define LSM303AGR_CFG_REG_A_M 0x60  /* Configuration register A magnetic field */

#define LSM303AGR_ODR_220_HZ ((uint8_t) 0x1C)  /*!< Output Data Rate = 220 Hz */

#define LSM303AGR_M_SENSITIVITY_XY_1_3Ga     1100  /*!< magnetometer X Y axes sensitivity for 1.3 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_Z_1_3Ga      980   /*!< magnetometer Z axis sensitivity for 1.3 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_XY_1_9Ga     855   /*!< magnetometer X Y axes sensitivity for 1.9 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_Z_1_9Ga      760   /*!< magnetometer Z axis sensitivity for 1.9 Ga full scale [LSB/Ga] */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

I2C_HandleTypeDef I2cHandle;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  //huart1.Init.BaudRate = 115200;

  //ACCELEROMETER
  char buffer1[MAX_CHAR];
  char buffer2[MAX_CHAR];
  	HAL_StatusTypeDef returnValue, stat, check, odr;

  	HAL_Init();
  		SystemClock_Config();

  	MX_GPIO_Init();
  		MX_USART1_UART_Init();
  		MX_I2C1_Init();

//  	uint8_t regValue = 0x57;
//  		returnValue = HAL_I2C_Mem_Write(&hi2c1, ACC_WRITE, 0x20, 1, &regValue, 1, 10);




  //MAGNETOMETER
//  	uint8_t magregValue = 0x57;
//  	 returnValue = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x20, 1, &magregValue, 1, 10);
//
//	if (returnValue != HAL_OK)
//	{
//		strcpy(buffer1, "You done fucked up\r\n");
//		HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//	}
//	else if(returnValue == HAL_OK){
//		strcpy(buffer1, "HAL OKAY\r\n");
//		HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//	}
//	else{
//		strcpy(buffer1, "nah\r\n");
//		HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//	}

  		uint8_t configValue = LSM303AGR_ODR_220_HZ;
  		odr = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, LSM303AGR_CFG_REG_A_M, 1, &configValue, 1, 10);
  		if (check != HAL_OK)
		{
			strcpy(buffer1, "You done fucked up\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else if(check == HAL_OK){
			strcpy(buffer1, "odr slay\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else{
			strcpy(buffer1, "not slay\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  	while (1)
  		{


//
//  			float sensor_sens = (1/3.9); //1g/3.9mg
//  			float adc_sens = 0.00024; //1
//
//
//  			//raw values unconverted
//  			uint8_t xMSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x29, 1, &xMSB, 1, 10);
//			uint8_t xLSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x28, 1, &xLSB, 1, 10);
//			//ADC Sensitivity * sensor sensitivity * data
//			int16_t accX = (((xMSB << 8) | xLSB));
//
////			// Zero padding
////			if (accX > 64000) {
////				accX = 0;
////			}
////
////			float acc_x = accX;
//			float acc_x = accX * sensor_sens* adc_sens;
//
//			//Jesse's idea, data * FS/minimum resolution of ADC
//			//int16_t accX = (((xMSB << 8) | xLSB)*pow(2, 13));
//
//			uint8_t yMSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2B, 1, &yMSB, 1, 10);
//			uint8_t yLSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2A, 1, &yLSB, 1, 10);
//			int16_t accY = (((yMSB << 8) | yLSB));
//
//			// Zero padding
////			if (accY > 64000) {
////				accY = 0;
////			}
////
////			float acc_y = accY;
//			float acc_y = accY * sensor_sens * adc_sens;
//
//
//			uint8_t zMSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2D, 1, &zMSB, 1, 10);
//			uint8_t zLSB = 0x00;
//			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2C, 1, &zLSB, 1, 10);
//			int16_t accZ = (((zMSB << 8) | zLSB));
//
////			// Zero padding
////			if (accZ > 64000) {
////				accZ = 0;
////			}
////
////			float acc_z = accZ;
//			float acc_z = accZ * sensor_sens * adc_sens;
//			//float acc_z = accZ*pow(2,13);
//
//			sprintf(buffer1, "ACCELEROMETER accX = %.3f accY = %.3f accZ = %.3f\r\n", acc_x, acc_y, acc_z);
//			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//			HAL_Delay(500);


//  			uint8_t xMSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x29, 1, &xMSB, 1, 10);
//  			uint8_t xLSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x28, 1, &xLSB, 1, 10);
//  			int16_t accX = ((((xMSB << 8) | xLSB)));
//
//  			uint8_t yMSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2B, 1, &yMSB, 1, 10);
//  			uint8_t yLSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2A, 1, &yLSB, 1, 10);
//  			int16_t accY = ((((yMSB << 8) | yLSB))*pow(2, 12)*2);
//
//  			uint8_t zMSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2D, 1, &zMSB, 1, 10);
//  			uint8_t zLSB = 0x00;
//  			HAL_I2C_Mem_Read(&hi2c1,ACC_READ, 0x2C, 1, &zLSB, 1, 10);
//  			float accZfloat = ((((zMSB << 8) | zLSB))*pow(2, 12)*2);
//  			int16_t accZ = ((((zMSB << 8) | zLSB))*pow(2, 12)*2);
//
//  			sprintf(buffer, "accX = %d accY = %d accZ = %d, accZf: %.2f\r\n", accX, accY, accZ, accZfloat);
//  			HAL_UART_Transmit(&huart1, buffer, strlen(buffer), HAL_MAX_DELAY);
//  			HAL_Delay(500);

			//MAGNETOMETER

//  		uint8_t mode = 0x00;  // Set the value for continuous mode
//  		  			HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x22, 1, &mode, 1, 10);

  		uint8_t mode = LSM303AGR_BlockUpdate_Continuous;
  		check = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x22, 1, &mode, 1, 10);
  		if (check != HAL_OK)
		{
			strcpy(buffer1, "You done fucked up\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else if(check == HAL_OK){
			strcpy(buffer1, "HAL OKAY\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else{
			strcpy(buffer1, "nah\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}



  		uint8_t magregValue = 0x57;
		 returnValue = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x20, 1, &magregValue, 1, 10);

		if (returnValue != HAL_OK)
		{
			strcpy(buffer1, "You done fucked up\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else if(returnValue == HAL_OK){
			strcpy(buffer1, "HAL OKAY\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}
		else{
			strcpy(buffer1, "nah\r\n");
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
		}

//
//  		uint8_t regValue = 0x00;  // Set the desired value, in this case, 0x00
//
		// Write to the OFFSET_X_REG (register address 0x45)
//		HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x45, 1, &regValue, 1, 10);

//  		LSM303AGR_CFG_REG_A_M = 0x00;

  			//uint8_t mode = LSM303AGR_BlockUpdate_Continuous;
  			//HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x22, 1, &mode, 1, 10);



			float sens = 0.001;


			//raw values unconverted
			//int8_t magXm = 0x00;
			int8_t magXm;
			HAL_I2C_Mem_Read(&hi2c1, MAG_READ, 0x69, 1, &magXm, 1, 10);

//			if (stat != HAL_OK){
//				strcpy(buffer1, "HAL AINT OKAY BRO\r\n");
//				HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//			}
//			else if(stat == HAL_OK){
//
//				strcpy(buffer1, "HAL OKAY\r\n");
//				HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
//			}
			//int8_t magXl = 0x00;
			int8_t magXl;
			HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x68, 1, &magXl, 1, 10);
			//ADC Sensitivity * sensor sensitivity * data

			int16_t magX = (((magXm << 8) | magXl));

			//float mag_x = magX *LSM303AGR_M_SENSITIVITY_XY_1_3Ga;
			float mag_x = magX* sens;


			//int8_t magYm = 0x00;
			int8_t magYm;
			HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6B, 1, &magYm, 1, 10);
			//int8_t magYl = 0x00;
			int8_t magYl;
			HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6A, 1, &magYl, 1, 10);
			int16_t magY = (((magYm << 8) | magYl));

			//float mag_y = magY * LSM303AGR_M_SENSITIVITY_XY_1_3Ga;
			float mag_y = magY* sens;

			//int8_t magZm = 0x00;
			int8_t magZm;
			HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6D, 1, &magZm, 1, 10);
			//int8_t magZl = 0x00;
			int8_t magZl;
			HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6C, 1, &magZl, 1, 10);
			int16_t magZ = (((magZm << 8) | magZl));

			//float mag_z = magZ * LSM303AGR_M_SENSITIVITY_Z_1_3Ga;
			float mag_z = magZ * sens;

			sprintf(buffer1, "magXm: %d, magXl: %d\r\nmagYm: %d, magYl: %d \r\nmagZm: %d, magZl: %d\r\n", magXm, magXl, magYm, magYl, magZm, magZl);
			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);


			sprintf(buffer2, "MAGNOTOMETER magX = %.4f magY = %.4f magZ = %.4f\r\n", mag_x, mag_y, mag_z);
			//sprintf(buffer2, "magXm %d \r\n", magXm);
			HAL_UART_Transmit(&huart1, buffer2, strlen(buffer2), HAL_MAX_DELAY);
			HAL_Delay(1000);
  		}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DRDY_Pin MEMS_INT3_Pin MEMS_INT4_Pin MEMS_INT1_Pin
                           MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = DRDY_Pin|MEMS_INT3_Pin|MEMS_INT4_Pin|MEMS_INT1_Pin
                          |MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
