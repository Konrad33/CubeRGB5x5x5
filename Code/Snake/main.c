


#include "MKL05Z4.h"                    	/* Device header */
#include "CubeL.h"												/* Cube 5x5x5 */
#include "buttons.h"											/* Buttons of external keyboard */
#include <stdlib.h>                       /* Pseudorandom number generator */


int data[5][5][5];

int snake_size = 2;
int direction = 31;
int defeat_or_win = 0;
int win = 0;
int lose = 0;
int old_snake_size = 2;

enum move{MOVE_UP,MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

SRGB rgb_leds [ _LED_CNT ];
/// pin 1 - 0.....24  - first wall
/// pin 2 - 25.....49 - second wall
/// pin 3 - 50.....74 - third wall
/// pin 4 - 75.....99  - fourth wall
/// pin 5 - 100.....124 - fifth wall

uint8_t * pasek = (uint8_t*) &rgb_leds;


typedef struct Coordinates{
	int x;  //PIN
	int y;  //height
	int z;  //length
} XYZ;

XYZ snake[125];
XYZ food;
XYZ tmp;



//here we create reference to data from SRGB struct for our 3D matrix data[5][5][5]
void fill_Data(void)
{
	for(int i =0; i < 5; i++)
	{
		for(int j =0; j < 5; j++)
			{
				if((j == 1) || (j == 3)){
					for(int k =0; k < 5; k++)
					{
						data[i][j][k] = 5-k-1 + j*5 + i*25;
					}		
				}
				else{
				for(int k =0; k < 5; k++)
					{
						data[i][j][k] = k + j*5 + i*25;
					}
				}
			}
	}
}

//here we set our starting conditions
void snake_start()
{
	snake[0].x = 0;
	snake[0].y = 1;
	snake[0].z = 2;
	
	snake[1].x = 0;
	snake[1].y = 1;
	snake[1].z = 1;
	
	food.x = 0;
	food.y = 1;
	food.z = 1;
}

//here we set where food should be
void where_food()
{
	//int tmp_food = 25 - snake_size ;											//when completed 125
	food.x =0; //rand() % 5;
	food.y = rand() % 5;
	food.z = rand() % 5;
	
	for(int i = 0; i < snake_size; i++){
		if(snake[i].x == food.x){
			food.x =0; //rand() % 5;
			//where_food();
		}
		if(snake[i].y == food.y){
			food.y = rand() % 5;
			//where_food();
		}
		if(snake[i].z == food.z){
			food.z = rand() % 5;
			//where_food();
		}
	}
}

//here we check if he ate food and if yes we make him bigger
void check_food()
{
	if((snake[0].x == food.x) && (snake[0].y == food.y) && (snake[0].z == food.z)){
		old_snake_size = snake_size;
		snake_size++;
		snake[old_snake_size].x = tmp.x;
		snake[old_snake_size].y = tmp.y;
		snake[old_snake_size].z = tmp.z;
		
		where_food();
	}
}

//here is how our snake should move
void snake_move()
{
	
	if(direction == 11)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].x++;
		
		if(snake[0].x == Edgesize ) snake[0].x = 0;	
	}
	
	if(direction == 12)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].x--;
		
		if(snake[0].x == Edgesize ) snake[0].x = 0;
	}
	
	if(direction == 21)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].y++;
		
		if(snake[0].y == Edgesize ) snake[0].y = 0;
	}
	
	if(direction == 22)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].y--;
		
		if(snake[0].y == Edgesize ) snake[0].y = 0;
	}
	
	if(direction == 31)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].z++;
		
		if(snake[0].z == Edgesize ) snake[0].z = 0;
	}
	
	if(direction == 32)
	{
		for(int i=snake_size-1; i>0; i--)
		{
			tmp = snake[i];
			snake[i] = snake[i-1];
		}
		snake[0].z--;
		
		if(snake[0].z == Edgesize ) snake[0].z = 0;
	}
	
	
}

//here we check if game ended
void check_when_lose_or_win()
{
	for(int i=1; i < snake_size; i++)
	{
		if((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y) && (snake[0].z == snake[i].z) ) 
		{
			defeat_or_win++;
			lose++;
		}
	}
	if (snake_size == 120) win++;		
}

//here we show word "lose" when somebody lose the game
void lose_end_game()
{
	if(lose == 1)
	{
		//1 we show letter here
		setPixel(pasek,data[0][4][1], 0xFF0000);
		setPixel(pasek,data[0][3][1], 0xFF0000);
		setPixel(pasek,data[0][2][1], 0xFF0000);
		setPixel(pasek,data[0][1][1], 0xFF0000);
		setPixel(pasek,data[0][0][1], 0xFF0000);
		setPixel(pasek,data[0][0][2], 0xFF0000);
		setPixel(pasek,data[0][0][3], 0xFF0000);
		setPixel(pasek,data[0][0][4], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(4000);
		//~1 and we clear letter here
		setPixel(pasek,data[0][4][1], 0x0000);
		setPixel(pasek,data[0][3][1], 0x0000);
		setPixel(pasek,data[0][2][1], 0x0000);
		setPixel(pasek,data[0][1][1], 0x0000);
		setPixel(pasek,data[0][0][1], 0x0000);
		setPixel(pasek,data[0][0][2], 0x0000);
		setPixel(pasek,data[0][0][3], 0x0000);
		setPixel(pasek,data[0][0][4], 0x0000);
		send_leds(pasek, 0);
		delay_ms(500);
		//2
		setPixel(pasek,data[0][4][1], 0xFF0000);
		setPixel(pasek,data[0][3][1], 0xFF0000);
		setPixel(pasek,data[0][2][1], 0xFF0000);
		setPixel(pasek,data[0][1][1], 0xFF0000);
		setPixel(pasek,data[0][0][1], 0xFF0000);
		setPixel(pasek,data[0][4][3], 0xFF0000);
		setPixel(pasek,data[0][3][3], 0xFF0000);
		setPixel(pasek,data[0][2][3], 0xFF0000);
		setPixel(pasek,data[0][1][3], 0xFF0000);
		setPixel(pasek,data[0][0][3], 0xFF0000);
		setPixel(pasek,data[0][0][2], 0xFF0000);
		setPixel(pasek,data[0][4][2], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(4000);
		//~2
		setPixel(pasek,data[0][4][1], 0x0000);
		setPixel(pasek,data[0][3][1], 0x0000);
		setPixel(pasek,data[0][2][1], 0x0000);
		setPixel(pasek,data[0][1][1], 0x0000);
		setPixel(pasek,data[0][0][1], 0x0000);
		setPixel(pasek,data[0][4][3], 0x0000);
		setPixel(pasek,data[0][3][3], 0x0000);
		setPixel(pasek,data[0][2][3], 0x0000);
		setPixel(pasek,data[0][1][3], 0x0000);
		setPixel(pasek,data[0][0][3], 0x0000);
		setPixel(pasek,data[0][0][2], 0x0000);
		setPixel(pasek,data[0][4][2], 0x0000);
		send_leds(pasek, 0);
		delay_ms(500);
		//3
		setPixel(pasek,data[0][4][1], 0xFF0000);
		setPixel(pasek,data[0][4][2], 0xFF0000);
		setPixel(pasek,data[0][4][3], 0xFF0000);
		setPixel(pasek,data[0][4][3], 0xFF0000);
		setPixel(pasek,data[0][3][1], 0xFF0000);
		setPixel(pasek,data[0][2][1], 0xFF0000);
		setPixel(pasek,data[0][2][2], 0xFF0000);
		setPixel(pasek,data[0][2][3], 0xFF0000);
		setPixel(pasek,data[0][1][3], 0xFF0000);
		setPixel(pasek,data[0][0][3], 0xFF0000);
		setPixel(pasek,data[0][0][2], 0xFF0000);
		setPixel(pasek,data[0][0][1], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(4000);
		//~3
		setPixel(pasek,data[0][4][1], 0x0000);
		setPixel(pasek,data[0][4][2], 0x0000);
		setPixel(pasek,data[0][4][3], 0x0000);
		setPixel(pasek,data[0][4][3], 0x0000);
		setPixel(pasek,data[0][3][1], 0x0000);
		setPixel(pasek,data[0][2][1], 0x0000);
		setPixel(pasek,data[0][2][2], 0x0000);
		setPixel(pasek,data[0][2][3], 0x0000);
		setPixel(pasek,data[0][1][3], 0x0000);
		setPixel(pasek,data[0][0][3], 0x0000);
		setPixel(pasek,data[0][0][2], 0x0000);
		setPixel(pasek,data[0][0][1], 0x0000);
		send_leds(pasek, 0);
		delay_ms(500);
		//4
		setPixel(pasek,data[0][4][1], 0xFF0000);
		setPixel(pasek,data[0][4][2], 0xFF0000);
		setPixel(pasek,data[0][4][3], 0xFF0000);
		setPixel(pasek,data[0][4][3], 0xFF0000);
		setPixel(pasek,data[0][3][1], 0xFF0000);
		setPixel(pasek,data[0][2][1], 0xFF0000);
		setPixel(pasek,data[0][2][2], 0xFF0000);
		setPixel(pasek,data[0][2][3], 0xFF0000);
		setPixel(pasek,data[0][1][1], 0xFF0000);
		setPixel(pasek,data[0][0][3], 0xFF0000);
		setPixel(pasek,data[0][0][2], 0xFF0000);
		setPixel(pasek,data[0][0][1], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(2000);
	}
}

//here we show word "win" when somebody wins the game
void win_end_game()
{
	if(win == 1)
	{
		//1
		setPixel(pasek,data[0][4][0], 0xFF0000);
		setPixel(pasek,data[0][3][0], 0xFF0000);
		setPixel(pasek,data[0][2][0], 0xFF0000);
		setPixel(pasek,data[0][1][0], 0xFF0000);
		setPixel(pasek,data[0][0][0], 0xFF0000);
		setPixel(pasek,data[0][1][1], 0xFF0000);
		setPixel(pasek,data[0][2][2], 0xFF0000);
		setPixel(pasek,data[0][1][3], 0xFF0000);
		setPixel(pasek,data[0][0][4], 0xFF0000);
		setPixel(pasek,data[0][1][4], 0xFF0000);
		setPixel(pasek,data[0][2][4], 0xFF0000);
		setPixel(pasek,data[0][3][4], 0xFF0000);
		setPixel(pasek,data[0][4][4], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(4000);
		//~1
		setPixel(pasek,data[0][4][0], 0x0000);
		setPixel(pasek,data[0][3][0], 0x0000);
		setPixel(pasek,data[0][2][0], 0x0000);
		setPixel(pasek,data[0][1][0], 0x0000);
		setPixel(pasek,data[0][0][0], 0x0000);
		setPixel(pasek,data[0][1][1], 0x0000);
		setPixel(pasek,data[0][2][2], 0x0000);
		setPixel(pasek,data[0][1][3], 0x0000);
		setPixel(pasek,data[0][0][4], 0x0000);
		setPixel(pasek,data[0][1][4], 0x0000);
		setPixel(pasek,data[0][2][4], 0x0000);
		setPixel(pasek,data[0][3][4], 0x0000);
		setPixel(pasek,data[0][4][4], 0x0000);
		send_leds(pasek, 0);
		delay_ms(500);
		//2
		setPixel(pasek,data[0][4][2], 0xFF0000);
		setPixel(pasek,data[0][3][2], 0xFF0000);
		setPixel(pasek,data[0][2][2], 0xFF0000);
		setPixel(pasek,data[0][1][2], 0xFF0000);
		setPixel(pasek,data[0][0][2], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(4000);
		//~2
		setPixel(pasek,data[0][4][2], 0x0000);
		setPixel(pasek,data[0][3][2], 0x0000);
		setPixel(pasek,data[0][2][2], 0x0000);
		setPixel(pasek,data[0][1][2], 0x0000);
		setPixel(pasek,data[0][0][2], 0x0000);
		send_leds(pasek, 0);
		delay_ms(500);
		//3
		setPixel(pasek,data[0][4][0], 0xFF0000);
		setPixel(pasek,data[0][3][0], 0xFF0000);
		setPixel(pasek,data[0][2][0], 0xFF0000);
		setPixel(pasek,data[0][1][0], 0xFF0000);
		setPixel(pasek,data[0][0][0], 0xFF0000);
		setPixel(pasek,data[0][3][1], 0xFF0000);
		setPixel(pasek,data[0][2][2], 0xFF0000);
		setPixel(pasek,data[0][1][3], 0xFF0000);
		setPixel(pasek,data[0][0][4], 0xFF0000);
		setPixel(pasek,data[0][1][4], 0xFF0000);
		setPixel(pasek,data[0][2][4], 0xFF0000);
		setPixel(pasek,data[0][3][4], 0xFF0000);
		setPixel(pasek,data[0][4][4], 0xFF0000);
		send_leds(pasek, 0);
		delay_ms(2000);
		
	}
}

//here we show snake and food on our cube
void display()
{	
	//clear_all();
	clearAllPixels(pasek );
	for(int i=1; i <snake_size; i++)
		{
			setPixel(pasek,data[snake[i].x][snake[i].y][snake[i].z], 0x001f00);
		}
		//if(old_snake_size == snake_size)setPixel(pasek,data[tmp.x][tmp.y][tmp.z], 0x00);
		//else old_snake_size = snake_size;
		setPixel(pasek,data[snake[0].x][snake[0].y][snake[0].z], 0x001f1f);
		setPixel(pasek,data[food.x][food.y][food.z], 0x1f1f00);
	for(int j = 0; j < 5; j++)
		{
				send_leds(pasek, j);
		}
}



int main(void) {

InitializeCube();
buttonsInitialize();
fill_Data();
	
clearwall(0);	
wait(5000);

win =1 ;


snake_start();

	while(!defeat_or_win)
	{	
		snake_move();
		check_food();
		display();
		check_when_lose_or_win();
		delay_ms(1000);
	}

//lose_end_game();
//win_end_game();
}

