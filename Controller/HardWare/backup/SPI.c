#include "SPI.h"

char DO[9],DI[9];

void SPI_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(SPI_PORT_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =CS_Pin; 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_Init(SPI_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =DO_Pin;
	GPIO_Init(SPI_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =CLK_Pin;
	GPIO_Init(SPI_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =DI_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(SPI_PORT,&GPIO_InitStructure);
}

void SPI_TransmitData(void){
	int i,verification=0;
	for(i=0;i<9;i++){
		CLK_HIGH;
		if(DO[i]==1) GPIO_SetBits(SPI_PORT,DO_Pin);
		else GPIO_ResetBits(SPI_PORT,DO_Pin);
		DI[i]=GPIO_ReadOutputDataBit(SPI_PORT,DI_Pin);
		CLK_LOW;
	}
	for(i=0;i<9;i++){
		verification+=DI[i];
	}
	if(verification%2==1) SPI_TransmitData();
}
