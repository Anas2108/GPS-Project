 #include "GPIO.h"
#include "Bit_Utilies.h"
#include "TM4C123.h"

void GPIO_initPortB(){
SET_BIT(SYSCTL_RCGCGPIO_R,1); // BIT 1 --> PORT B
while(GET_BIT(SYSCTL_PRGPIO_R,1)== 0); // Check that Clock is ready
GPIO_PORTB_CR_R |= 0xFF; // allow changes to PB7-PB0
GPIO_PORTB_AMSEL_R &= 0x0; // Disable Analog
GPIO_PORTB_PCTL_R &= 0x0; // PCTL GPIO on PB7-PB0
GPIO_PORTB_DIR_R |= 0xFF; // PF4 PF0 --> in, PB7-PB0--> out
GPIO_PORTB_AFSEL_R &= 0x00; // Disable alt funct on PB7-PB0
GPIO_PORTB_DEN_R |= 0xFF; // Enable digital I/O on PF4-0

}



void GPIO_initPortF(void){
SYSCTL_RCGCGPIO_R |=0x20;
	while((SYSCTL_PRGPIO_R &0x20)==0);
	GPIO_PORTF_LOCK_R= GPIO_LOCK_KEY;
	GPIO_PORTF_CR_R |=0x1F;
	GPIO_PORTF_AFSEL_R &=0x00;
	GPIO_PORTF_AMSEL_R &=0x00;
	GPIO_PORTF_DEN_R|=0x1F;
	GPIO_PORTF_PCTL_R&=0x00000000;
	GPIO_PORTF_PUR_R |= 0x11; 
	GPIO_PORTF_DIR_R|=0x0E;
	GPIO_PORTF_DATA_R&=~0x0E;
	
	
}

unsigned char GPIO_getSwitchesValue(unsigned char sw){
switch (sw){
	case GPIO_SW1 :return GET_BIT(GPIO_PORTF_DATA_R,4); break;
	
	case GPIO_SW2 :return GET_BIT(GPIO_PORTF_DATA_R,0); break;
 	
	default : return 0;
	
   }

}

void GPIO_setLedValue(unsigned char ledColor,unsigned char ledState){ // two parameters one to select led second to on/off
	 switch (ledColor){
		 case GPIO_RED_LED : switch(ledState)
			 
			 {case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,1);break;
				 case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,1);break;
			 default : break;
		   } break;
			 
			 case GPIO_BLUE_LED : switch(ledState)
				 
			 {case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,2);break;
				 case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,2);break;
				 default : break;
		   } break;
			 
			 case GPIO_GREEN_LED : switch(ledState)
				 
			 {case GPIO_LED_OFF: CLR_BIT(GPIO_PORTF_DATA_R,3);break;
				 case GPIO_LED_ON: SET_BIT(GPIO_PORTF_DATA_R,3);break;
				 default : break;
		   } break;
	 
				 default : break;
	 }
}


void GPIO_PORTB_setPort(unsigned char sevenSegmentValues){
	
GPIO_PORTB_DATA_R=sevenSegmentValues;

}

void GPIO_setSevenSegment (unsigned char valueOfSevenSegment){// from 0:9

GPIO_PORTB_setPort (seven_segmentArray[valueOfSevenSegment]);
}
	


/////*two var to save the value from switches*////
unsigned char SW1,SW2;

int main(){

GPIO_initPortF();
	
GPIO_initPortB();	

while(1){

SW1=GPIO_getSwitchesValue(GPIO_SW1);
SW2=GPIO_getSwitchesValue(GPIO_SW2);	
if(SW1!=GPIO_SW_NOT_PRESSED&&SW2!=GPIO_SW_NOT_PRESSED){
    GPIO_setLedValue(GPIO_RED_LED,GPIO_LED_ON);
	  GPIO_setLedValue(GPIO_BLUE_LED,GPIO_LED_OFF);
		GPIO_setLedValue(GPIO_GREEN_LED,GPIO_LED_OFF);
  }
	 else if(SW1!=GPIO_SW_NOT_PRESSED&&SW2==GPIO_SW_NOT_PRESSED){
     GPIO_setLedValue(GPIO_BLUE_LED,GPIO_LED_ON);
		 GPIO_setLedValue(GPIO_RED_LED,GPIO_LED_OFF);
	 	 GPIO_setLedValue(GPIO_GREEN_LED,GPIO_LED_OFF);
  }
	 else if(SW1==GPIO_SW_NOT_PRESSED&&SW2!=GPIO_SW_NOT_PRESSED){
     GPIO_setLedValue(GPIO_GREEN_LED,GPIO_LED_ON);
		 GPIO_setLedValue(GPIO_BLUE_LED,GPIO_LED_OFF);
		 GPIO_setLedValue(GPIO_RED_LED,GPIO_LED_OFF);
  }
	 else if(SW1==GPIO_SW_NOT_PRESSED&&SW2==GPIO_SW_NOT_PRESSED){
    GPIO_setLedValue(GPIO_RED_LED,GPIO_LED_OFF);
		GPIO_setLedValue(GPIO_BLUE_LED,GPIO_LED_OFF);
		GPIO_setLedValue(GPIO_GREEN_LED,GPIO_LED_OFF);
  }



 
 }
}