/*----------------------------------------------------------------------------
 *      Name:    CubeL.c
 *
 *      Purpose: Microprocessors Laboratory Project      
 *
 *      Author: Krzysztof Reczek
 *---------------------------------------------------------------------------*/

#include "MKL05Z4.h"                    //Device header
#include "CubeL.h"												//Declarations

static uint32_t data[Edgesize^2 * 24]; // data for display on LEDs


void InitializeCube()
{
	//Initialize pins to send data on leds
	SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK;      /* Enable Clock to Port B */ 
	for(volatile int i = 0; i < Edgesize; i++ )
	{
			PORTB->PCR[pins[i]] = PORT_PCR_MUX(1);        /*Set pin 1,2,3,4,5 as GPIO */	
			PTB->PDDR |= (1<<pins[i]);	
	}

}

//////////////////////////////////////////////////////////////////////////////////////////
//***********here i have functions which send bits 0 and 1 to LEDS*************//
static void set1(void)
{
	PTB->PDOR |= (1 << 1);
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");
	PTB->PDOR&= ~(1 << 1);
	
	PTB->PDOR |= (1 << 2);
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");
	PTB->PDOR&= ~(1 << 2);		
}

static void set0(void)
{
	PTB->PDOR |= (1 << 1);
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	__asm volatile ("nop");
	
	
	PTB->PDOR&= ~(1 << 1);

		PTB->PDOR |= (1 << 2);
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	__asm volatile ("nop");
	
	PTB->PDOR&= ~(1 << 2);
}
//////////////////////////////////////////////////////////////////////////////////////////


void sendrgb(uint8_t r, uint8_t g, uint8_t b )
{
	
	if(r & 128) set1(); else set0();
	if(r & 64) set1(); else set0();
	if(r & 32) set1(); else set0();
	if(r & 16) set1(); else set0();
	if(r & 8) set1(); else set0();
	if(r & 4) set1(); else set0();
	if(r & 2) set1(); else set0();
	if(r & 1) set1(); else set0();
	
	if(g & 128) set1(); else set0();
	if(g & 64) set1(); else set0();
	if(g & 32) set1(); else set0();
	if(g & 16) set1(); else set0();
	if(g & 8) set1(); else set0();
	if(g & 4) set1(); else set0();
	if(g & 2) set1(); else set0();
	if(g & 1) set1(); else set0();
	
	if(b & 128) set1(); else set0();
	if(b & 64) set1(); else set0();
	if(b & 32) set1(); else set0();
	if(b & 16) set1(); else set0();
	if(b & 8) set1(); else set0();
	if(b & 4) set1(); else set0();
	if(b & 2) set1(); else set0();
	if(b & 1) set1(); else set0();
}

void sendcolor(uint32_t c )
{
	uint8_t r = c >> 16, g = c >> 8, b = c;
	
	if(r & 128) set1(); else set0();
	if(r & 64) set1(); else set0();
	if(r & 32) set1(); else set0();
	if(r & 16) set1(); else set0();
	if(r & 8) set1(); else set0();
	if(r & 4) set1(); else set0();
	if(r & 2) set1(); else set0();
	if(r & 1) set1(); else set0();
	
	if(g & 128) set1(); else set0();
	if(g & 64) set1(); else set0();
	if(g & 32) set1(); else set0();
	if(g & 16) set1(); else set0();
	if(g & 8) set1(); else set0();
	if(g & 4) set1(); else set0();
	if(g & 2) set1(); else set0();
	if(g & 1) set1(); else set0();
	
	if(b & 128) set1(); else set0();
	if(b & 64) set1(); else set0();
	if(b & 32) set1(); else set0();
	if(b & 16) set1(); else set0();
	if(b & 8) set1(); else set0();
	if(b & 4) set1(); else set0();
	if(b & 2) set1(); else set0();
	if(b & 1) set1(); else set0();
}

void clearall()
{
	for(int i = 0; i <32*16 ; i++) set0();
}

void send_leds(SRGB * leds)
{
	uint8_t i;
	uint8_t *wsk= (uint8_t*)leds; 
	
	for(i = 0; i < _LED_CNT; i++ )
	{
		sendrgb( *wsk, *(wsk +1), *(wsk +2));
		wsk+=3;
	}
	wait(10000);
}

/////////////////////////////////////////////////////////////////////////
								// in this function i change between red, green and blue color in the same pattern periodically
void cycle_color_change(	SRGB rgb_leds[] )
{
	uint8_t i, k=0;	
	uint8_t *wsk = (uint8_t*)&rgb_leds;

	int howmanyleds = 8;                          //here i sets how many led i want to use
	memset(&rgb_leds,0, 16*3 );										//we must clear all before we begin because we can find some strange things written in memory
	while(1)
	{
		uint8_t *wsk = (uint8_t*)&rgb_leds;
		memset(&rgb_leds,0, howmanyleds*3 );                               //here we must reset what we written to RAM because we want our colors to keep changing
		for(i=0; i < howmanyleds*3; i++)  
		{
			if((i % 3) == k )*wsk = 128; //napelniam tylko 1 kolorem
			*wsk++;
		}	

		send_leds(&rgb_leds);
		k++;
		if(k>2) k=0;
		wait(12000000);
	}

}


void wait(volatile uint32_t cnt) {
    while(cnt--)
        __asm("nop");
}

