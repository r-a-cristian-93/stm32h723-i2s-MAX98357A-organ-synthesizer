#include "eko_tiger_p61.h"

#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"
#include "i2s.h"

#include <OrganEngine/Config.h>
#include <OrganEngine/RotarySpeaker.h>
#include <OrganEngine/WaveTables.h>
#include <WaveOrgan/WaveOrgan.h>
#include <WaveOrgan/Envelope.h>

uint32_t timBlink = 0;
uint32_t timSpi = 0;
uint32_t timDigitalInputs = 0;
SoftClip softClip = {};


#define BUFF_LEN 128
#define BUFF_LEN_DIV2 64

uint16_t	drums_buff[BUFF_LEN] = {0};
uint32_t	audio_buff[BUFF_LEN];
uint8_t        effect_chorus = 0;

__attribute((always_inline)) inline
void handleBitsChange(uint16_t* dataArray, uint16_t* prevBitsArray, uint8_t noteOffset);

LPF drum_lpf;

__attribute((always_inline)) inline
void getSamples(uint32_t* output, uint16_t startFrame, uint16_t endFrame)
{
	int32_t sample = 0;
	uint32_t u_sample = 0;

	for (uint16_t iFrame = startFrame; iFrame < endFrame; iFrame++)
	{
		sample = wave_organ_generate_sample();

		if (effect_chorus != 0)
			sample += rotary_speaker_process_sample(sample);
		else
			sample = rotary_speaker_process_sample(sample);

	    sample = SoftClip_ProcessSample(&softClip, sample);

	    // +-32767 >> 4 = +-2047
		sample = sample >> 4;

		// +-2047 + 0x7FF = 0_4095
		sample = sample + 0x7FF;

		u_sample = (uint32_t) sample;
		uint16_t drum_sample = drums_buff[iFrame];
//		drum_sample = drum_lpf.getSample(drum_sample);
		u_sample = u_sample + drum_sample;

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

//void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s);
//void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s);

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
#define DIN_EFFECT_MASK (0b00011111)

void readDigitalInputs() {
	const uint8_t effectOrchestraCancel = !(DIN_CONTROLS_PORT->IDR >> 12 & 0b00000001);

	const uint8_t orchestraVoice = (DIN_CONTROLS_PORT->IDR & DIN_ORCHESTRA_MASK) * effectOrchestraCancel;
	wave_organ_set_voice(orchestraVoice);

	const uint8_t effectVoice = DIN_CONTROLS_PORT->IDR >> 7 & DIN_EFFECT_MASK;
	wave_organ_set_effect(effectVoice);

	const uint8_t effectVibratoDepth = DIN_CONTROLS_PORT->IDR >> 6 & 0b00000001;
	const uint8_t midiParamVibratoDepth = effectVibratoDepth * 127;
	rotary_speaker_set_depth(midiParamVibratoDepth);

	const uint8_t effectChorus = !(DIN_CONTROLS_PORT->IDR >> 5 & 0b00000001);
	effect_chorus = effectChorus;
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


#define ADC_BUFFER_SIZE (16)
uint32_t adcBuffer[ADC_BUFFER_SIZE] = {0};
uint8_t paramBassVolume = 0;
uint8_t paramAccompVolume = 0;
uint8_t paramVibrato = 0;
uint8_t paramSustain = 0;

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
	// DO NOTHING
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	uint32_t adcVibrato = adcBuffer[0] >> 9;
	uint32_t adcSustain = adcBuffer[1] >> 9;
	uint32_t adcBassVolume = adcBuffer[2] >> 9;
	uint32_t adcAccompVolume = adcBuffer[3] >> 9;

	if (adcBassVolume != paramBassVolume)
	{
		paramBassVolume = (uint8_t) adcBassVolume;
		wave_organ_set_bass_volume(paramBassVolume);

		ledToggle();
	}

	if (adcAccompVolume != paramAccompVolume)
	{
		paramAccompVolume = (uint8_t) adcAccompVolume;
		wave_organ_set_orchestra_volume(paramAccompVolume);

		ledToggle();
	}

	if (adcVibrato != paramVibrato)
	{
		paramVibrato = (uint8_t) adcVibrato;
		rotary_speaker_set_speed(paramVibrato);

		ledToggle();
	}

	if (adcSustain != paramSustain)
	{
		paramSustain = (uint8_t)adcSustain;
		envelope_set_release_rate(paramSustain);

		ledToggle();
	}
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
	ledInit();
    SoftClip_Init(&softClip, 16383, 3);


	HAL_TIM_Base_Start(&htim6);
	HAL_TIM_Base_Start(&htim7);
	HAL_DAC_Start_DMA(&hdac1, DAC_CHANNEL_1, audio_buff, BUFF_LEN, DAC_ALIGN_12B_R);
	HAL_I2S_Receive_DMA(&hi2s2, drums_buff, BUFF_LEN);

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
