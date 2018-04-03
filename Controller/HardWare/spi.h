#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

#define SPI1_PORT GPIOA
#define CSN_Pin GPIO_Pin_3

#define Read_Com 0x00
#define Write_Com 0x20
 				  	    						
#define CSN_HIGH GPIO_SetBits(SPI1_PORT,CSN_Pin)
#define CSN_LOW GPIO_ResetBits(SPI1_PORT,CSN_Pin)


void SPI1_Init(void);			 //初始化SPI口
void SPI1_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
u8 SPI1_Write_Reg(u8 reg,u8 *data,int amount);
void SPI1_Read_Reg(u8 reg,u8 *data,int amount);
		 
#endif

