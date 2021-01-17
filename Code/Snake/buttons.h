#ifndef buttons_h
#define buttons_h


#define BUTTON_1_POS 1
#define BUTTON_2_POS 2
#define BUTTON_3_POS 3
#define BUTTON_4_POS 4


//#define RED_LED_POS 8
//#define GREEN_LED_POS 9
//#define BLUE_LED_POS 10


void delay_ms( int n);
void buttonsInitialize(void);
void buttonsService(void* line);							//buttons' interrupt service procedure
void PORTB_IRQHandler(void);

#endif