#include "eko_tiger_p61_rhythm.h"
#include <DrumMachine/Sequencer.h>
#include <DrumMachine/DrumMachine.h>
#include "main.h"
#include "i2s.h"

#define BUFF_LEN (128)
#define BUFF_LEN_HALF (64)

uint32_t audio_buff[BUFF_LEN] = {0};


void eko_tiger_p61_rhythm_setup()
{
	HAL_I2S_Transmit_DMA(&hi2s1, (uint16_t *) audio_buff, BUFF_LEN);
	sequencer_init();
	sequencer_set_bpm(160);
}

__attribute((always_inline)) inline
void getSamples(uint32_t* output, uint16_t startFrame, uint16_t endFrame)
{
	int32_t sample = 0;
	uint32_t u_sample = 0;

	for (uint16_t iFrame = startFrame; iFrame < endFrame; iFrame++)
	{
		sequencer_tick();
		sample =  drum_machine_generate_sample();

	    // +-32767 >> 8 = +-0x7FF
//		sample = sample >> 4;
		sample = sample >> 7;

		// +-0x7FF + 0x7FF = 0_0xFFF
		sample = sample + 0x7FFF;

		u_sample = (uint32_t) sample;

        output[iFrame] = u_sample;
	}
}

void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
	getSamples(audio_buff, 0, BUFF_LEN_HALF);
}

void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
	getSamples(audio_buff, BUFF_LEN_HALF, BUFF_LEN);
}
