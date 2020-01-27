#pragma once
#include "drawing.h"
#include "struct.h"
#include "LEDandHEX.h"

unsigned int getCoins(unsigned short int x, unsigned short int y,cellXY **head, cellXY **tail, cell ***stage);

void deleteCoins(unsigned short int X, unsigned short int Y, cellXY **head, cellXY **tail, cell ***stage);

void UpdateCoins(cellXY **head, cellXY **tail, cell***stage);

