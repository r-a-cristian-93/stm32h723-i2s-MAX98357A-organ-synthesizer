#include "eko_tiger_p61.h"

#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include <OrganEngine/Config.h>
#include <OrganEngine/RotarySpeaker.h>
#include <OrganEngine/WaveTables.h>
#include <WaveOrgan/WaveOrgan.h>
#include <DrumMachine/DrumMachine.h>
#include <DrumMachine/Sequencer.h>

uint32_t timBlink = 0;
uint32_t timSpi = 0;


#define BUFF_LEN 128
#define BUFF_LEN_DIV2 64

uint32_t	audio_buff[BUFF_LEN];

__attribute((always_inline)) inline
void getSamples(uint32_t* output, uint16_t startFrame, uint16_t endFrame)
{
	int32_t sample = 0;

	for (uint16_t iFrame = startFrame; iFrame < endFrame; iFrame++)
	{
		sequencer_tick();
		sample = wave_organ_generate_sample();
		sample = rotary_speaker_process_sample(sample);
		sample += drum_machine_generate_sample();

		sample = sample >> 1;

		uint32_t u_sample = (uint32_t) sample + (0x7FF);

        output[iFrame] = u_sample;
	}
}

void HAL_DAC_ConvHalfCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
	getSamples(audio_buff, 0, BUFF_LEN_DIV2);
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef* hdac)
{
	getSamples(audio_buff, BUFF_LEN_DIV2, BUFF_LEN);
}

__attribute((always_inline)) inline
bool areAllEqual(const uint16_t* array) {
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


#define ADC_BUFFER_SIZE (2)
uint32_t adcBuffer[ADC_BUFFER_SIZE] = {0};
uint8_t paramRotarySpeed = 0;
uint8_t paramOrchestraInstrument = 0;
uint8_t paramBassVolume = 0;

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{

	uint32_t adcBassValue = adcBuffer[0] >> 9;
	uint32_t adcRotaryValue = adcBuffer[1] >> 9;

	if (adcBassValue != paramBassVolume)
	{
		paramBassVolume = (uint8_t) adcBassValue;
		wave_organ_set_bass_volume(paramBassVolume);
	}

	if (adcRotaryValue != paramRotarySpeed)
	{
		paramRotarySpeed = (uint8_t) adcRotaryValue;
		rotary_speaker_set_speed(paramRotarySpeed);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	// DO NOTHING
}

void eko_tiger_p61_setup()
{
	for (uint16_t i = 0; i < BUFF_LEN; i++) {
		audio_buff[i] = 0;
	}

	waveforms_initialize();
	rotary_speaker_initialize();
	wave_organ_init();
	envelope_initialize();
	sequencer_init();
	ledInit();


	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start(&htim7);
	HAL_ADC_Start_DMA(&hadc1, adcBuffer, ADC_BUFFER_SIZE);
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, audio_buff, BUFF_LEN, DAC_ALIGN_12B_R);

}

