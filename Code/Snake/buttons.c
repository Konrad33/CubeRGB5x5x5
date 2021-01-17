#include "MKL05Z4.h"                    //Device header
#include "buttons.h"												//Declarations
#include "CubeL.h"	


void delay_ms( int n) {
volatile int i;
volatile int j;
for( i = 0 ; i < n; i++)
for(j = 0; j < 3500; j++) {}
} 



void buttonsInitialize(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /* Enable clock for GPIO B */
	PORTB->PCR[BUTTON_1_POS] |= PORT_PCR_MUX(1); /* Set Pin 1 MUX as GPIO */
	PORTB->PCR[BUTTON_2_POS] |= PORT_PCR_MUX(1); 
	PORTB->PCR[BUTTON_3_POS] |= PORT_PCR_MUX(1);
	PORTB->PCR[BUTTON_4_POS] |= PORT_PCR_MUX(1);	
		
	PORTB->PCR[BUTTON_1_POS] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;  // Enable pull-up resitor on Pin 1	
	PORTB->PCR[BUTTON_2_POS] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	 
	PORTB->PCR[BUTTON_3_POS] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[BUTTON_4_POS] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	
	//PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(1); // Set Pin 8 MUX as GPIO /
  //PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(1); // Set Pin 9 MUX as GPIO /
  //PORTB->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(1); // Set Pin 10 MUX as GPIO */
	//PTB->PDDR |= (1<<RED_LED_POS) | (1<<GREEN_LED_POS) | (1<<BLUE_LED_POS); // Set RED LED pin as output /
  //PTB->PSOR |= (1<<RED_LED_POS) | (1<<GREEN_LED_POS) | (1<<BLUE_LED_POS); // Turn off RED LED */
}


