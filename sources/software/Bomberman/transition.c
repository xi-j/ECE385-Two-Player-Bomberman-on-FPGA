/*
 * transition.c
 *
 *  Created on: 2019Äê12ÔÂ7ÈÕ
 *      Author: Jerry-H
 */
#include "./header_file/draw_driver.h"
#include "./header_file/spriteIndex.h"
#include "./header_file/drawing.h"
#include "./header_file/audio_driver.h"

void begin_anim(){



	changeBackVolume(0);



	//Draw Background
	//Loop Column
	//Draw Black Background
	for (int i = 0; i < 4; i++ ){
		//Loop  Row
		for (int z = 0; z < 3; z++){
			draw_driver(414,300,414+159,300+159,i*160,160*z,2);
			delay(1);
		}
	}

	//Draw Bomb Box
	for (int r1 = 0; r1 < 210; r1 ++){
		draw_driver(310,12,311,13,r1+215,382,1);
	}

	for (int rn = 0 ; rn < 40; rn ++ ){
		draw_driver(310,12,311,13,215,382+rn,1);
	}

	for (int r2 = 0; r2 < 210; r2 ++){
		draw_driver(310,12,311,13,r2+215,382+39,1);
	}

	for (int rn2 = 0 ; rn2 < 40; rn2 ++ ){
		draw_driver(310,12,311,13,215+209,382+rn2,1);
	}



	//Draw Character
	drawBomb(1,9,7);
	drawBomb(1,10,7);

	int counter = 0;

	coin begin_coin[6];
	for (int i = 0; i < 6; i++){
		(begin_coin[6]).counter = 0;
	}


	for (int slow_down_counter = 0; slow_down_counter < 72*100; slow_down_counter++){
		if (slow_down_counter % 100 == 0){
				draw_driver(414,300,414+31,300+31,32*9,32*6,2);
//				cleanCell(9,6);
				drawExplosion(counter % 36,9,6);
				draw_driver(414,300,414+31,300+31,32*9,32*5,2);
//				cleanCell(9,5);
				drawExplosion(counter % 36,9,5);

				draw_driver(414,300,414+31,300+31,32*9,32*8,2);
//				cleanCell(9,8);
				drawExplosion(counter % 36,9,8);
				draw_driver(414,300,414+31,300+31,32*9,32*9,2);
//				cleanCell(9,9);
				drawExplosion(counter % 36,9,9);

				draw_driver(414,300,414+31,300+31,32*10,32*6,2);
//				cleanCell(10,6);
				drawExplosion(counter % 36,10,6);
				draw_driver(414,300,414+31,300+31,32*10,32*5,2);
//				cleanCell(10,5);
				drawExplosion(counter % 36,10,5);

				draw_driver(414,300,414+31,300+31,32*10,32*8,2);
//				cleanCell(10,8);
				drawExplosion(counter % 36,10,8);
				draw_driver(414,300,414+31,300+31,32*10,32*9,2);
//				cleanCell(10,9);
				drawExplosion(counter % 36,10,9);

				draw_driver(414,300,414+31,300+31,32*8,32*7,2);
//				cleanCell(8,7);
				drawExplosion(counter % 36,8,7);
				draw_driver(414,300,414+31,300+31,32*7,32*7,2);
//				cleanCell(7,7);
				drawExplosion(counter % 36,7,7);

				draw_driver(414,300,414+31,300+31,32*11,32*7,2);
//				cleanCell(11,7);
				drawExplosion(counter % 36,11,7);
		//		cleanCell(12,7);
		//		drawExplosion(counter % 36,12,7);
				draw_driver(player1_hurt_x0, player1_hurt_y0, player1_hurt_x1, player1_hurt_y1, 384,224, 1);
				draw_driver(player2_front0_x0, player2_front0_y0, player2_front0_x1, player2_front0_y1, 192,224, 1);

				counter ++;
		}

		if (slow_down_counter % 7 == 0){

			//Draw Bomb Loading
			if (counter > 0){
				draw_driver(414,300,414+31,300+31,32*7,32*12,2);
//				cleanCell(7,12);
				drawCoin(7,12,&begin_coin[0]);

			}

			if (counter > 12){
				draw_driver(414,300,414+31,300+31,32*8,32*12,2);
//				cleanCell(8,12);
				drawCoin(8,12,&begin_coin[1]);
			}

			if (counter > 24){
				draw_driver(414,300,414+31,300+31,32*9,32*12,2);
//				cleanCell(9,12);
				drawCoin(9,12,&begin_coin[2]);
			}

			if (counter > 36){
				draw_driver(414,300,414+31,300+31,32*10,32*12,2);
//				cleanCell(10,12);
				drawCoin(10,12,&begin_coin[3]);
			}

			if (counter > 48){
				draw_driver(414,300,414+31,300+31,32*11,32*12,2);
//				cleanCell(11,12);
				drawCoin(11,12,&begin_coin[4]);
			}

			if (counter > 60){
				draw_driver(414,300,414+31,300+31,32*12,32*12,2);
//				cleanCell(12,12);
				drawCoin(12,12,&begin_coin[5]);
			}

			delay(5);
		}
	}
	Audio_Select('1');
	changeBackVolume(3);
}





