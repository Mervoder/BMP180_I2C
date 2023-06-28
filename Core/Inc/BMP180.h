/*
 * BMP180.h
 *
 *  Created on: Jun 27, 2023
 *      Author: Oğuz Kaan
 */

#ifndef INC_BMP180_H_
#define INC_BMP180_H_

#include<stm32f4xx_hal.h>

extern I2C_HandleTypeDef hi2c1;

// Device Address
#define BMP180_Read_Address   0xEF
#define BMP180_Write_Address  0xEE


// Calibration Values Lenght -----------------------------------------

#define BMP180_CALIBRATION_VALUE_LENGHT 22 // 11 words 16 bits
#define BMP180_Calibration_Start_Addr   0xAA


void BMP180_Init(void);
void BMP180_GetCalibration(void);
void BMP180_Get_Calibration_Value(void);
void BMP180_Get_Uncompansated_Temp_Val(void);
int32_t BMP180_Get_Temperature(void);
void BMP180_Get_Uncompansated_Pressure_Val(void);
int32_t BMP180_Get_Pressure(void);


#endif /* INC_BMP180_H_ */
