/*
PF4 GPIO SW1
PF0 GPIO SW2        <<<<<<<<--------- unlocking this switch
PF1 GPIO RGB LED (Red)
PF2 GPIO RGB LED (Blue)
PF3 GPIO RGD LED (Green)

*/
#include "TM4C123.h"
#include "GPIORegisterConfig.h"

void writeGPIOdata (char port, uint8_t data);
int main()
{
	EnableRCGCGPIO('F');   //SYSCTL -> RCGCGPIO |= 0x20;
	
	unlockGPIOport('F');  // unlocking commit register
	
	setGPIOcommit('F', 0x01); //unlocking SW2/PF0
	
	setGPIODIR('F', 0x0E); //GPIOF -> DIR |= 0x0E; Three LED are ouputs
	setGPIODEN('F', 0x1F); //GPIOF -> DEN |= 0x1E; 000sw1 GBRsw2-> lower 5 bits enabled
	
	setGPIOPUR('F', 0x10);//GPIOF -> PUR |= 0x11; // both switches are connected to PULL UP resistors, so active low
	
	
	while(1)
	{
		unsigned int val = readGPIODATA('F') & 0x11;
		
		if(val == 0x01)  writeGPIOdata ('F', 0x08);      // pressed sw# generates bit value 0 //checking if sw1 is pressed
		else if (val == 0x10)  writeGPIOdata ('F', 0x02);    //checking if sw1 is pressed
		else if (val == 0x00)  writeGPIOdata ('F', 0x04);     //checking if both sw1 and sw2 are pressed
		else                  { writeGPIOdata ('F', 0x00); 									// clearing latched value
														writeDIGITAL_GPIO( 'B', 0x20, 0x20);}//*((unsigned int*) 0x400253FCU) &=~0x02;//GPIOF -> DATA &=~0x08;
																																// or port B led on

// The FOLLOWING CODE creates a latching effect and LED lights up based on priority sequence so Blue one (with both R and Gs condition )
//never gets a chance for lighting up		
//		if(!(readGPIODATA('F') & 0x10))//if(!(GPIOF -> DATA & 0x10)) //checking if sw1 is pressed
//		{
//			writeGPIOdata ('F', 0x08);
//		}
//		
//		else if (!(readGPIODATA('F') & 0x01))//if(!(GPIOF -> DATA & 0x10)) //checking if sw2 is pressed
//		{
//			writeGPIOdata ('F', 0x02);
//		}
//		
//		else if (!(readGPIODATA('F') & 0x11))//if(!(GPIOF -> DATA & 0x10)) //checking if both sw1 and sw2 are pressed
//		{
//			writeGPIOdata ('F', 0x04);
//		}
// else                   writeDIGITAL_GPIO( 'B', 0x20, 0x20);//*((unsigned int*) 0x400253FCU) &=~0x02;//GPIOF -> DATA &=~0x08;
																																// or port B led on		
		
	}
	
	
}

