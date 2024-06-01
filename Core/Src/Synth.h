/*
 * Synth.h
 *
 *  Created on: Jun 1, 2024
 *      Author: Bianca
 */

#ifndef SRC_SYNTH_H_
#define SRC_SYNTH_H_

#define WTB_LEN 1024
#define BUFF_LEN 256
#define BULL_LEN_HALF 128
#define SAMPLE_RATE 48000

class Synth {
public:
	Synth();
	virtual ~Synth();

	float osc_wtb_pointer = 0;
	float osc;
	float signal = 0;
	float pitch = 0;

	float calculate_oscilator();
};

#endif /* SRC_SYNTH_H_ */
