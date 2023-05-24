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
#include <ADC_channels.h>
#include "main.h"
#include <stdlib.h>;
#include <stdio.h>


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

#define LSM303AGR_ODR_10_HZ               ((uint8_t)0x20)  /*!< Output Data Rate = 10 Hz */



#define LSM303AGR_M_SENSITIVITY_XY_1_3Ga     1100  /*!< magnetometer X Y axes sensitivity for 1.3 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_Z_1_3Ga      980   /*!< magnetometer Z axis sensitivity for 1.3 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_XY_1_9Ga     855   /*!< magnetometer X Y axes sensitivity for 1.9 Ga full scale [LSB/Ga] */

#define LSM303AGR_M_SENSITIVITY_Z_1_9Ga      760   /*!< magnetometer Z axis sensitivity for 1.9 Ga full scale [LSB/Ga] */

#define ARRAY_SIZE 10 //size of array for the data taken to average

#define LED_ALL 0xffff
#define LED_FOUR 0x5555
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

volatile int LED_POS = 0;
volatile uint8_t* led_output_display = ((uint8_t*)&(GPIOE->ODR)) + 1;
volatile uint32_t systickValue = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//define sConfig struct type to be used in ADC_select functions
ADC_ChannelConfTypeDef sConfig = {0};


void enable_clocks() {

RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;
}



void shuffleArray(float array[], float degrees){
	for(int i = 1; i < ARRAY_SIZE; i ++){
		array[i - 1] = array[i];
	}
	array[ARRAY_SIZE - 1] = degrees;
}

void enableLED()
{
	//only take important bits (first 16) of LED output register
	uint16_t* portReg = ((uint16_t*)&(GPIOE->MODER))+1;

	//set LED pins to output
	*portReg = LED_FOUR;
}

void turnOnLED(int pos){
	LED_POS = pos;
	*led_output_display = 1UL << LED_POS;

}

void turnOnAll(){
	*led_output_display = LED_ALL;
}

void turnOnFour(){
	*led_output_display = LED_FOUR;
}


//TWO FUNCTIONS USED FOR RANDOMISING
// SysTick callback function
void HAL_SYSTICK_Callback(void)
{
    systickValue++; // Increment SysTick value
}

// Randomizing function using SysTick value
uint8_t GenerateRandomNumber(void)
{
    return (uint8_t)(systickValue % 8); // Return the remainder of systickValue divided by 8 (0 to 7)
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	enable_clocks();

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */



  int solution = 1;

//
//  solution = HAL_GetTick() % 8;

  //huart1.Init.BaudRate = 115200;

  //ACCELEROMETER
  char buffer1[MAX_CHAR];
  char buffer2[MAX_CHAR];
  	HAL_StatusTypeDef returnValue, stat, check, odr;

  	uint8_t test[64];
  	uint8_t countString[64];
  	uint8_t string[64];
  	//VARIABLES FRO AVERAGE FUNCTION
  	float array[ARRAY_SIZE] = {0};
  	float average = 0;
  	int count = 0;
  	float sum = 0;

  	int solved = 0;

  	//srand(time(NULL));
  	//int solution = rand() % 8;

  	HAL_Init();
  		SystemClock_Config();

  	MX_GPIO_Init();
  		MX_USART1_UART_Init();
  		MX_I2C1_Init();

//  	uint8_t regValue = 0x57;
//  		returnValue = HAL_I2C_Mem_Write(&hi2c1, ACC_WRITE, 0x20, 1, &regValue, 1, 10);




  //MAGNETOMETER

  		uint8_t configValue = LSM303AGR_ODR_220_HZ;
  		odr = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, LSM303AGR_CFG_REG_A_M, 1, &configValue, 1, 10);


  		uint8_t mode = LSM303AGR_BlockUpdate_Continuous;
  		  		check = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x22, 1, &mode, 1, 10);



		uint8_t magregValue = 0x57;
		 returnValue = HAL_I2C_Mem_Write(&hi2c1, MAG_WRITE, 0x20, 1, &magregValue, 1, 10);

			 // MAGNETOMETER LOOP START
			   while (1){



				   sprintf(buffer1, "%d", solution);
				   HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);



			 	   //MAGNETOMETER
			 	  	float sens = (1); //1LSB/1.5mg


			 	  	//raw values unconverted
			 	  	//int8_t magXm = 0x00;
			 	  	uint8_t magXm;
			 	  	HAL_I2C_Mem_Read(&hi2c1, MAG_READ, 0x69, 1, &magXm, 1, 1000);

			 	  	//int8_t magXl = 0x00;
			 	  	uint8_t magXl;
			 	  	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x68, 1, &magXl, 1, 1000);
			 	  	//ADC Sensitivity * sensor sensitivity * data

			 	  	int16_t magX = (((magXm << 8) | magXl));

			 	  	//float mag_x = magX *LSM303AGR_M_SENSITIVITY_XY_1_3Ga;
			 	  	float mag_x = magX* sens;


			 	  	//int8_t magYm = 0x00;
			 	  	uint8_t magYm;
			 	  	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6B, 1, &magYm, 1, 1000);
			 	  	//int8_t magYl = 0x00;
			 	  	uint8_t magYl;
			 	  	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6A, 1, &magYl, 1, 1000);
			 	  	int16_t magY = (((magYm << 8) | magYl));

			 	  	//float mag_y = magY * LSM303AGR_M_SENSITIVITY_XY_1_3Ga;
			 	  	float mag_y = magY* sens;

			 	  	//int8_t magZm = 0x00;
			 	  	uint8_t magZm;
			 	  	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6D, 1, &magZm, 1, 1000);
			 	  	//int8_t magZl = 0x00;
			 	  	uint8_t magZl;
			 	  	HAL_I2C_Mem_Read(&hi2c1,MAG_READ, 0x6C, 1, &magZl, 1, 1000);
			 	  	int16_t magZ = (((magZm << 8) | magZl));

			 	  	//float mag_z = magZ * LSM303AGR_M_SENSITIVITY_Z_1_3Ga;
			 	  	float mag_z = magZ * sens;

			 	  	//CONVERTING TO DEGREES

			 	  	double degrees, y_on_x;
			 	  	double pi = 3.14159;
			 	  			if(mag_x != 0 && mag_y != 0){

			 	  	  				//determining which quadrant the mag is facing
			 	  	  				if(mag_x > 0 && mag_y > 0){
			 	  	  					y_on_x = (mag_y/mag_x);
			 	  	  					degrees = atan(y_on_x)*(180/pi);
			 	  	  					while(degrees >= 360){
			 	  	  						degrees = degrees - 360;
			 	  	  					}
			 	  	  				}
			 	  	  				else if (mag_x < 0 && mag_y > 0){
			 	  	  					y_on_x = (mag_y/mag_x);
			 	  	  					degrees = atan(y_on_x)*(180/pi) + 180;
			 	  	  					while(degrees >= 360){
			 	  	  						degrees = degrees - 360;
			 	  	  					}
			 	  	  				}
			 	  	  				else if (mag_x < 0 && mag_y < 0){
			 	  	  					y_on_x = (mag_y/mag_x);
			 	  	  					degrees = atan(y_on_x)*(180/pi) + 180;
			 	  	  					while(degrees >= 360){
			 	  	  						degrees = degrees - 360;
			 	  	  					}
			 	  	  				}
			 	  	  				else if (mag_x > 0 && mag_y < 0){
			 	  	  					y_on_x = (mag_y/mag_x);
			 	  	  					degrees = atan(y_on_x)*(180/pi) + 360;
			 	  	  					while(degrees >= 360){
			 	  	  						degrees = degrees - 360;
			 	  	  					}
			 	  	  				}
			 	  	  				else{

			 	  	  				}

			 	  	  			}
			 	  	  			else if(mag_x == 0 && mag_y > 0){
			 	  	  				degrees = 90;
			 	  	  			}
			 	  	  			else if(mag_x == 0 && mag_y < 0){
			 	  	  				degrees = 270;
			 	  	  			}
			 	  	  			else if(mag_y == 0 && mag_x > 0){
			 	  	  				degrees = 0;
			 	  	  			}
			 	  	  			else if (mag_y == 0 && mag_x < 0){
			 	  	  				degrees = 180;
			 	  	  			}


			 	  	  			//AVERAGING
			 	  	  			if (array[ARRAY_SIZE - 1] == 0){
			 	  	  				array[count] = degrees;
			 	  	  				count ++;

			 	  	  			}
			 	  	  			else{
			 	  	  				//shuffle the array
			 	  	  				shuffleArray(array, degrees);

			 	  	  				sum = 0;
			 	  	  				for(int i = 0; i < ARRAY_SIZE; i ++){
			 	  	  					sum += array[i];
			 	  	  				}

			 	  	  				average = (sum/ARRAY_SIZE);

			 	  	  				sprintf(buffer1, "%.2f, %.2f, ", array[0], array[ARRAY_SIZE - 1]);
			 	  	  				HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);

			 	  	  				sprintf(buffer1, "%.2f, ", average);
			 	  	  				HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);
			 	  	  			}

			 	  	  			sprintf(buffer1, "%d\r\n", solution);
			 	  	  			HAL_UART_Transmit(&huart1, buffer1, strlen(buffer1), HAL_MAX_DELAY);

			 	  	  			//LED DISPLAY
			 	  	  			//first sort into one of 8 categories
			 	  	  			if(average > 67.5 && average < 112.5 && solution == 1){
			 	  	  				turnOnLED(2);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 22.5 && average < 67.5 && solution == 2){
			 	  	  				turnOnLED(3);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (((degrees < 360 && degrees > 337.5) || (degrees > 0 && degrees < 22.5)) && solution == 3){ //something weird for 0 - 360
			 	  	  				turnOnLED(4);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 292.5 && average < 337.5 && solution == 4){
			 	  	  				turnOnLED(5);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 247.5 && average < 292.5 && solution == 5){
			 	  	  				turnOnLED(6);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 202.5 && average < 247.5 && solution == 6){
			 	  	  				turnOnLED(7);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 157.5 && average < 202.5 && solution == 7){
			 	  	  				turnOnLED(0);
			 	  	  				break;
			 	  	  			}
			 	  	  			else if (average > 112.5 && average < 157.5 && solution == 0){
			 	  	  				turnOnLED(1);
			 	  	  				break;
			 	  	  			}
			 	  	  			else{
			 	  	  				//turn on all LED's
			 	  	  				turnOnFour();

			 	  	  			}

			 	  	  			HAL_Delay(100);
			 	  	    	}
			   // END MAGNETOMETER LOOP


	  // START ADC LOOP
	  // calibrate ADC1
	  HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

	  // Create channel function pointer arrays
	  void (*LDRChannels[8])() = {
          &ADC_select_CH2,
          &ADC_select_CH3,
          &ADC_select_CH4,
          &ADC_select_CH5,
          &ADC_select_CH6,
          &ADC_select_CH7,
          &ADC_select_CH8,
          &ADC_select_CH9
      };

      // Array to record LDR status
      int LDRs[] = {0, 0, 0, 0, 0, 0, 0, 0};

      // Set Solution array to match against
      int ADC_Solutions[] = {0,0,0,0,0,0,0,0};
      ADC_Solutions[solution] = 1;

      // check LDRs and match to solution:
      while (ADC_check(LDRChannels, LDRs, ADC_Solutions, &hadc1, &sConfig) != 1){}
      // END ADC LOOP

      // Send Serial Code to core STM32 discovery board and display success on discovery board
      turnOnAll();
      HAL_UART_Transmit(&huart1, (uint8_t*) "]", strlen("]"), HAL_MAX_DELAY);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	    /* USER CODE END 3 */

  }
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
//  sConfig.Channel = ADC_CHANNEL_2;
//  sConfig.Rank = ADC_REGULAR_RANK_1;
//  sConfig.SingleDiff = ADC_SINGLE_ENDED;
//  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
//  sConfig.OffsetNumber = ADC_OFFSET_NONE;
//  sConfig.Offset = 0;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_2;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_3;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_4;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_5;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_6;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_7;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//
//  /** Configure Regular Channel
//  */
//  sConfig.Rank = ADC_REGULAR_RANK_8;
//  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
