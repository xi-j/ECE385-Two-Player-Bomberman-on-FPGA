/*
 * INIT.c
 *
 *  Created on: 2019Äê12ÔÂ7ÈÕ
 *      Author: Jerry-H
 */

#include "./header_file/draw_driver.h"
#include "./header_file/USB_Keyboard_Driver.h"
#include "./header_file/audio_driver.h"

volatile unsigned int * Boot_Up = (unsigned int *) 0x080000d0;


void INIT(){
///////////////////////////////////////////////////////////////////////Init Stage
	draw_driver_init();

	//Draw Black Background
	for (int i = 0; i < 4; i++ ){
		//Loop  Row
		for (int z = 0; z < 3; z++){
			draw_driver(414,7,414+159,7+159,i*160,160*z,4);
			delay(1);
		}
	}

	//Wait until the Boot_Up bottom being pressed
	while (!(*Boot_Up)){}



	draw_driver(13,16,13+217,16+21,10,10,4);
	Audio_init();

	for (int i = 0; i < 12; i++){
		draw_driver(12,260,28,276,i*10,400,4);
		delay(30);
	}

	draw_driver(13,58,13+222,24+58,9,50,4);
	delay(500);

	for (int i = 12; i < 20; i++){
		draw_driver(12,260,28,276,i*10,400,4);
		delay(30);
	}

	draw_driver(11,109,11+238,107+21,12,90,4);
	Keyboard_INIT();

//////////////////////////////////////////////////////////////////////////////////
}


