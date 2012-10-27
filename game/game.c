#include "game/game.h"
#include "output/graphics/graphics.h"
#include "output/graphics/color.h"
#include "kernel/event.h"
#include "input/controller.h"

#include <stdlib.h>

typedef struct {

	Color 		c;
	Color		pcolor;
	Color		lcolor;
	uint8_t 	xpos;
	uint8_t		ypos;
	uint8_t     vx;
	uint8_t		vy;
	uint8_t     acc;
	
	uint8_t     lastx;
	uint8_t     lasty;
	
} Player;


static Player p;
static uint8_t board[8][8] = {

	{ 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 1, 0, 0, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 1, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 2, 0, 0, 1 },
};
								
static uint8_t speed = 40;
static uint8_t lives = 4;
static uint8_t stopped = 0;
static uint8_t nextLevel = 10;
static uint8_t gotoNext = 0;
uint16_t timer;

//The Setup function must be defined.
void setup()
{
	p.c     = RED;
	p.xpos  = 4;
	p.ypos  = 7;
	p.vx    = 0;
	p.vy    = 0;
	p.acc   = 1;
	p.lastx = 4;
	p.lasty = 7;
	
	DrawPlayer();
	PaintScreen();
	DrawLives();
	
	watchEvent(LEFT, &MoveLeft);
	watchEvent(RIGHT, &MoveRight);
	watchEvent(UP, &MoveForward);
	watchEvent(DOWN, &MoveBackward);
	watchEvent(A, &NextTick);
	watchEvent(B, &NextTick);
}

//The Loop function must be defined.
void loop()
{
	if( (TimerTick(500*speed) || gotoNext) && !stopped)
	{
		UpdateScreen();
		TimerReset();
		
		nextLevel--;
		if(nextLevel == 0)
		{
			LevelUp();
		}
			
		MovedByWall();
		
		gotoNext = 0;
	}
}

//has player been push back by the oncoming wall
void MovedByWall()
{
	if(board[p.ypos][p.xpos] == 1){
		
		//if pushed off the screen end the game and reset less 1 life
		if(p.ypos == 7){
			
			if(lives == 0){
				clearScreen(); 
				stopped = 1;
			}
			else
			{	
				lives--;
				DrawLives();
				reset();	
			}
		}
		else
		{
			p.lasty = p.ypos;
			++p.ypos;
			PaintScreen();
			DrawPlayer();
		}
	}
}

void LevelUp()
{
	speed = 10;
	if(speed==5)
	{
		stopped = 1;
	}
}

void MoveLeft()
{
	if(p.xpos > 0 && (board[p.ypos][p.xpos-1]%10 ==0) )
	{
		board[p.ypos][p.xpos] = 0;
		p.xpos -= 1;
		board[p.ypos][p.xpos] = 2;
		repaint();
	}	
}
		

void MoveRight()
{
	if(p.xpos < 7 && (board[p.ypos][p.xpos+1]%10 ==0) )
	{
		board[p.ypos][p.xpos] = 0;
		p.xpos += 1;
		board[p.ypos][p.xpos] = 2;
		repaint();
	}
}

void MoveForward()
{
	if(p.ypos > 0 && (board[p.ypos-1][p.xpos]%10 ==0) )
	{
		board[p.ypos][p.xpos] = 0;
		p.ypos -= 1;
		board[p.ypos][p.xpos] = 2;
		repaint();
	}	
}

void MoveBackward()
{
	if(p.ypos < 8 && (board[p.ypos+1][p.xpos]%10 ==0) )
	{
		board[p.ypos][p.xpos] = 0;
		p.ypos += 1;
		board[p.ypos][p.xpos] = 2;
		repaint();
	}	
}

void DrawPlayer()
{
	//SetPxl(p.lastx, p.lasty, BLACK);
	//SetPxl(p.xpos, p.ypos, p.c);
}

void PaintScreen()
{
	uint8_t i,j;
	
	for(j=0; j<8; j++)
	{
		for(i=0; i<8; i++)
		{
			if(board[j][i] == 0)
			{
				SetPxl(i, j, BLACK);
			}
			else if(board[j][i] == 1)
			{
				SetPxl(i, j, WHITE);
			}
			else if(board[j][i] == 2)
			{
				SetPxl(i, j, RED);
			}
			else if(board[j][i] == 20)
			{
				SetPxl(i, j, GREEN);
			}
		}
	}
	
}

void repaint()
{
	PaintScreen();
	DrawPlayer();
}

void UpdateScreen()
{

	uint8_t i;
	for(i = 7; i > 0; --i)
	{
		board[i][0] = board[i-1][0];
		board[i][1] = board[i-1][1];
		board[i][2] = board[i-1][2];
		board[i][3] = board[i-1][3];
		board[i][4] = board[i-1][4];
		board[i][5] = board[i-1][5];
		board[i][6] = board[i-1][6];
		board[i][7] = board[i-1][7];
	}
	
	if(nextLevel == 1) 
	{
		board[0][0] = 20;
		board[0][1] = 20;
		board[0][2] = 20;
		board[0][3] = 20;
		board[0][4] = 20;
		board[0][5] = 20;
		board[0][6] = 20;
		board[0][7] = 20;
		
		nextLevel = 10;
	}
	else
	{
		uint8_t i;
		
		srand(timer);
		
		for(i=0; i < 8; i++)
		{
		
			uint8_t left = board[1][i-1];
			uint8_t center = board[1][i];
			uint8_t right = board[1][i+1];
			
			if(left == 1 && right == 1 && center == 0)
			{
				board[0][i] = 0;
			}
			else if(left == 0 && right == 0 && center == 1)
			{
				board[0][i] = rand()%2; //may ned to be random
			}
			else if( ((left == 1 && right == 0) || (left == 0 && right == 1)) && (center == 0 || center == 1) )
			{
				if(board[0][i-1] == 0)
				{
					board[0][i] = rand()%2; //needs to randomly 0 or 1
				}
				else 
				{
					board[0][i] = 0;
				}
			}
			else if(left == 0 && right == 0 && center == 0)
			{
				board[0][i] = rand()%2; //may need to become random but will have to test first
			}
			else if(left == 1 && right == 1 && center == 1)
			{
				board[0][i] = rand()%2; //randomly be 0 or 1
			}
			else
			{
				board[0][i] = rand()%2;
			}
			
		}

	}
	
	
	if(board[p.ypos][p.xpos] != 1){
	
		if(p.ypos < 7) {
			board[p.ypos+1][p.xpos] = 0;
		}
		board[p.ypos][p.xpos] = 2;
	
	}
	 
	repaint();
}

void reset()
{	
	p.xpos = 4;
	p.ypos = 7;
	
	repaint();
}

void DrawLives()
{
	SetAuxAll(0);
	
	uint8_t i;
	for(i = 0; i < lives; i++)
	{
		SetAuxLedOn(i);
	}
}

void NextTick()
{
	gotoNext = 1;
}
