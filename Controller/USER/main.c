#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "NRF24L01.h"


 int main(void)
 {		
	 u8 data[32]={0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA,0xEA},status;
	 u8 address[5]={0x34,0x43,0x10,0x10,0x01};
	 u8 sta;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	NRF_Init();
	SPI1_Read_Reg(STATUS,&sta,1);
	SPI1_Write_Reg(STATUS,&sta,1);
	while(NRF_Check());
	NRF_Configuration_TX(address);
	SPI1_Read_Reg(STATUS,&status,1);
	NRF_Data_Transmit(data,32);
 }
