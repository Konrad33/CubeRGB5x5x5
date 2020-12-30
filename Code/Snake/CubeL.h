 #ifndef CubeL_H
#define CubeL_H

#define Edgesize 4
#define _LED_CNT 125


typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	
} SRGB;

static int pins[Edgesize] = {1,2,3,4};

void InitializeCube();
void sendrgb(uint8_t r, uint8_t g, uint8_t b );
void sendcolor(uint32_t c );
void clearall(void);

void send_leds(SRGB * leds);
void wait(volatile uint32_t cnt);

void cycle_color_change( SRGB rgb_leds[] );










#endif

