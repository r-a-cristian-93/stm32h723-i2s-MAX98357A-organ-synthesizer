/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ADC_VIBRATO_SPEED_Pin GPIO_PIN_1
#define ADC_VIBRATO_SPEED_GPIO_Port GPIOC
#define ADC_SUSTAIN_Pin GPIO_PIN_1
#define ADC_SUSTAIN_GPIO_Port GPIOA
#define ADC_BASS_VOLUME_Pin GPIO_PIN_2
#define ADC_BASS_VOLUME_GPIO_Port GPIOA
#define ADC_ACCOMP_VOLUME_Pin GPIO_PIN_3
#define ADC_ACCOMP_VOLUME_GPIO_Port GPIOA
#define HC597_LATCH_CLOCK_Pin GPIO_PIN_8
#define HC597_LATCH_CLOCK_GPIO_Port GPIOE
#define HC597_SERIAL_SHIFT_PARALLEL_LOAD_Pin GPIO_PIN_9
#define HC597_SERIAL_SHIFT_PARALLEL_LOAD_GPIO_Port GPIOE
#define DIN_EFFECT_PIANNO_Pin GPIO_PIN_8
#define DIN_EFFECT_PIANNO_GPIO_Port GPIOD
#define DIN_EFFECT_HARPSICORD_Pin GPIO_PIN_9
#define DIN_EFFECT_HARPSICORD_GPIO_Port GPIOD
#define DIN_EFFECT_ECHO_BELLS_Pin GPIO_PIN_10
#define DIN_EFFECT_ECHO_BELLS_GPIO_Port GPIOD
#define DIN_EFFECT_SYNTH_WAH_Pin GPIO_PIN_11
#define DIN_EFFECT_SYNTH_WAH_GPIO_Port GPIOD
#define DIN_EFFECT_ORCHESTRA_CANCEL_Pin GPIO_PIN_12
#define DIN_EFFECT_ORCHESTRA_CANCEL_GPIO_Port GPIOD
#define DIN_ORCHESTRA_FLUTE_8_Pin GPIO_PIN_0
#define DIN_ORCHESTRA_FLUTE_8_GPIO_Port GPIOD
#define DIN_ORCHESTRA_FLUTE_4_Pin GPIO_PIN_1
#define DIN_ORCHESTRA_FLUTE_4_GPIO_Port GPIOD
#define DIN_ORCHESTRA_VIOLIN_Pin GPIO_PIN_2
#define DIN_ORCHESTRA_VIOLIN_GPIO_Port GPIOD
#define DIN_ORCHESTRA_TRUMPET_Pin GPIO_PIN_3
#define DIN_ORCHESTRA_TRUMPET_GPIO_Port GPIOD
#define DIN_ORCHESTRA_CLARINET_Pin GPIO_PIN_4
#define DIN_ORCHESTRA_CLARINET_GPIO_Port GPIOD
#define DIN_VIBRATO_ON_OFF_Pin GPIO_PIN_5
#define DIN_VIBRATO_ON_OFF_GPIO_Port GPIOD
#define DIN_VIBRATO_DELAY_Pin GPIO_PIN_6
#define DIN_VIBRATO_DELAY_GPIO_Port GPIOD
#define DIN_EFFECT_PERCUSSION_4_Pin GPIO_PIN_7
#define DIN_EFFECT_PERCUSSION_4_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
#define MIDI_IN_PORTS_NUM   0x01 // Specify input ports number of your device
#define MIDI_OUT_PORTS_NUM  0x01 // Specify output ports number of your device
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
