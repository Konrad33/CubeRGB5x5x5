#ifndef CubeL_H
#define CubeL_H

#define Edgesize 5
#define _LED_CNT 125
#define PTB1 6
#define PTB2 7
#define PTB3 8
#define PTB4 9
#define PTB5 10


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


//effects
void cycle_color_change( SRGB rgb_leds[] );
void flying_strips1(void * pasek);
void flying_strips2(void * pasek, int data[5][5][5]);






#endif
