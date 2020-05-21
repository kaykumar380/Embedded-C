#include "stdint.h"

void writeDIGITAL_GPIO(char port, uint8_t dir_vector, uint8_t data);
void EnableRCGCGPIO(char port);
void setGPIODIR(char port, uint8_t dir_vector);
void setGPIODEN(char port, uint8_t dir_vector);
void writeGPIOdata (char port, uint8_t data);
void delaay(int d);


void writeDIGITAL_GPIO(char port, uint8_t dir_vector, uint8_t data)
{
  EnableRCGCGPIO(port);
  setGPIODIR(port, dir_vector);
  setGPIODEN(port, dir_vector);
  writeGPIOdata(port, data);
}

void delaay(int d)
{
  while (d>0)
  {
    d--;
  }
}

void EnableRCGCGPIO(char port)
{
  // cortex M: TM4C123GH6PM RCGCGPIO base : 0x400F.E000 , offest 0x608
  unsigned int* rcgcgpio_mem = (unsigned int*)0x400FE608U;
  
  if (port == 'A')
    *rcgcgpio_mem |= 0x01U;
  else if (port == 'B')
    *rcgcgpio_mem |= 0x02U;
  else if (port == 'C')
    *rcgcgpio_mem |= 0x04U;
  else if (port == 'D')
    *rcgcgpio_mem |= 0x08U;
  else if (port == 'E')
    *rcgcgpio_mem |= 0x10U;
  else *rcgcgpio_mem |= 0x20U;
  
}

void setGPIODIR(char port, uint8_t dir_vector)
{
  // cortex M: TM4C123GH6PM GPIODIR 
/*GPIO Port A (APB) base: 0x4000.4000
GPIO Port B (APB) base: 0x4000.5000
GPIO Port C (APB) base: 0x4000.6000
GPIO Port D (APB) base: 0x4000.7000
GPIO Port E (APB) base: 0x4002.4000
GPIO Port F (APB) base: 0x4002.5000
Offset 0x400
Type RW, reset 0x0000.0000*/
//ONLY APB ports considered  
  
  if (port == 'A')
    *((unsigned int*) 0x40004400U) |= dir_vector;
  else if (port == 'B')
    *((unsigned int*) 0x40005400U) |= dir_vector;
  else if (port == 'C')
    *((unsigned int*) 0x40006400U) |= dir_vector;
  else if (port == 'D')
    *((unsigned int*) 0x40007400U) |= dir_vector;
  else if (port == 'E')
    *((unsigned int*) 0x40024400U) |= dir_vector;
  else *((unsigned int*) 0x40025400U) |= dir_vector;
  
}

void setGPIODEN(char port, uint8_t dir_vector)
{
/*GPIO Port A (APB) base: 0x4000.4000
GPIO Port B (APB) base: 0x4000.5000
GPIO Port C (APB) base: 0x4000.6000
GPIO Port D (APB) base: 0x4000.7000
GPIO Port E (APB) base: 0x4002.4000
GPIO Port F (APB) base: 0x4002.5000
Offset 0x51C*/
  
  if (port == 'A')
    *((unsigned int*) 0x4000451CU) |= dir_vector;
  else if (port == 'B')
    *((unsigned int*) 0x4000551CU) |= dir_vector;
  else if (port == 'C')
    *((unsigned int*) 0x4000651CU) |= dir_vector;
  else if (port == 'D')
    *((unsigned int*) 0x4000751CU) |= dir_vector;
  else if (port == 'E')
    *((unsigned int*) 0x4002451CU) |= dir_vector;
  else *((unsigned int*) 0x4002551CU) |= dir_vector;
    
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