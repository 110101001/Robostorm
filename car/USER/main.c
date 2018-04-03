#include "main.h"

extern Rstruct RVals;
extern char JiaoZhunMeiYou;
int main(void)
{
	u8 sta=0;
	delay_init(84);
	gpio_init();
	IN1=IN2=IN3=IN4=0;
  TIM1_PWM_Init(ARR,1);
	TIM2_Init();
	Remote_Init();
	while(!JiaoZhunMeiYou);
	while(1){
//	while(NRF24L01_IRQ);
//		do{
//			sta=NRF24L01_Read_Reg(CD);
//			sta=NRF24L01_Read_Reg(STATUS);
//		}while(!(sta&RX_OK));
//		Remote_Receive(&RVals);
	  get_speed_state();
	}
}
