/*
 * sccb.h
 *
 *  Created on: Jul 5, 2024
 *      Author: ShiinaKaze
 */

#ifndef DSP_COMPONENTS_OV2640_SCCB_H_
#define DSP_COMPONENTS_OV2640_SCCB_H_

#include "main.h"
void SWSCCB_Init(void);
void SWSCCB_WriteReg(uint8_t id_address, uint8_t sub_address, uint8_t data);
uint8_t SWSCCB_ReadReg(uint8_t id_address, uint8_t sub_address);

#endif /* DSP_COMPONENTS_OV2640_SCCB_H_ */
