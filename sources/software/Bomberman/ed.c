#include "./header_file/ed.h"

void initED(int ending){

	draw_driver(0,0,639,479,0,0,3);
	//player 1 wins
    if(ending == 1){
    	draw_driver(player1_front0_x0, player1_front0_y0, player1_front0_x1, player1_front0_y1, 280,144, 1);
    	draw_driver(player2_hurt_x0, player2_hurt_y0, player2_hurt_x1, player2_hurt_y1, 320,144, 1);
    }
    //player 2 wins
    else if(ending ==2){
    	draw_driver(player2_front0_x0, player2_front0_y0, player2_front0_x1, player2_front0_y1, 280,144, 1);
    	draw_driver(player1_hurt_x0, player1_hurt_y0, player1_hurt_x1, player1_hurt_y1, 320,144, 1);
    }
    //player 3 wins
    else{
    	draw_driver(player1_front0_x0, player1_front0_y0, player1_front0_x1, player1_front0_y1, 280,144, 1);
    	draw_driver(player2_front0_x0, player2_front0_y0, player2_front0_x1, player2_front0_y1, 320,144, 1);
    }
    Audio_Select('w');
}

//if user presses replay, return 1
//else return 0
int ed(unsigned int keycode[],unsigned int counter){
	if(counter%400==0){
		draw_driver(PETRP_x0,PETRP_y0,PETRP_x1,PETRP_y1,180,300,1);
	}
	if(counter%400==200){
		draw_driver(240,300,240+PETRP_x1-PETRP_x0,300+PETRP_y1-PETRP_y0,180,300,3);
	}
	if(ENTER_en(keycode)){return 1;}
	else{return 0;}
}
