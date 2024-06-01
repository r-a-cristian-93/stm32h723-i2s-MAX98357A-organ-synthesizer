/*
 * Codec.h
 *
 *  Created on: Jun 1, 2024
 *      Author: Bianca
 */

#ifndef SRC_CODEC_H_
#define SRC_CODEC_H_

#include "stm32h7xx_hal.h"

#define AUDIO_I2C_ADDR 0x94

class Codec {
public:
	Codec();
	virtual ~Codec();

	uint8_t init();

private:
	uint8_t write(uint8_t reg, uint8_t val);
};

#endif /* SRC_CODEC_H_ */
