#ifndef CubeL_H
#define CubeL_H

#define Edgesize 5
#define _LED_CNT 125
#define PTB1 1
#define PTB2 2
#define PTB3 3
#define PTB4 4
#define PTB5 5


typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	
} SRGB;

//extern SRGB rgb_leds[_LED_CNT];

static int pins[Edgesize] = {PTB1,PTB2,PTB3,PTB4,PTB5};


void InitializeCube();
void sendrgb(uint8_t r, uint8_t g, uint8_t b, int x );
void sendcolor(uint32_t c, int x );
void clearwall(int x);
void lightupwall(int x);
void clear_all(void);

void clearAllPixels(void * line );
void setPixel( void * line, int ledofchoice, uint32_t color );
void create_line(void * line, int len_start, uint16_t len, uint32_t color);
void send_leds(SRGB * leds, int x);

void wait(volatile uint32_t cnt);

void cycle_color_change( SRGB rgb_leds[] );








#endif
