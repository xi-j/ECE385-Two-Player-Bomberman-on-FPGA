#pragma once
#include "struct.h"
#include "spriteIndex.h"
#include "draw_driver.h"
#include "audio_driver.h"
#include <stdlib.h>

void cleanCell(unsigned short int X, unsigned short int Y);

void drawSolidWall(unsigned short int X, unsigned short int Y, cell **stage);

void drawSoftWall(unsigned short int X, unsigned short int Y, cell **stage);

void drawPlayer(unsigned short int index, player *player, unsigned short int moving);

void drawPlayerHurt(player *playerA);

void cleanPlayer(player *player1);

void drawExplosion(unsigned short int counter, unsigned short int X, unsigned short int Y);

void drawBomb(unsigned short int counter, unsigned short int X, unsigned short int Y);

void drawFiringWall(unsigned short int counter, unsigned short int X, unsigned short int Y);

void drawBombAndExplosion(unsigned short int index, unsigned short int counter, unsigned short int X, unsigned short int Y,
		cell**stage, cellXY**head,cellXY**tail);

void drawCoin(unsigned short int X, unsigned short int Y, coin *ptr);

void cleanCoin(unsigned short int X, unsigned short int Y);

void pushToCoinList(unsigned short int X, unsigned short int Y, cellXY**head,cellXY**tail);
