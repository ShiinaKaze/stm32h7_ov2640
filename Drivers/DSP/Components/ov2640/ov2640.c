/*
 * ov2640.c
 *
 *  Created on: Jul 5, 2024
 *      Author: ShiinaKaze
 */

#include "ov2640.h"
#include "ov2640_cfg.h"
#include "sccb.h"
#include "systick.h"

#define OV2640_DEVICE_ADDRESS 0x60

#define PWDN_RESET_GPIOx GPIOD
#define PWDN_PIN GPIO_PIN_1
#define RESET_PIN GPIO_PIN_2

#define SCCB_Write(sub_address, data) SWSCCB_WriteReg(OV2640_DEVICE_ADDRESS, sub_address, data)
#define SCCB_Read(sub_address) SWSCCB_ReadReg(OV2640_DEVICE_ADDRESS, sub_address)

void OV2640_HW_Reset(void) {
	// Reset Camera
	HAL_GPIO_WritePin(PWDN_RESET_GPIOx, RESET_PIN, GPIO_PIN_RESET);
	Delay_ms(10);
	HAL_GPIO_WritePin(PWDN_RESET_GPIOx, RESET_PIN, GPIO_PIN_SET);
	Delay_ms(10);
}

void OV2640_SetPowerDownMode(GPIO_PinState PinState) {
	// Set Device into Normal Mode
	if (PinState) {
		HAL_GPIO_WritePin(PWDN_RESET_GPIOx, PWDN_PIN, GPIO_PIN_SET);
	} else {
		HAL_GPIO_WritePin(PWDN_RESET_GPIOx, PWDN_PIN, GPIO_PIN_RESET);
	}
}

uint16_t OV2640_GetPID(void) {
	SCCB_Write(0xFF, 0x01);
	uint16_t PID = SCCB_Read(OV2640_SENSOR_PIDH);
	PID <<= 8;
	PID |= SCCB_Read(OV2640_SENSOR_PIDL);
	return PID;
}

uint16_t OV2640_GetMID(void) {
	SCCB_Write(0xFF, 0x01);
	uint16_t MID = SCCB_Read(OV2640_SENSOR_MIDH);
	MID <<= 8;
	MID |= SCCB_Read(OV2640_SENSOR_MIDL);
	return MID;
}

void OV2640_InitConfig(void) {
	uint32_t cfg_len = sizeof(ov2640_qvga_cfg) / sizeof(ov2640_qvga_cfg[0]);
	for (uint32_t i = 0; i < cfg_len; i++) {
		SCCB_Write(ov2640_qvga_cfg[i][0], ov2640_qvga_cfg[i][1]);
	}
}

void OV2640_SetOutputJPEG(void) {
	uint16_t cfg_len = sizeof(ov2640_yuv422_cfg) / sizeof(ov2640_yuv422_cfg[0]);
	for (uint16_t cfg_index = 0; cfg_index < cfg_len; cfg_index++) {
		SCCB_Write(ov2640_yuv422_cfg[cfg_index][0],
				ov2640_yuv422_cfg[cfg_index][1]);
	}
	cfg_len = sizeof(ov2640_jpeg_cfg) / sizeof(ov2640_jpeg_cfg[0]);
	for (uint16_t cfg_index = 0; cfg_index < cfg_len; cfg_index++) {
		SCCB_Write(ov2640_jpeg_cfg[cfg_index][0], ov2640_jpeg_cfg[cfg_index][1]);
	}
}

void OV2640_SetOutputSize(uint16_t width, uint16_t height) {
	uint16_t output_width;
	uint16_t output_height;

	output_width = width >> 2;
	output_height = height >> 2;

	SCCB_Write(0xFF, 0x00);
	SCCB_Write(OV2640_DSP_RESET, 0x04);
	SCCB_Write(OV2640_DSP_ZMOW, (uint8_t ) (output_width & 0x00FF));
	SCCB_Write(OV2640_DSP_ZMOH, (uint8_t ) (output_height & 0x00FF));
	SCCB_Write(OV2640_DSP_ZMHH,
			((uint8_t ) (output_width >> 8) & 0x03)
					| ((uint8_t ) (output_height >> 6) & 0x04));
	SCCB_Write(OV2640_DSP_RESET, 0x00);
}

void OV2640_SetClockDivision(uint8_t Clock, uint8_t DVP_Clock) {
	SCCB_Write(0XFF, 0x00);
	SCCB_Write(0XD3, DVP_Clock); // DVP PCLK division
	SCCB_Write(0XFF, 0x01);
	SCCB_Write(0X11, Clock); // CLK division
}

void OV2640_Init(void) {
	OV2640_HW_Reset();
	OV2640_SetPowerDownMode(0);
	OV2640_InitConfig();
	OV2640_SetOutputJPEG();
}

