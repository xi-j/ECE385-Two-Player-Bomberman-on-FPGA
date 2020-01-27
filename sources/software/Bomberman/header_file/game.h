#pragma once
#include "audio_driver.h"
#include "LEDandHEX.h"
#include "coins.h"
#include "readKey.h"
#include <time.h>

void initStage();

void initPlayer();

int game(unsigned int keycode[]);

void move(player* playerA, player* playerB, unsigned short int dir);

int canMove(unsigned short int x, unsigned short int y, player* playerB);

int onFire(unsigned short int x, unsigned short int y);

int catchFire(player* playerA);

int placeBomb(player* playerA, player* playerB);

void UpdateBomb(player* playerA, player* playerB);

int HPcheck(player* playerA, player* playerB);

int scoreCompare(player* playerA, player* playerB);

void displayHP(player* playerA, player* playerB);

//from stack overflow
static void shuffle(int *array, int N){
	int i;
	for(i=0; i<N-1;i++){
		int j = i + rand()/(RAND_MAX/(N-i)+1);
		int t = array[j];
		array[j]=array[i];
		array[i]=t;
	}
}
