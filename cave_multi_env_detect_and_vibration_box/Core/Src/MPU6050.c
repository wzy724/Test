/*
 * MPU6050.c
 *
 *  Created on: 2026年3月11日
 *      Author: 17629
 */

#include "MPU6050.h"
#include "MyI2C.h"

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();//演示用，先不做处理
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();//演示用，先不做处理
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();

	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS|0x01);
	MyI2C_ReceiveAck();
	uint8_t Temp=MyI2C_ReceiveByte();
	MyI2C_SendAck(1);//1不要了，0继续，就是最下方函数得应答依据
	MyI2C_Stop();
	return Temp;
}

void MPU6050_Init(void)
{
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);		//电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);			//配置寄存器，配置DLPF
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX,  int16_t *AccY,  int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	*AccX=(MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L));

	*AccY=(MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L));

	*AccZ=(MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L));

	*GyroX=(MPU6050_ReadReg(MPU6050_GYRO_XOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_GYRO_XOUT_L));

	*GyroY=(MPU6050_ReadReg(MPU6050_GYRO_YOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_GYRO_YOUT_L));

	*GyroZ=(MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H)<<8)|(MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L));
}
//上面是读关读。下面是根据i2c重复读取会循序地址接着像下读得代码可连续读取例如从加速的读到位置最后，包含温度都可以存在数组里，之后在外面用数组元素拼接
void MPU6050_ReadBurst(uint8_t startReg, int8_t *pData, uint8_t len)
{
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(startReg);
    MyI2C_ReceiveAck();
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceiveAck();
    for (uint8_t i=0; i<len;i++)
    {
        pData[i]=MyI2C_ReceiveByte();
        if (i<len-1)
        {
            MyI2C_SendAck(0);
        }
        else
        {
            MyI2C_SendAck(1);
        }
    }
    MyI2C_Stop();
}

