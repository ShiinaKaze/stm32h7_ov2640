/*
 * sccb.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ShiinaKaze
 */
#include "sccb.h"
#include "systick.h"

#define SCCB_GPIOx GPIOB
#define SIO_C_PIN GPIO_PIN_10
#define SIO_D_PIN GPIO_PIN_11

#define SCCB_ERROR 0xFF

#define SIO_C_WritePin(PinState) HAL_GPIO_WritePin(SCCB_GPIOx, SIO_C_PIN, PinState)
#define SIO_D_WritePin(PinState) HAL_GPIO_WritePin(SCCB_GPIOx, SIO_D_PIN, PinState)
#define SIO_D_ReadPin() HAL_GPIO_ReadPin(SCCB_GPIOx, SIO_D_PIN)
#define SCCB_Delay() Delay_us(5)

void SIO_D_SetInput(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = SIO_D_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SCCB_GPIOx, &GPIO_InitStruct);
}

void SIO_D_SetOutput(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = SIO_D_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SCCB_GPIOx, &GPIO_InitStruct);
}

void SWSCCB_Start(void) {
	// make sure SIO_C SIO_D high
	SIO_C_WritePin(GPIO_PIN_SET);
	SIO_D_WritePin(GPIO_PIN_SET);
	SCCB_Delay();
	// SCCB Start condition
	SIO_D_WritePin(GPIO_PIN_RESET);
	SCCB_Delay();
	SIO_C_WritePin(GPIO_PIN_RESET);
	SCCB_Delay();
}

void SWSCCB_Stop(void) {
	// make sure SIO_D high
	SIO_D_WritePin(GPIO_PIN_RESET);
	SCCB_Delay();
	// SCCB Stop condition
	SIO_C_WritePin(GPIO_PIN_SET);
	SCCB_Delay();
	SIO_D_WritePin(GPIO_PIN_SET);
	SCCB_Delay();
}

uint8_t SWSCCB_WriteByte(uint8_t byte) {
	uint8_t x_bit;
	for (uint8_t i = 0; i < 8; i++) {
		if (byte & 0x80) {
			SIO_D_WritePin(GPIO_PIN_SET);
		} else {
			SIO_D_WritePin(GPIO_PIN_RESET);
		}
		byte <<= 1;
		SCCB_Delay();
		SIO_C_WritePin(GPIO_PIN_SET);
		SCCB_Delay();
		SIO_C_WritePin(GPIO_PIN_RESET);
		SCCB_Delay();
	}
	SIO_D_SetInput();
	SCCB_Delay();
	SIO_C_WritePin(GPIO_PIN_SET);
	x_bit = SIO_D_ReadPin(); // X, Don't care bit, typical value is 0
	SCCB_Delay();
	SIO_C_WritePin(GPIO_PIN_RESET);
	SCCB_Delay();
	SIO_D_SetOutput();
	return x_bit;
}

uint8_t SWSCCB_ReadByte(void) {
	uint8_t byte = 0x00;
	SIO_D_SetInput();
	for (uint8_t i = 0; i < 8; i++) {
		SCCB_Delay();
		SIO_C_WritePin(GPIO_PIN_SET);
		if (SIO_D_ReadPin()) {
			byte |= (0x80 >> i);
		}
		SCCB_Delay();
		SIO_C_WritePin(GPIO_PIN_RESET);
		SCCB_Delay();
	}
	//master send NA bit
	SIO_D_WritePin(GPIO_PIN_SET);
	SCCB_Delay();
	SIO_C_WritePin(GPIO_PIN_SET);
	SCCB_Delay();
	SIO_C_WritePin(GPIO_PIN_RESET);
	SCCB_Delay();
	SIO_D_SetOutput();

	return byte;
}

void SWSCCB_WriteReg(uint8_t id_address, uint8_t sub_address, uint8_t data) {
	// 3-Phase Write
	SWSCCB_Start();
	SWSCCB_WriteByte(id_address);
	SWSCCB_WriteByte(sub_address);
	SWSCCB_WriteByte(data);
	SWSCCB_Stop();
}

uint8_t SWSCCB_ReadReg(uint8_t id_address, uint8_t sub_address) {
	uint8_t data;
	// 2-Phase Write
	SWSCCB_Start();
	SWSCCB_WriteByte(id_address);
	SWSCCB_WriteByte(sub_address);
	SWSCCB_Stop();
	// 2-Phase Read
	SWSCCB_Start();
	SWSCCB_WriteByte(id_address | 0x01);
	data = SWSCCB_ReadByte();
	SWSCCB_Stop();

	return data;
}
