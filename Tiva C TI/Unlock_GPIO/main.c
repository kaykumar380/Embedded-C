#include "TM4C123.h"
#include "GPIORegisterConfig.h"

void writeGPIOdata (char port, uint8_t data);
int main()
{
	EnableRCGCGPIO('F');   //SYSCTL -> RCGCGPIO |= 0x20;
	
	setGPIODIR('F', 0x0E); //GPIOF -> DIR |= 0x0E;
	setGPIODEN('F', 0x1E); //GPIOF -> DEN |= 0x1E;
	
	setGPIOPUR('F', 0x10);//GPIOF -> PUR |= 0x10;
	
	
	while(1)
	{
		if(!(GPIOF -> DATA & 0x10))
		{
			//GPIOF -> DATA |= 0x04;
			writeGPIOdata ('F', 0x04);
		}
		
		else writeGPIOdata ('F', 0x02);//*((unsigned int*) 0x400253FCU) &=~0x02;//GPIOF -> DATA &=~0x08;
	}
	
	
}

