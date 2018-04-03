#include "RemoteTask.h"
/**
  ******************************************************************************
  * @author  WuPeiCong
  * @version V1.56
  * @date    2016-05-7
	******************************************************************************
*/
char data[3];

void Remote_Init(u8 *address){
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	SPI1_Init();
	NRF_Init();
	NRF_Configuration_TX(address);
	//≈‰÷√TIM3
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 

	TIM_TimeBaseStructure.TIM_Period = 700;
	TIM_TimeBaseStructure.TIM_Prescaler =7199;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
	TIM_ITConfig(TIM3,TIM_IT_Update ,ENABLE );
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	TIM_Cmd(TIM3, ENABLE);
	
}

void Remote_Encode(int X_offset,int Y_offset){
	data[0]=X_offset/0x10;
	data[1]=Y_offset/0x10;
	data[2]=X_offset%0x10+0x10*Y_offset%0x10;
}

void Remote_Decode(int *X_offset,int *Y_offset){
	*X_offset=data[0]*0x10+data[2]%0x10;
	*Y_offset=data[1]*0x10+data[2]/0x10;
}


void TIM3_IRQHandler(void)   //TIM3÷–∂œ
{	
	u8 data;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET){
		
//		Remote_Encode(X_offset,Y_offset);
//		NRF_Data_Transmit(&data,3);
		
	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
}
