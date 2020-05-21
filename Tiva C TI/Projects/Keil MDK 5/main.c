#include "TM4C123.h"
void writeGPIOdata (char port, uint8_t data);
int main()
{
	SYSCTL -> RCGCGPIO |= 0x20;
	GPIOF -> DIR |= 0x0E;
	GPIOF -> DEN |= 0x1E;
	GPIOF -> PUR |= 0x10;
	
	while(1)
	{
		if(!(GPIOF -> DATA & 0x10))
		{
			//GPIOF -> DATA |= 0x04;
			writeGPIOdata ('F', 0x02);
		}
		
		else writeGPIOdata ('F', 0x08);//*((unsigned int*) 0x400253FCU) &=~0x02;//GPIOF -> DATA &=~0x08;
	}
}

void writeGPIOdata (char port, uint8_t data)
{
/*
GPIO Port A (APB) base: 0x4000.4000
GPIO Port B (APB) base: 0x4000.5000
GPIO Port C (APB) base: 0x4000.6000
GPIO Port D (APB) base: 0x4000.7000
GPIO Port E (APB) base: 0x4002.4000
GPIO Port F (APB) base: 0x4002.5000
Offset 0x000
Type RW, reset 0x0000.0000*/  
 
// offset of 0x3FC was used for GPIO masking approach in cortex-M. 0x3FC ensures all data bits are written in memory.  
  
 if (port == 'A')
 {
   *((unsigned int*) 0x400043FCU) &= 0x00;
   *((unsigned int*) 0x400043FCU) |= data;
 }   
  else if (port == 'B')
 {
   *((unsigned int*) 0x400053FCU) &= 0x00;
   *((unsigned int*) 0x400053FCU) |= data;
 }
  else if (port == 'C')
 {
   *((unsigned int*) 0x400063FCU) &= 0x00;
   *((unsigned int*) 0x400063FCU) |= data;
 }
  else if (port == 'D')
 {
   *((unsigned int*) 0x400073FCU) &= 0x00;
   *((unsigned int*) 0x400073FCU) |= data;
 }
  else if (port == 'E')
 {
   *((unsigned int*) 0x400243FCU) &= 0x00;
   *((unsigned int*) 0x400243FCU) |= data;
 }
  else {
   *((unsigned int*) 0x400253FCU) &= 0x00;
   *((unsigned int*) 0x400253FCU) |= data;
 }
  
}