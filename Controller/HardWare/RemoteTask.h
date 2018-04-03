#ifndef REMOTETASK_H
#define REMOTETASK_H

#include "sys.h"
#include "SPI.h"
#include "delay.h"
#include "NRF24L01.h"

void Remote_Init(u8 *address);
void Remote_Send(int X_offset,int Y_offset);
void Remote_Encode(int X_offset,int Y_offset);
void Remote_Decode(int *X_offset,int *Y_offset);
void TIM3_IRQHandler(void);

#endif
