/*
 * audio_driver.c
 *
 *  Created on: 2019Äê11ÔÂ20ÈÕ
 *      Author: Jerry-H
 */
#include "./header_file/audio_driver.h"


volatile unsigned int* Back_Vol_ptr = (unsigned int*)0x08000080;
volatile unsigned int* Bomb_Vol_ptr = (unsigned int*)0x080000a0;
volatile unsigned int* Bomb_Act_ptr = (unsigned int*)0x08000090;
volatile unsigned int* Audio_Sel_ptr = (unsigned int*)0x080000c0;

void changeBackVolume(unsigned int vol){

	if (vol >= 8)
		printf("need a integer between 0-8");
	else
		*Back_Vol_ptr = vol;

}

void changeBombVolume(unsigned int vol){

	if (vol >= 8)
		printf("need a integer between 0-8");
	else
		*Bomb_Vol_ptr = vol;

}


void Audio_init(){

	changeBackVolume(0);
	changeBombVolume(3);
	*Bomb_Act_ptr = 0;
	Audio_Select('o');

}

void Bomb(){
	*Bomb_Act_ptr = 1;
	*Bomb_Act_ptr = 0;
}

void Audio_Select(char i){

	switch(i){

		case 'o': *Audio_Sel_ptr = 0; *Audio_Sel_ptr = 5; break;			//OP //A
		case '1': *Audio_Sel_ptr = 1; *Audio_Sel_ptr = 7;break;			//Game0	//A
		case '_': *Audio_Sel_ptr = 2; break;			//Game0 to Game1 Transition
		case '2': *Audio_Sel_ptr = 2; break;			//Game1
		case 'w': *Audio_Sel_ptr = 4; *Audio_Sel_ptr = 5; break;			//Winner Music
	}



}
