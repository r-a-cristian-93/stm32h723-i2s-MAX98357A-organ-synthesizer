/*
 * Synth.cpp
 *
 *  Created on: Jun 1, 2024
 *      Author: Bianca
 */
#include "stm32h7xx_hal.h"

#include "Synth.h"
#include "wavetable.h"

Synth::Synth() {
	// TODO Auto-generated constructor stub

}

Synth::~Synth() {
	// TODO Auto-generated destructor stub
}

//#define LIM 32767.0f
#define LIM 32767.0f

float Synth::calculate_oscilator()
{
	uint16_t a, b;
	float da, db;

	float osc_wtb_inc = WTB_LEN * (pitch) / SAMPLE_RATE;

	osc_wtb_pointer += osc_wtb_inc;

	if (osc_wtb_pointer > WTB_LEN)
	{
		osc_wtb_pointer -= WTB_LEN;
	}

	a = (int)osc_wtb_pointer;
	da = osc_wtb_pointer - a;
	b = a + 1;
	db = b - osc_wtb_pointer;

	if (b >= WTB_LEN)
	{
		b = 0;
	}

	osc = da* triangle[a] + db * triangle[b];

	signal = osc * LIM;

	if (signal > LIM)
	{
		signal = LIM;
	}
	if (signal < -LIM)
	{
		signal = -LIM;
	}

	return signal;
}
