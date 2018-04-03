#ifndef SPI_H
#define SPI_H

#include "sys.h"

#define SPI_PORT GPIOB
#define SPI_PORT_CLK RCC_APB2Periph_GPIOB

#define CS_Pin GPIO_Pin_5
#define DI_Pin GPIO_Pin_6
#define DO_Pin GPIO_Pin_7
#define CLK_Pin GPIO_Pin_8

#define CLK_HIGH GPIO_SetBits(SPI_PORT,CLK_Pin)
#define CLK_LOW GPIO_ResetBits(SPI_PORT,CLK_Pin)

void SPI_init(void);
void SPI_TransmitData(void);

#endif
