


///*PortF Switches*///
#define GPIO_SW1 0
#define GPIO_SW2 1
#define GPIO_SW_NOT_PRESSED 1



///*PortF LED color*///
#define GPIO_RED_LED 0
#define GPIO_GREEN_LED 1
#define GPIO_BLUE_LED 2

///*PortF LED state on/off*///
#define GPIO_LED_ON 1
#define GPIO_LED_OFF 0

unsigned char seven_segmentArray[10]={0x3F, 0x6, 0x5B, 0x4F, 0x66, 0x6D,0x7D, 0x27, 0x7F,0x6F };


/////////*functions*///////
void GPIO_initPortB();
void GPIO_initPortF(void);
unsigned char GPIO_getSwitchesValue(unsigned char sw);
void GPIO_setLedValue(unsigned char ledColor,unsigned char ledState);
void GPIO_PORTB_setPort(unsigned char sevenSegmentValues);
void GPIO_setSevenSegment (unsigned char valueOfSevenSegment);