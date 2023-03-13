#ifndef __SNAKE_H
#define __SNAKE_H
#include "./SYSTEM/sys/sys.h"
#include "stdlib.h"
#include "./BSP/LCD/lcd.h"

typedef struct  
{	
	u8 life;
	u8 headX;			
	u8 headY;		
	u8 snakeX[300];
	u8 snakeY[300];	
	u8 length;
	int dir;
	int tpdir;
	u8 foodX;
	u8 foodY;

}Snake; 	

void snakeInit(void);
void snakeGo(int direct);
void refresh(void);
void GameStart(void);
void generateFood(void);
void dead(void);
u8 isCover(u8 snakeX[],u8 snakeY[],u8 foodX,u8 foodY);
u8 isNearSelf(void);
void Load_Drow_Dialog(void);

#endif 
