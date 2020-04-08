#include <stdint.h>
#include <stdbool.h>
#include "RG_Toggle.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "C:\ti\TivaWare_C_Series-2.1.4.178\inc\tm4c123gh6pm.h"
#include "C:\ti\TivaWare_C_Series-2.1.4.178\driverlib\sysctl.h"

#define SW1	     		GPIO_PIN_4		// PF4
#define SW2      		GPIO_PIN_0		// PF0
#define red_LED     GPIO_PIN_1		// 0x02
#define blue_LED    GPIO_PIN_2		// 0x04
#define green_LED		GPIO_PIN_3		// 0x08

//*****************************************************************************
void
PortFunctionInit(void)
{
    //
    // Enable Peripheral Clocks 
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    //First open the lock and select the bits we want to modify in the GPIO commit register.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

    //
    //Now modify the configuration of the pins that we unlocked.
    //
	
    //
    // Enable pin PF0 for GPIOInput
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW2);

    //
    // Enable pin PF3 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, green_LED);

    //
    // Enable pin PF4 for GPIOInput
    //
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW1);

    //
    // Enable pin PF1 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, red_LED);

    //
    // Enable pin PF2 for GPIOOutput
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, blue_LED);


// ****** Initialized by PinMux Utility *************** 
	
    // enable pullup resistors using bitwise OR of PF4(0x10), PF0(0x01)
    GPIO_PORTF_PUR_R |= 0x11;        

}


void DelayInSec(double delay_in_s)
{
    // SysCtlClockGet() returns the PIOSC clock frequency of the Tiva (16 MHz +/- 1%)
    // 1 clock cycle (in seconds) = 1 / SysCtlClockGet() second
    // 1 loop of SysCtlDelay = 3 clock cycles = 3 / SysCtlClockGet() 
    // 1 second = SysCtlClockGet()  / 3
    SysCtlDelay(delay_in_s * (SysCtlClockGet()  / 3));
}
	

int main(void)
{
    uint8_t LED_data;
	
    // initializes the GPIO ports	
    PortFunctionInit();
		signed char c=0;
		LED_data^=blue_LED;	
		LED_data^=red_LED;
		LED_data^=green_LED;
	
    while(1)
		{
			while(GPIOPinRead(GPIO_PORTF_BASE, SW2)==0x00) //SW2 is pressed
				{
					c=0;
					if(c<=7)
					{
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
						c=c+1; //c = 1
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
							break;}
					
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
						c=c+1; //c = 2
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
						break;}
						
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED off
						c=c+1; //c = 3
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
							break;}
						
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
						c=c+1; //c = 4
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
						break;}
						
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED off
						c=c+1; //c = 5
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
							break;}
						
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED off
						c=c+1; //c = 6
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
							break;}
						
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED off
						c=c+1;//c = 7
						DelayInSec(0.5);// about 0.5 second delay
						if(GPIOPinRead(GPIO_PORTF_BASE, SW2)!=0x00){
							break;}
						}
						
				}

				if(GPIOPinRead(GPIO_PORTF_BASE, SW1)==0x00) //SW1 is pressed 
					{
						switch(c)
						{
							
							case 1:
								LED_data^=blue_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
								DelayInSec(0.5);
								break;
							
							case 2:
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED off
							LED_data^=green_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED on
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
								DelayInSec(0.5);
								break;
							
							case 3:
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED off
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
							LED_data^=red_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED on
								DelayInSec(0.5);
								break;
							
							case 4:
								LED_data^=blue_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
							LED_data^=green_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED on
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, 0x00);	// red LED off
								DelayInSec(0.5);
								break;
							
							case 5:
								LED_data^=blue_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00); // green LED off
							LED_data^=red_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED on
								DelayInSec(0.5);
								break;
							
							case 6:
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	//blue LED off
							LED_data^=green_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED on
							LED_data^=red_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED on
								DelayInSec(0.5);
								break;
							
							case 7:
								LED_data^=blue_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, LED_data);	//blue LED on
							LED_data^=green_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, green_LED, LED_data); // green LED on
							LED_data^=red_LED;	
								GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data);	// red LED on
								DelayInSec(0.5);
								break;
								
						}
					}
				else //SW1 is not pressed, toggle red LED (PF3) which is the default
					{
						GPIOPinWrite(GPIO_PORTF_BASE, green_LED, 0x00);	// green LED off
						GPIOPinWrite(GPIO_PORTF_BASE, blue_LED, 0x00);	// green LED off

						DelayInSec(0.5);   // about 0.5 second delay
						LED_data^=red_LED; // bitwise XOR red LED (PF1)
						GPIOPinWrite(GPIO_PORTF_BASE, red_LED, LED_data); // red LED on
					}
				}		
					
    
}
