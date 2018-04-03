#include "NRF24L01.h"
/**
  ******************************************************************************
  * @author  WuPeiCong
  * @version V1.56
  * @date    2016-05-7
	******************************************************************************
*/
void NRF_Init(){

	GPIO_InitTypeDef GPIO_InitStructure;
	SPI1_Init();
	SPI1_SetSpeed(SPI_BaudRatePrescaler_8);
	GPIO_InitStructure.GPIO_Pin = IRQ_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,CE_Pin);
	CSN_HIGH;
	CE_LOW;
}

int NRF_Check(){
	int retry=0,i;
	u8 buff[5]={0xC2,0xC2,0xC2,0xC2,0xC2};
	u8 buff1[5];
	GPIO_ResetBits(GPIOA,CE_Pin);
	do{
	SPI1_Write_Reg(TX_ADDR,buff,5);
	SPI1_Read_Reg(TX_ADDR,buff1,5);
		for(i=0;i<5;i++){
			if(buff[i]!=buff1[i]) break;
		}
	if((retry++)==100) return 1;
	}while(i!=5);
	return 0;
}

void NRF_Configuration_TX(u8 *address){//
	//address是目标地址，RoboStorm的每一辆小车都需要不同的地址以免相互混淆.请选手不要改动以免影响正常操作
	u8 config=TX_CONFIGURATION,
	en_aa=EN_AA_CONFIGURATION,
	en_rxaddr=EN_RXADDR_CONFIGURATION,
	setup_rete=SETUP_RETR_CONFIGURATION,
	rf_ch=RF_CH_CONFIGURATION,
	rf_setup=RF_SETUP_CONFIGURATION;
	//配置寄存器
	SPI1_Write_Reg(RX_ADDR_P0,address,5);
	SPI1_Write_Reg(TX_ADDR,address,5);
	SPI1_Write_Reg(EN_AA,&en_aa,1);
	SPI1_Write_Reg(RF_CH,&rf_ch,1);
	SPI1_Write_Reg(EN_RXADDR,&en_rxaddr,1);
	SPI1_Write_Reg(SETUP_RETR,&setup_rete,1);
	SPI1_Write_Reg(RF_SETUP,&rf_setup,1);
	SPI1_Write_Reg(CONFIG,&config,1);
	CE_LOW;//拉高CE，进入发射模式
	delay_ms(15);
}

void NRF_Configuration_RX(u8 *address){
	u8 config=RX_CONFIGURATION,
	en_aa=EN_AA_CONFIGURATION,
	en_rxaddr=EN_RXADDR_CONFIGURATION,
	setup_rete=SETUP_RETR_CONFIGURATION,
	rf_setup=RF_SETUP_CONFIGURATION,
	rx_pw_p0=DATA_LEN,
	setup_aw=SETUP_AW_CONFIGURATION;
	
	//配置寄存器
	
	SPI1_Write_Reg(RX_ADDR_P0,address,5);
	SPI1_Write_Reg(CONFIG,&config,1);
	SPI1_Write_Reg(SETUP_AW,&setup_aw,1);
	SPI1_Write_Reg(EN_AA,&en_aa,1);
	SPI1_Write_Reg(EN_RXADDR,&en_rxaddr,1);
	SPI1_Write_Reg(SETUP_RETR,&setup_rete,1);
	SPI1_Write_Reg(RF_SETUP,&rf_setup,1);
	SPI1_Write_Reg(RX_PW_P0,&rx_pw_p0,1);
	SPI1_Read_Reg(CONFIG,&config,1);
	config=0;
	CE_LOW;
}


void NRF_Data_Transmit(u8 *data,int amount){
	u8 status,flush=0xff;
	CE_LOW;
	SPI1_Write_Reg(TX_PLD,data,amount);
	CE_HIGH;
	delay_us(10);
	while(GPIO_ReadInputDataBit(SPI1_PORT,IRQ_Pin));
	SPI1_Read_Reg(STATUS,&status,1);
	SPI1_Write_Reg(STATUS,&status,1);
	if(status&TX_OK) SPI1_Write_Reg(FLUSH_RX,&flush,1);
}

void NRF_Data_Receive(u8 *data,int amount){
	u8 status,flush=0xff;
	SPI1_Read_Reg(STATUS,&status,1);
	SPI1_Write_Reg(STATUS,&status,1);
	if(status&RX_OK){
		SPI1_Write_Reg(FLUSH_RX,&flush,1);
		SPI1_Read_Reg(RX_PLD,data,amount);
	}
}
