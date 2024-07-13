/*
 * ov2640.h
 *
 *  Created on: Jul 5, 2024
 *      Author: ShiinaKaze
 */

#ifndef DSP_COMPONENTS_OV2640_OV2640_H_
#define DSP_COMPONENTS_OV2640_OV2640_H_

#include "main.h"

void OV2640_HW_Reset(void);
uint16_t OV2640_GetPID(void);
uint16_t OV2640_GetMID(void);
void OV2640_InitConfig(void);
void OV2640_Init(void);
void OV2640_InitConfig(void);
void OV2640_SetOutputSize(uint16_t width, uint16_t height);
void OV2640_TestCaptureUART(void);

#endif /* DSP_COMPONENTS_OV2640_OV2640_H_ */
