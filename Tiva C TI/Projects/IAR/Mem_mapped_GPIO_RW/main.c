// Push and hold an active low switch to light up an LED*/
/*PF4 GPIO SW1
  PF0 GPIO SW2
  PF1 GPIO RGB LED (Red)
  PF2 GPIO RGB LED (Blue)
  PF3 GPIO RGD LED (Green)*/



#include "stdint.h"
#include "write_func.h"

void setGPIOPUR(char port, uint8_t pur_vector);
void setGPIOcommit(char port, uint8_t commit_vector);
unsigned int readGPIODATA(char port);

int main()
{
  /*EnableRCGCGPIO('F'); // Enable Port F
  setGPIODIR('F', 0x0E); // set GPIO direction; 000(PF4 = 0) (PF3= Greeen LED=1)000;
  setGPIOPUR('F', 0x10); // Pull up Register at SW1; 000(SW1=1) 0000
  setGPIODEN('F', 0x1E); // Digital Enable , 000(SW1=1) (LEDG=1)000
  
  while(1)
  {
    if(readGPIODATA('F') & 0x10 == 0x00) // checking if SW1 i slow => pressed
    {
      writeGPIOdata ('F', 0x08); // LED on
      writeGPIOdata ('F', 0x02);
    }
    
    else writeGPIOdata ('F', 0x00); // LED off
  }
  */
  writeDIGITAL_GPIO('F', 0x0E, 0x02);
}


void setGPIOPUR(char port, uint8_t pur_vector)
{
  /*GPIO Pull-Up Select (GPIOPUR)
GPIO Port A (APB) base: 0x4000.4000
GPIO Port B (APB) base: 0x4000.5000
GPIO Port C (APB) base: 0x4000.6000
GPIO Port D (APB) base: 0x4000.7000
GPIO Port E (APB) base: 0x4002.4000
GPIO Port F (APB) base: 0x4002.5000
Offset 0x510*/
  if (port == 'A')
    *((unsigned int*) 0x40004510U) |= pur_vector;
  else if (port == 'B')
    *((unsigned int*) 0x40005510U) |= pur_vector;
  else if (port == 'C')
    *((unsigned int*) 0x40006510U) |= pur_vector;
  else if (port == 'D')
    *((unsigned int*) 0x40007510U) |= pur_vector;
  else if (port == 'E')
    *((unsigned int*) 0x40024510U) |= pur_vector;
  else *((unsigned int*) 0x40025510U) |= pur_vector;
  
}

void setGPIOcommit(char port, uint8_t commit_vector)
{
  /*GPIO Commit (GPIOCR)
GPIO Port A (APB) base: 0x4000.4000
GPIO Port B (APB) base: 0x4000.5000
GPIO Port C (APB) base: 0x4000.6000
GPIO Port D (APB) base: 0x4000.7000
GPIO Port E (APB) base: 0x4002.4000
GPIO Port F (APB) base: 0x4002.5000
Offset 0x524 */
  if (port == 'A')
    *((unsigned int*) 0x40004524U) |= commit_vector;
  else if (port == 'B')
    *((unsigned int*) 0x40005524U) |= commit_vector;
  else if (port == 'C')
    *((unsigned int*) 0x40006524U) |= commit_vector;
  else if (port == 'D')
    *((unsigned int*) 0x40007524U) |= commit_vector;
  else if (port == 'E')
    *((unsigned int*) 0x40024524U) |= commit_vector;
  else *((unsigned int*) 0x40025524U) |= commit_vector;
   
}

unsigned int readGPIODATA(char port)
{
       if (port == 'A') return *((unsigned int*) 0x400043FCU);
  else if (port == 'B') return *((unsigned int*) 0x400053FCU);
  else if (port == 'C') return *((unsigned int*) 0x400063FCU);
  else if (port == 'D') return *((unsigned int*) 0x400073FCU);
  else if (port == 'E') return *((unsigned int*) 0x400243FCU);
                   else return *((unsigned int*) 0x400253FCU);
}

