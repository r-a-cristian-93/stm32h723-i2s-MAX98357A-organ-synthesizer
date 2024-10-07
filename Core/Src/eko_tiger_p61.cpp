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
uint32_t timDigitalInputs = 0;


#define BUFF_LEN 128
#define BUFF_LEN_DIV2 64

uint32_t	audio_buff[BUFF_LEN];

__attribute((always_inline)) inline
void handleBitsChange(uint16_t* dataArray, uint16_t* prevBitsArray, uint8_t noteOffset);

__attribute((always_inline)) inline
void getSamples(uint32_t* output, uint16_t startFrame, uint16_t endFrame)
{
	int32_t sample = 0;

	for (uint16_t iFrame = startFrame; iFrame < endFrame; iFrame++)
	{
		sequencer_tick();
		sample = wave_organ_generate_sample();
		sample = rotary_speaker_process_sample(sample);
//		sample += drum_machine_generate_sample();
//
//		sample = sample >> 1;

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
#define SHIFT_REGISTER_BYTES_COUNT (8)
#define SHIFT_REGISTER_BITS_COUNT (8)

uint16_t data0[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data1[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data2[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data3[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data4[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data5[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data6[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t data7[SHIFT_REGISTER_SAMPLES] = {0};
uint16_t prevBits0[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits1[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits2[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits3[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits4[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits5[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits6[SHIFT_REGISTER_BITS_COUNT] = {1};
uint16_t prevBits7[SHIFT_REGISTER_BITS_COUNT] = {1};
uint8_t buffer_index = 0;

uint8_t incommingBytes[SHIFT_REGISTER_BYTES_COUNT] = {0};


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

    // Read 2 bytes of data0 from the shift registers
//    HAL_SPI_Receive(&hspi6, incommingBytes, 2, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi6, incommingBytes, SHIFT_REGISTER_BYTES_COUNT, HAL_MAX_DELAY);
//    HAL_SPI_Receive(&hspi6, incommingBytes, 1, HAL_MAX_DELAY);


//    HAL_SPI_Receive(&hspi6, &incommingBytes[1], 1, HAL_MAX_DELAY);
//    HAL_SPI_Receive(&hspi6, &incommingBytes[2], 1, HAL_MAX_DELAY);
//    HAL_SPI_Receive(&hspi6, &incommingBytes[3], 1, HAL_MAX_DELAY);+-

//    data0[buffer_index] = (incommingBytes[0] << 8) | incommingBytes[1];
    data0[buffer_index] = incommingBytes[0];
    data1[buffer_index] = incommingBytes[1];
    data2[buffer_index] = incommingBytes[2];
    data3[buffer_index] = incommingBytes[3];
    data4[buffer_index] = incommingBytes[4];
    data5[buffer_index] = incommingBytes[5];
    data6[buffer_index] = incommingBytes[6];
    data7[buffer_index] = incommingBytes[7];

    HAL_GPIO_WritePin(HC597_SERIAL_SHIFT_PARALLEL_LOAD_GPIO_Port, HC597_SERIAL_SHIFT_PARALLEL_LOAD_Pin, GPIO_PIN_RESET);

	buffer_index++;

	if (buffer_index >= SHIFT_REGISTER_SAMPLES) {
		buffer_index = 0;
		handleBitsChange(data0, prevBits0, 0);
		handleBitsChange(data1, prevBits1, 8);
		handleBitsChange(data2, prevBits2, 16);
		handleBitsChange(data3, prevBits3, 24);
		handleBitsChange(data4, prevBits4, 32);
		handleBitsChange(data5, prevBits5, 40);
		handleBitsChange(data6, prevBits6, 48);
		handleBitsChange(data7, prevBits7, 56);
	}
}

uint8_t orchestraVoice = 0;

#define DIN_CONTROLS_PORT GPIOD
#define DIN_ORCHESTRA_MASK (0b00011111)

void readDigitalInputs() {
	const uint8_t effectOrchestraCancel = !(DIN_CONTROLS_PORT->IDR >> 12 & 0b00000001);

	const uint8_t orchestraVoice = ( DIN_CONTROLS_PORT->IDR & DIN_ORCHESTRA_MASK ) * effectOrchestraCancel;
	wave_organ_set_voice(orchestraVoice);


//	const uint8_t effectVoice = DIN_CONTROLS_PORT->IDR >> 7 & 0b00111111;
//	wave_organ_set_effect(effectVoice);
}

void handleBitsChange(uint16_t* dataArray, uint16_t* prevBitsArray, uint8_t noteOffset) {
	if (areAllEqual(dataArray)) {

		for (int i = 0; i < SHIFT_REGISTER_BITS_COUNT; ++i) {
			uint16_t bit = dataArray[0] & (1 << i);

			if (bit != prevBitsArray[i]) {
				prevBitsArray[i] = bit;

				if (bit == 0)
				   wav_organ_note_on(i + noteOffset + 48);
				else
					wav_organ_note_off(i + noteOffset + 48);
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

		ledToggle();
	}

	if (adcRotaryValue != paramRotarySpeed)
	{
		paramRotarySpeed = (uint8_t) adcRotaryValue;
		rotary_speaker_set_speed(paramRotarySpeed);

		ledToggle();
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
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, audio_buff, BUFF_LEN, DAC_ALIGN_12B_R);

	HAL_ADCEx_Calibration_Start(&hadc1,  ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, adcBuffer, ADC_BUFFER_SIZE);
}


uint8_t note_state = 0;

void toggleNote() {
	if (note_state == 0)
	{
		note_state = 1;
		wav_organ_note_on(60);
	}
	else
	{
		note_state = 0;
		wav_organ_note_off(60);
	}
}