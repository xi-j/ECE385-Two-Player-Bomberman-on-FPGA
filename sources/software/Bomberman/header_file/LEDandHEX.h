#pragma once
#include "struct.h"


#define LEDs	(volatile int*) 0x080000b0
#define player1Score1 (volatile int*) 0x08000160
#define player1Score0 (volatile int*) 0x08000170
#define player2Score1 (volatile int*) 0x08000180
#define player2Score0 (volatile int*) 0x08000190
#define timeScreen2   (volatile int*) 0x08000140
#define timeScreen1   (volatile int*) 0x08000150
#define timeScreen0   (volatile int*) 0x08000130

void displayScore(player* playerA, player* playerB);

void displayTime(unsigned int sec);
