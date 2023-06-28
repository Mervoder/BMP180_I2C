/*
 * BMP180.c
 *
 *  Created on: Jun 27, 2023
 *      Author: Oğuz Kaan
 */

#include"BMP180.h"

// Calibration Values
int16_t AC1;
int16_t AC2;
int16_t AC3;
int16_t AC4;
int16_t AC5;
int16_t AC6;
int16_t B1;
int16_t B2;
int16_t MB ;
int16_t MC ;
int16_t MD;


//Temperature Values
int16_t unComp_Temp, unComp_Press;
float Temperature, Pressure;
int32_t tX1, tX2, tB5;

void BMP180_Init()
{
	// checking the device
	if(HAL_I2C_IsDeviceReady(&hi2c1, BMP180_Write_Address, 1, 1000) != HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET); // device is not ready
	}

	BMP180_Get_Calibration_Value();

}


void BMP180_GetCalibration()
{



}


void BMP180_Get_Calibration_Value()
{
	uint8_t calibBuff[BMP180_CALIBRATION_VALUE_LENGHT]= {0};

	HAL_I2C_Mem_Read(&hi2c1, BMP180_Read_Address, BMP180_Calibration_Start_Addr, 1, calibBuff, BMP180_CALIBRATION_VALUE_LENGHT, 10000);

	AC1 = (int16_t)((calibBuff[0] << 8) | (calibBuff[1]) );
	AC2 = (int16_t)((calibBuff[2] << 8) | (calibBuff[3]) );
	AC3 = (int16_t)((calibBuff[4] << 8) | (calibBuff[5]) );
	AC4 = (int16_t)((calibBuff[6] << 8) | (calibBuff[7]) );
	AC5 = (int16_t)((calibBuff[8] << 8) | (calibBuff[9]) );
	AC6 = (int16_t)((calibBuff[10] << 8) | (calibBuff[11]) );

	B1 =(int16_t)( calibBuff[12] << 8 | calibBuff[13]);
	B2 =(int16_t)(calibBuff[14] << 8 | calibBuff[15]);

	MB = (int16_t)(calibBuff[16] << 8 | calibBuff[17]);
	MC =(int16_t) (calibBuff[18] << 8 | calibBuff[19]);
	MD =(int16_t) (calibBuff[20] << 8 | calibBuff[21]);

/*
 * 	if((AC1 == 0x00) || (AC2 == 0x00) || (AC3 == 0x00) || (AC4 == 0x00) || (AC5 == 0x00) || (AC6 == 0x00))
	{
		// calib datas errors
	}
	if((B1 == 0x00) || (B2 == 0x00) || (MB == 0x00) || (MC == 0x00) || (MD == 0x00) )
		{
			// calib datas errors
		}
	*/
}

void BMP180_Get_Uncompansated_Temp_Val(void)
{
	uint8_t rData[2] = {0};
	uint8_t wData[1];
	wData[0] = 0x2E;
	// datasheet şematiğinde var
	HAL_I2C_Mem_Write(&hi2c1, BMP180_Write_Address, 0xF4, 1, wData, 1, 1000);
	// wait 4.5 ms then read tha data
	HAL_Delay(5);

	HAL_I2C_Mem_Read(&hi2c1, BMP180_Read_Address, 0xF6, 1, rData, 2, 1000);

	unComp_Temp = (int16_t) ((rData[0] << 8) | rData[1]);
}

int32_t BMP180_Get_Temperature(void)
{
	BMP180_Get_Uncompansated_Temp_Val();

	tX1 = (((int32_t)unComp_Temp - (int32_t)AC6) * (int32_t)AC5) / 32768; // 2'15
	tX2 = ((int32_t) MC *2048) / (tX1 + (int32_t)MD);
	tB5 = tX1 + tX2;

	Temperature = (float)(tB5 + 8 )/16;
	return Temperature*0.1;
}


void BMP180_Get_Uncompansated_Pressure_Val(void)
{

}
int32_t BMP180_Get_Pressure(void)
{

	return 0;
}




