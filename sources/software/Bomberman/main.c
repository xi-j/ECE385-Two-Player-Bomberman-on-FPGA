/*
 * main.c
 *
 *  Created on: 11-07/2019
 *      Author: Jerry Wang
 */

#include "./header_file/game.h"
#include "./header_file/op.h"
#include "./header_file/ed.h"
#include "./header_file/draw_driver.h"
#include "./header_file/USB_Keyboard_Driver.h"
#include "./header_file/audio_driver.h"
#include "./header_file/LEDandHEX.h"
#include "./header_file/INIT.h"
#include "./header_file/transition.h"

unsigned int keycode[6];
int L1 = 1000;
int L2 = 2;
int i = 0;
unsigned int counter = 0;




int main(){

	INIT();

	START:
    //opening
    initOP();
    while(1){
    	FetchKey(keycode);
    	if(op(keycode,counter)){break;}
    	counter++;
    }
    //gaming

    begin_anim();
	initStage();
	int ending = 0;
    initPlayer();
	while (1){
			FetchKey(keycode);
			ending = game(keycode);
			if(ending){break;}
	}

	//ending
	initED(ending);
    while(1){
    	FetchKey(keycode);
    	if(ed(keycode,counter)){goto START;}
    	counter++;
    }

    return 0;
}


