#include "TM4C123.h"
#include "Bit_Utilies.h"
void UART_init (void){

SET_BIT( SYSCTL_RCGCUART_R ,2); //to enable UART-2
SET_BIT( SYSCTL_RCGCGPIO_R ,3);  // to enable the clock of port D
while( GET_BIT(SYSCTL_PRGPIO_R,3)== 0); // Check that Clock is ready
CLR_BIT(UART2_CTL_R,0)  ; //disable UART2
	
	/*We want to baud rate 115.2k/s*/ 
	
	// (80M)/(115.2k*16) =43.40278	
UART2_IBRD_R =43;  // int(43.40278)
UART2_FBRD_R =26; // round(0.40278*64)

UART2_LCRH_R=0x70; // FIFO,1 stop bit,8 bit data

SET_BIT(UART2_CTL_R,0); //Enable UAERT2

GPIO_PORTD_AFSEL_R |= 0xC0; //RX >PD6 TX > PD7

GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&~0xFF000000)|(0x11000000); // to select UART put 1 on 4 bit of PD7 & PD6
GPIO_PORTD_DEN_R|=0XC0;                //make PD6  , PD7 as digital
	
	
}

