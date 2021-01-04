////////////////////////////////////////////////////////////
//////***non-optymised library version***///////////////////
////////////////////////////////////////////////////////////

#include "MKL05Z4.h"                    //Device header
#include "CubeL.h"												//Declaration



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
static void set1(int x)
{
	PTB->PDOR |= (1 << pins[x]);
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");              							
	
	
	
	PTB->PDOR&= ~(1 << pins[x]);
}

static void set0(int x)
{
	PTB->PDOR |= (1 << pins[x]);
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
	PTB->PDOR&= ~(1 << pins[x]);
}
//////////////////////////////////////////////////////////////////////////////////////////


void sendrgb(uint8_t r, uint8_t g, uint8_t b, int x )
{
	
	if(r & 128) set1(x); else set0(x);
	if(r & 64) set1(x); else set0(x);
	if(r & 32) set1(x); else set0(x);
	if(r & 16) set1(x); else set0(x);
	if(r & 8) set1(x); else set0(x);
	if(r & 4) set1(x); else set0(x);
	if(r & 2) set1(x); else set0(x);
	if(r & 1) set1(x); else set0(x);
	
	if(g & 128) set1(x); else set0(x);
	if(g & 64) set1(x); else set0(x);
	if(g & 32) set1(x); else set0(x);
	if(g & 16) set1(x); else set0(x);
	if(g & 8) set1(x); else set0(x);
	if(g & 4) set1(x); else set0(x);
	if(g & 2) set1(x); else set0(x);
	if(g & 1) set1(x); else set0(x);
	
	if(b & 128) set1(x); else set0(x);
	if(b & 64) set1(x); else set0(x);
	if(b & 32) set1(x); else set0(x);
	if(b & 16) set1(x); else set0(x);
	if(b & 8) set1(x); else set0(x);
	if(b & 4) set1(x); else set0(x);
	if(b & 2) set1(x); else set0(x);
	if(b & 1) set1(x); else set0(x);
}

//here we send color in hex 
//for example: sendcolor(0xFF0000, 2); to light up red color on pin 2 leds
void sendcolor(uint32_t c, int x )
{
	uint8_t r = c >> 16, g = c >> 8, b = c;
	
	if(r & 128) set1(x); else set0(x);
	if(r & 64) set1(x); else set0(x);
	if(r & 32) set1(x); else set0(x);
	if(r & 16) set1(x); else set0(x);
	if(r & 8) set1(x); else set0(x);
	if(r & 4) set1(x); else set0(x);
	if(r & 2) set1(x); else set0(x);
	if(r & 1) set1(x); else set0(x);
	
	if(g & 128) set1(x); else set0(x);
	if(g & 64) set1(x); else set0(x);
	if(g & 32) set1(x); else set0(x);
	if(g & 16) set1(x); else set0(x);
	if(g & 8) set1(x); else set0(x);
	if(g & 4) set1(x); else set0(x);
	if(g & 2) set1(x); else set0(x);
	if(g & 1) set1(x); else set0(x);
	
	if(b & 128) set1(x); else set0(x);
	if(b & 64) set1(x); else set0(x);
	if(b & 32) set1(x); else set0(x);
	if(b & 16) set1(x); else set0(x);
	if(b & 8) set1(x); else set0(x);
	if(b & 4) set1(x); else set0(x);
	if(b & 2) set1(x); else set0(x);
	if(b & 1) set1(x); else set0(x);
}

//// send bit 0 to all leds
void clearwall(int x)
{
	
	for(int i = 0; i <24*25 ; i++) set0(x);
	
}
void clear_all(void)
{
for(int j=0; j<5; j++){
		for(int i = 0; i <24*25 ; i++) set0(j);
	}

}

//// send bit 1 to all leds
void lightupwall(int x)
{
	
	for(int i = 0; i < 24*25; i++)
	{
			set1(x);
	}
	
}

// here we set color and brightness of one led in our memory 
void setPixel( void* line, int ledofchoice, uint32_t color )
{
	if(ledofchoice<0) return;
	if(ledofchoice >= _LED_CNT) return;
	ledofchoice*=3;
	*((uint8_t*)line + ledofchoice) = color >> 16;
	*((uint8_t*)line + ledofchoice+1) = color >> 8;
	*((uint8_t*)line + ledofchoice+2) = color ;
}

void clearAllPixels(void * line )
{
	for(int i = 0; i < 125; i++)
	{
		setPixel(line, i, 0x00);
	}
}


void create_line(void * line, int len_start, uint16_t len, uint32_t color)
{
	for( int i = len_start; i < (int)(len_start + len); i++)
	{
		setPixel(line, len_start,  color );
	}
}



//here we send to our cube what is written in our memory
void send_leds(SRGB * leds, int x)
{
	uint8_t i;
	uint8_t *wsk= (uint8_t*)leds; 
	if(x == 0)
	{
		for(i = 0; i < 25; i++ )
		{
			sendrgb( *wsk, *(wsk +1), *(wsk +2), 0);
			wsk+=3;
		}
	}
	if(x == 1)
	{
		for(i = 25; i < 50; i++ )
		{
			sendrgb( *wsk, *(wsk +1), *(wsk +2), 1);
			wsk+=3;
		}
	}
	if(x == 2)
	{
		for(i = 50; i < 75; i++ )
		{
			sendrgb( *wsk, *(wsk +1), *(wsk +2), 2);
			wsk+=3;
		}
	}
	if(x == 3)
	{
		for(i = 75; i < 100; i++ )
		{
			sendrgb( *wsk, *(wsk +1), *(wsk +2), 3);
			wsk+=3;
		}
	}
	if(x == 4)
	{
		for(i = 100; i < _LED_CNT; i++ )
		{
			sendrgb( *wsk, *(wsk +1), *(wsk +2), 4);
			wsk+=3;
		}
	}
	
}



/////////////////////////////////////////////////////////////////////////
// in this function i change between red, green and blue color in the same pattern periodically

void cycle_color_change(	SRGB rgb_leds[] )
{
	uint8_t i, k=0;	
	//uint8_t *wsk = (uint8_t*)&rgb_leds;

	int howmanyleds = 25;                          //here i sets how many led i want to use
	memset(&rgb_leds,0, 25*3 );										//we must clear all before we begin because when we don't use all leds, leds which are not used can be lgihtened up in diffrent colours
	while(1)
	{
		for(int j=0; j<5; j++)
		{
			uint8_t *wsk = (uint8_t*)&rgb_leds;
			memset(&rgb_leds,0, howmanyleds*3 );                               //here we must reset what we written to RAM because we want our colors to keep changing
			for(i=0; i < howmanyleds*3; i++)  
			{
				if((i % 3) == k )*wsk = 255;                              //here we change our colours  
				
				*wsk++;
			}	

			send_leds(&rgb_leds, j);
			k++;
			if(k>2) k=0;
		}
		wait(12000000);
	}

}

////////////////////////////////////////////////////////////////////////////

//wait function where argument is clock tick
void wait(volatile uint32_t cnt) {
    while(cnt--)
        __asm("nop");
}

