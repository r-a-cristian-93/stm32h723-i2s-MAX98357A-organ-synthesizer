/*
 * Codec.cpp
 *
 *  Created on: Jun 1, 2024
 *      Author: Bianca
 */

#include "Codec.h"
#include "i2c.h"
#include "gpio.h"

Codec::Codec() {
	// TODO Auto-generated constructor stub

}

Codec::~Codec() {
	// TODO Auto-generated destructor stub
}

uint8_t Codec::init()
{
	uint8_t codec_status = HAL_OK;
	HAL_GPIO_WritePin(CODEC_RESET_GPIO_Port, CODEC_RESET_Pin, GPIO_PIN_SET);


//	MAX98357A won't need this

//	codec_status += write(0x40, 0xaf);
//	codec_status += write(0x06, 0x07);
//	codec_status += write(0x02, 0x93);

	return codec_status;
}

uint8_t Codec::write(uint8_t reg, uint8_t val)
{
	HAL_StatusTypeDef codec_status = HAL_I2C_Mem_Write(&hi2c1, AUDIO_I2C_ADDR, reg, 1, &val, sizeof(val), HAL_MAX_DELAY);

	return codec_status;
}
