/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "i2s.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "led.h"

#include <OrganEngine/Config.h>
#include <OrganEngine/RotarySpeaker.h>
#include <OrganEngine/WaveTables.h>
#include <WaveOrgan/WaveOrgan.h>
#include <DrumMachine/DrumMachine.h>
#include <DrumMachine/Sequencer.h>

#include "midi_router.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

#define BUFF_LEN 128
#define BUFF_LEN_DIV2 64

uint16_t	audio_buff[BUFF_LEN];


void readSpi6();

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

__attribute((always_inline)) inline
void getSamples(uint16_t output[], uint16_t startFrame, uint16_t endFrame)
{
	int32_t sample = 0;

	for (uint16_t iFrame = startFrame; iFrame < endFrame; iFrame += 2)
	{
		sequencer_tick();
		sample = wave_organ_generate_sample();
		sample = rotary_speaker_process_sample(sample);
		sample += drum_machine_generate_sample();

		sample = sample >> 1;

        uint16_t u_sample = (uint16_t) sample + (0xFFFF);
        output[iFrame] = u_sample;
        output[iFrame + 1] = u_sample;
	}
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	getSamples(audio_buff, 0, BUFF_LEN_DIV2);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	getSamples(audio_buff, BUFF_LEN_DIV2, BUFF_LEN);
}

bool inline timeOut(uint32_t& tim, uint32_t millis)
{
	uint32_t nowTicks = HAL_GetTick();

	if (nowTicks - tim > millis)
	{
		tim = nowTicks;

		return true;
	}

	return false;
}

bool inline areAllEqual(const uint16_t* array) {
    return (array[0] == array[1]) &&
           (array[1] == array[2]) &&
           (array[2] == array[3]) &&
           (array[3] == array[4]) &&
           (array[4] == array[5]) &&
           (array[5] == array[6]) &&
           (array[6] == array[7]);
}

#define SHIFT_REGISTER_SAMPLES (8)
#define SHIFT_REGISTER_BITS_COUNT (16)

uint16_t data[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t prevBit[SHIFT_REGISTER_BITS_COUNT] = {0};
uint8_t buffer_index = 0;
uint8_t dataByte1 = 0;
uint8_t dataByte2 = 0;

uint8_t incommingBytes[2] = {0};

void readSpi6() {
    // Set PL high to enable serial loading mode
    HAL_GPIO_WritePin(HC597_SERIAL_SHIFT_PARALLEL_LOAD_GPIO_Port, HC597_SERIAL_SHIFT_PARALLEL_LOAD_Pin, GPIO_PIN_SET);

    // Set RESET high (inactive)
//    HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, GPIO_PIN_SET);

    // Set ST_CP high to latch data into the shift registers
    HAL_GPIO_WritePin(HC597_LATCH_CLOCK_GPIO_Port, HC597_LATCH_CLOCK_Pin, GPIO_PIN_SET);
//    HAL_Delay(1); // Short delay
//    for (volatile int i = 0; i < 10; i++);

    HAL_GPIO_WritePin(HC597_LATCH_CLOCK_GPIO_Port, HC597_LATCH_CLOCK_Pin, GPIO_PIN_RESET);

    // Read 2 bytes of data from the shift registers
    HAL_SPI_Receive(&hspi6, incommingBytes, 2, HAL_MAX_DELAY);

    data[buffer_index] = (incommingBytes[0] << 8) | incommingBytes[1];

    HAL_GPIO_WritePin(HC597_SERIAL_SHIFT_PARALLEL_LOAD_GPIO_Port, HC597_SERIAL_SHIFT_PARALLEL_LOAD_Pin, GPIO_PIN_RESET);

	buffer_index++;

	if (buffer_index >= SHIFT_REGISTER_SAMPLES) {
		buffer_index = 0;
		if (areAllEqual(data)) {

			for (int i = 0; i < SHIFT_REGISTER_BITS_COUNT; ++i) {
				uint16_t bit = (data[0] >> i) & 1;

				if (bit != prevBit[i]) {
					prevBit[i] = bit;

					if (bit != 0)
					   wav_organ_note_on(i+72);
					else
						wav_organ_note_off(i+72);
				}
			}
		}
	}
}



#define ADC_BUFFER_SIZE (8)
uint32_t adcBuffer[ADC_BUFFER_SIZE] = {0};
uint32_t adcValue = 0;
uint8_t paramRotarySpeed = 0;
uint8_t paramOrchestraInstrument = 0;

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint32_t adcValue =
			adcBuffer[0] +
			adcBuffer[1] +
			adcBuffer[2] +
			adcBuffer[3] +
			adcBuffer[4] +
			adcBuffer[5] +
			adcBuffer[6] +
			adcBuffer[7];

	adcValue = adcValue >> 14;

	if (adcValue != paramOrchestraInstrument)
	{
		paramOrchestraInstrument = (uint8_t) adcValue;
		wave_organ_set_voice(paramOrchestraInstrument);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	// DO NOTHING
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint32_t timBlink = 0;
	uint32_t timSpi = 0;

	for (uint16_t i = 0; i < BUFF_LEN; i++) {
		audio_buff[i] = 0;
	}

	waveforms_initialize();
	rotary_speaker_initialize();
	wave_organ_init();
	envelope_initialize();
	sequencer_init();
	ledInit();

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_DMA_Init();
  MX_I2S3_Init();
  MX_USB_DEVICE_Init();
  MX_SPI6_Init();
  MX_ADC1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

	HAL_I2S_Transmit_DMA(&hi2s3, (uint16_t *) audio_buff, BUFF_LEN);
	HAL_ADC_Start_DMA(&hadc1, adcBuffer, ADC_BUFFER_SIZE);
	HAL_TIM_Base_Start(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1)
	{
	    MIDI_ProcessIncomming();
	    MIDI_ProcessOutgoing();

	    if (timeOut(timBlink,100)) {
			ledToggle();
		}

		if (timeOut(timSpi, 1)) {
			readSpi6();
		}

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 44;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
