#include "./header_file/drawing.h"

//notice that X and Y corresponds to cell index not pixel index
void cleanCell(unsigned short int X, unsigned short int Y){
	draw_driver(X*32, Y*32, X*32+31, Y*32+31, X*32, Y*32,0);
}

void drawSolidWall(unsigned short int X, unsigned short int Y, cell **stage){
	draw_driver(solid_wall_x0, solid_wall_y0, solid_wall_x1, solid_wall_y1, X*32, Y*32,1);
	stage[X][Y].type = 1;

}


void drawSoftWall(unsigned short int X, unsigned short int Y, cell **stage){
	draw_driver(soft_wall_x0, soft_wall_y0, soft_wall_x1, soft_wall_y1, X*32, Y*32, 1);
	stage[X][Y].type = 2;
}


void cleanPlayer(player *player1){
	if(player1->moveCounter==100){player1->moveCounter=0;}
	else{player1->moveCounter++;}
	draw_driver(player1->x, player1->y, player1->x+25, player1->y+25, player1->x, player1->y, 0);
}

void drawPlayer(unsigned short int dir, player *player1, unsigned short int moving){
	unsigned short int index = player1->index;
	if(moving == 1){
		if(index == 0){
		     if(player1->moveCounter<50){
				switch(dir){
					case 0:
						draw_driver(player1_back1_x0, player1_back1_y0, player1_back1_x1, player1_back1_y1, player1->x, player1->y, 1);
						break;
					case 1:
						draw_driver(player1_front1_x0, player1_front1_y0, player1_front1_x1, player1_front1_y1, player1->x, player1->y, 1);
						break;
					case 2:
						draw_driver(player1_left1_x0, player1_left1_y0, player1_left1_x1, player1_left1_y1, player1->x, player1->y, 1);
						break;
					case 3:
						draw_driver(player1_right1_x0, player1_right1_y0, player1_right1_x1, player1_right1_y1, player1->x, player1->y, 1);
						break;
				}
			}
			else{
				switch(dir){
					case 0:
						draw_driver(player1_back2_x0, player1_back2_y0, player1_back2_x1, player1_back2_y1, player1->x, player1->y, 1);
						break;
					case 1:
						draw_driver(player1_front2_x0, player1_front2_y0, player1_front2_x1, player1_front2_y1, player1->x, player1->y, 1);
						break;
					case 2:
						draw_driver(player1_left2_x0, player1_left2_y0, player1_left2_x1, player1_left2_y1, player1->x, player1->y, 1);
						break;
					case 3:
						draw_driver(player1_right2_x0, player1_right2_y0, player1_right2_x1, player1_right2_y1, player1->x, player1->y, 1);
						break;
				}
			}
		}
		else{
		     if(player1->moveCounter<50){
				switch(dir){
					case 0:
						draw_driver(player2_back1_x0, player2_back1_y0, player2_back1_x1, player2_back1_y1, player1->x, player1->y, 1);
						break;
					case 1:
						draw_driver(player2_front1_x0, player2_front1_y0, player2_front1_x1, player2_front1_y1, player1->x, player1->y, 1);
						break;
					case 2:
						draw_driver(player2_left1_x0, player2_left1_y0, player2_left1_x1, player2_left1_y1, player1->x, player1->y, 1);
						break;
					case 3:
						draw_driver(player2_right1_x0, player2_right1_y0, player2_right1_x1, player2_right1_y1, player1->x, player1->y, 1);
						break;
				}
			}
			else{
				switch(dir){
					case 0:
						draw_driver(player2_back2_x0, player2_back2_y0, player2_back2_x1, player2_back2_y1, player1->x, player1->y, 1);
						break;
					case 1:
						draw_driver(player2_front2_x0, player2_front2_y0, player2_front2_x1, player2_front2_y1, player1->x, player1->y, 1);
						break;
					case 2:
						draw_driver(player2_left2_x0, player2_left2_y0, player2_left2_x1, player2_left2_y1, player1->x, player1->y, 1);
						break;
					case 3:
						draw_driver(player2_right2_x0, player2_right2_y0, player2_right2_x1, player2_right2_y1, player1->x, player1->y, 1);
						break;
				}
			}
		}
	}
	else{
		if(index == 0){
			switch(dir){
				case 0:
					draw_driver(player1_back0_x0, player1_back0_y0, player1_back0_x1, player1_back0_y1, player1->x, player1->y, 1);
					break;
				case 1:
					draw_driver(player1_front0_x0, player1_front0_y0, player1_front0_x1, player1_front0_y1, player1->x, player1->y, 1);
					break;
				case 2:
					draw_driver(player1_left0_x0, player1_left0_y0, player1_left0_x1, player1_left0_y1, player1->x, player1->y, 1);
					break;
				case 3:
					draw_driver(player1_right0_x0, player1_right0_y0, player1_right0_x1, player1_right0_y1, player1->x, player1->y, 1);
					break;
			}
		}
		else{
			switch(dir){
				case 0:
					draw_driver(player2_back0_x0, player2_back0_y0, player2_back0_x1, player2_back0_y1, player1->x, player1->y, 1);
					break;
				case 1:
					draw_driver(player2_front0_x0, player2_front0_y0, player2_front0_x1, player2_front0_y1, player1->x, player1->y, 1);
					break;
				case 2:
					draw_driver(player2_left0_x0, player2_left0_y0, player2_left0_x1, player2_left0_y1, player1->x, player1->y, 1);
					break;
				case 3:
					draw_driver(player2_right0_x0, player2_right0_y0, player2_right0_x1, player2_right0_y1, player1->x, player1->y, 1);
					break;
			}
		}
	}
}

void drawPlayerHurt(player *playerA){
	cleanPlayer(playerA);
	if(playerA->index==0){
		draw_driver(player1_hurt_x0, player1_hurt_y0, player1_hurt_x1, player1_hurt_y1, playerA->x, playerA->y, 1);
	}
	else{
		draw_driver(player2_hurt_x0, player2_hurt_y0, player2_hurt_x1, player2_hurt_y1, playerA->x, playerA->y, 1);
	}
}

//notice that X and Y corresponds to cell index not pixel index
void drawExplosion(unsigned short int counter, unsigned short int X, unsigned short int Y){
	switch(counter){
		case 0:
			draw_driver(explosion0_x0, explosion0_y0, explosion0_x1, explosion0_y1, X*32, Y*32, 1);
			break;
		case 1:
			draw_driver(explosion1_x0, explosion1_y0, explosion1_x1, explosion1_y1, X*32, Y*32, 1);
			break;
		case 2:
			draw_driver(explosion2_x0, explosion2_y0, explosion2_x1, explosion2_y1, X*32, Y*32, 1);
			break;
		case 3:
			draw_driver(explosion3_x0, explosion3_y0, explosion3_x1, explosion3_y1, X*32, Y*32, 1);
			break;
		case 4:
			draw_driver(explosion4_x0, explosion4_y0, explosion4_x1, explosion4_y1, X*32, Y*32, 1);
			break;
		case 5:
			draw_driver(explosion5_x0, explosion5_y0, explosion5_x1, explosion5_y1, X*32, Y*32, 1);
			break;
		case 6:
			draw_driver(explosion6_x0, explosion6_y0, explosion6_x1, explosion6_y1, X*32, Y*32, 1);
			break;
		case 7:
			draw_driver(explosion7_x0, explosion7_y0, explosion7_x1, explosion7_y1, X*32, Y*32, 1);
			break;
		case 8:
			draw_driver(explosion8_x0, explosion8_y0, explosion8_x1, explosion8_y1, X*32, Y*32, 1);
			break;
		case 9:
			draw_driver(explosion9_x0, explosion9_y0, explosion9_x1, explosion9_y1, X*32, Y*32, 1);
			break;
		case 10:
			draw_driver(explosion10_x0, explosion10_y0, explosion10_x1, explosion10_y1, X*32, Y*32, 1);
			break;
		case 11:
			draw_driver(explosion11_x0, explosion11_y0, explosion11_x1, explosion11_y1, X*32, Y*32, 1);
			break;
		case 12:
			draw_driver(explosion12_x0, explosion12_y0, explosion12_x1, explosion12_y1, X*32, Y*32, 1);
			break;
		case 13:
			draw_driver(explosion13_x0, explosion13_y0, explosion13_x1, explosion13_y1, X*32, Y*32, 1);
			break;
		case 14:
			draw_driver(explosion14_x0, explosion14_y0, explosion14_x1, explosion14_y1, X*32, Y*32, 1);
			break;
		case 15:
			draw_driver(explosion15_x0, explosion15_y0, explosion15_x1, explosion15_y1, X*32, Y*32, 1);
			break;
		case 16:
			draw_driver(explosion16_x0, explosion16_y0, explosion16_x1, explosion16_y1, X*32, Y*32, 1);
			break;
		case 17:
			draw_driver(explosion17_x0, explosion17_y0, explosion17_x1, explosion17_y1, X*32, Y*32, 1);
			break;
		case 18:
			draw_driver(explosion18_x0, explosion18_y0, explosion18_x1, explosion18_y1, X*32, Y*32, 1);
			break;
		case 19:
			draw_driver(explosion19_x0, explosion19_y0, explosion19_x1, explosion19_y1, X*32, Y*32, 1);
			break;
		case 20:
			draw_driver(explosion20_x0, explosion20_y0, explosion20_x1, explosion20_y1, X*32, Y*32, 1);
			break;
		case 21:
			draw_driver(explosion21_x0, explosion21_y0, explosion21_x1, explosion21_y1, X*32, Y*32, 1);
			break;
		case 22:
			draw_driver(explosion22_x0, explosion22_y0, explosion22_x1, explosion22_y1, X*32, Y*32, 1);
			break;
		case 23:
			draw_driver(explosion23_x0, explosion23_y0, explosion23_x1, explosion23_y1, X*32, Y*32, 1);
			break;
		case 24:
			draw_driver(explosion24_x0, explosion24_y0, explosion24_x1, explosion24_y1, X*32, Y*32, 1);
			break;
		case 25:
			draw_driver(explosion25_x0, explosion25_y0, explosion25_x1, explosion25_y1, X*32, Y*32, 1);
			break;
		case 26:
			draw_driver(explosion26_x0, explosion26_y0, explosion26_x1, explosion26_y1, X*32, Y*32, 1);
			break;
		case 27:
			draw_driver(explosion27_x0, explosion27_y0, explosion27_x1, explosion27_y1, X*32, Y*32, 1);
			break;
		case 28:
			draw_driver(explosion28_x0, explosion28_y0, explosion28_x1, explosion28_y1, X*32, Y*32, 1);
			break;
		case 29:
			draw_driver(explosion29_x0, explosion29_y0, explosion29_x1, explosion29_y1, X*32, Y*32, 1);
			break;
		case 30:
			draw_driver(explosion30_x0, explosion30_y0, explosion30_x1, explosion30_y1, X*32, Y*32, 1);
			break;
		case 31:
			draw_driver(explosion31_x0, explosion31_y0, explosion31_x1, explosion31_y1, X*32, Y*32, 1);
			break;
		case 32:
			draw_driver(explosion32_x0, explosion32_y0, explosion32_x1, explosion32_y1, X*32, Y*32, 1);
			break;
		case 33:
			draw_driver(explosion33_x0, explosion33_y0, explosion33_x1, explosion33_y1, X*32, Y*32, 1);
			break;
		case 34:
			draw_driver(explosion34_x0, explosion34_y0, explosion34_x1, explosion34_y1, X*32, Y*32, 1);
			break;
		case 35:
			draw_driver(explosion35_x0, explosion35_y0, explosion35_x1, explosion35_y1, X*32, Y*32, 1);
			break;
		default:
			break;
	}
}

//notice that X and Y corresponds to cell index not pixel index
void drawBomb(unsigned short int counter, unsigned short int X, unsigned short int Y){
	switch(counter){
		case 0:
			draw_driver(bomb0_x0, bomb0_y0, bomb0_x1, bomb0_y1, X*32, Y*32, 1);
			break;
		case 1:
			draw_driver(bomb1_x0, bomb1_y0, bomb1_x1, bomb1_y1, X*32, Y*32, 1);
			break;
		case 2:
			draw_driver(bomb2_x0, bomb2_y0, bomb2_x1, bomb2_y1, X*32, Y*32, 1);
			break;
		case 3:
			draw_driver(bomb3_x0, bomb3_y0, bomb3_x1, bomb3_y1, X*32, Y*32, 1);
			break;
		case 4:
			draw_driver(bomb4_x0, bomb4_y0, bomb4_x1, bomb4_y1, X*32, Y*32, 1);
			break;
		case 5:
			draw_driver(bomb5_x0, bomb5_y0, bomb5_x1, bomb5_y1, X*32, Y*32, 1);
			break;
		case 6:
			draw_driver(bomb6_x0, bomb6_y0, bomb6_x1, bomb6_y1, X*32, Y*32, 1);
			break;
		case 7:
			draw_driver(bomb7_x0, bomb7_y0, bomb7_x1, bomb7_y1, X*32, Y*32, 1);
			break;
		case 8:
			draw_driver(bomb8_x0, bomb8_y0, bomb8_x1, bomb8_y1, X*32, Y*32, 1);
			break;
		case 9:
			draw_driver(bomb9_x0, bomb9_y0, bomb9_x1, bomb9_y1, X*32, Y*32, 1);
			break;
		case 10:
			draw_driver(bomb10_x0, bomb10_y0, bomb10_x1, bomb10_y1, X*32, Y*32, 1);
			break;
		case 11:
			draw_driver(bomb11_x0, bomb11_y0, bomb11_x1, bomb11_y1, X*32, Y*32, 1);
			break;
		case 12:
			draw_driver(bomb12_x0, bomb12_y0, bomb12_x1, bomb12_y1, X*32, Y*32, 1);
			break;
		case 13:
			draw_driver(bomb13_x0, bomb13_y0, bomb13_x1, bomb13_y1, X*32, Y*32, 1);
			break;
		case 14:
			draw_driver(bomb14_x0, bomb14_y0, bomb14_x1, bomb14_y1, X*32, Y*32, 1);
			break;
		case 15:
			draw_driver(bomb15_x0, bomb15_y0, bomb15_x1, bomb15_y1, X*32, Y*32, 1);
			break;
		case 16:
			draw_driver(bomb16_x0, bomb16_y0, bomb16_x1, bomb16_y1, X*32, Y*32, 1);
			break;
		case 17:
			draw_driver(bomb17_x0, bomb17_y0, bomb17_x1, bomb17_y1, X*32, Y*32, 1);
			break;
		case 18:
			draw_driver(bomb18_x0, bomb18_y0, bomb18_x1, bomb18_y1, X*32, Y*32, 1);
			break;
		case 19:
			draw_driver(bomb19_x0, bomb19_y0, bomb19_x1, bomb19_y1, X*32, Y*32, 1);
			break;
		case 20:
			draw_driver(bomb20_x0, bomb20_y0, bomb20_x1, bomb20_y1, X*32, Y*32, 1);
			break;
		case 21:
			draw_driver(bomb21_x0, bomb21_y0, bomb21_x1, bomb21_y1, X*32, Y*32, 1);
			break;
		case 22:
			draw_driver(bomb22_x0, bomb22_y0, bomb22_x1, bomb22_y1, X*32, Y*32, 1);
			break;
		case 23:
			draw_driver(bomb23_x0, bomb23_y0, bomb23_x1, bomb23_y1, X*32, Y*32, 1);
			break;
		case 24:
			draw_driver(bomb24_x0, bomb24_y0, bomb24_x1, bomb24_y1, X*32, Y*32, 1);
			break;
		case 25:
			draw_driver(bomb25_x0, bomb25_y0, bomb25_x1, bomb25_y1, X*32, Y*32, 1);
			break;
		case 26:
			draw_driver(bomb26_x0, bomb26_y0, bomb26_x1, bomb26_y1, X*32, Y*32, 1);
			break;
		case 27:
			draw_driver(bomb27_x0, bomb27_y0, bomb27_x1, bomb27_y1, X*32, Y*32, 1);
			break;
		case 28:
			draw_driver(bomb28_x0, bomb28_y0, bomb28_x1, bomb28_y1, X*32, Y*32, 1);
			break;
		case 29:
			draw_driver(bomb29_x0, bomb29_y0, bomb29_x1, bomb29_y1, X*32, Y*32, 1);
			break;
		case 30:
			draw_driver(bomb30_x0, bomb30_y0, bomb30_x1, bomb30_y1, X*32, Y*32, 1);
			break;
		case 31:
			draw_driver(bomb31_x0, bomb31_y0, bomb31_x1, bomb31_y1, X*32, Y*32, 1);
			break;
		case 32:
			draw_driver(bomb32_x0, bomb32_y0, bomb32_x1, bomb32_y1, X*32, Y*32, 1);
			break;
		case 33:
			draw_driver(bomb33_x0, bomb33_y0, bomb33_x1, bomb33_y1, X*32, Y*32, 1);
			break;
		case 34:
			draw_driver(bomb34_x0, bomb34_y0, bomb34_x1, bomb34_y1, X*32, Y*32, 1);
			break;
		case 35:
			draw_driver(bomb35_x0, bomb35_y0, bomb35_x1, bomb35_y1, X*32, Y*32, 1);
			break;
		case 36:
			draw_driver(bomb36_x0, bomb36_y0, bomb36_x1, bomb36_y1, X*32, Y*32, 1);
			break;
		case 37:
			draw_driver(bomb37_x0, bomb37_y0, bomb37_x1, bomb37_y1, X*32, Y*32, 1);
			break;
		case 38:
			draw_driver(bomb38_x0, bomb38_y0, bomb38_x1, bomb38_y1, X*32, Y*32, 1);
			break;
		case 39:
			draw_driver(bomb39_x0, bomb39_y0, bomb39_x1, bomb39_y1, X*32, Y*32, 1);
			break;
		case 40:
			draw_driver(bomb40_x0, bomb40_y0, bomb40_x1, bomb40_y1, X*32, Y*32, 1);
			break;
		case 41:
			draw_driver(bomb41_x0, bomb41_y0, bomb41_x1, bomb41_y1, X*32, Y*32, 1);
			break;
		case 42:
			draw_driver(bomb42_x0, bomb42_y0, bomb42_x1, bomb42_y1, X*32, Y*32, 1);
			break;
		case 43:
			draw_driver(bomb43_x0, bomb43_y0, bomb43_x1, bomb43_y1, X*32, Y*32, 1);
			break;
		case 44:
			draw_driver(bomb44_x0, bomb44_y0, bomb44_x1, bomb44_y1, X*32, Y*32, 1);
			break;
		case 45:
			draw_driver(bomb45_x0, bomb45_y0, bomb45_x1, bomb45_y1, X*32, Y*32, 1);
			break;
		case 46:
			draw_driver(bomb46_x0, bomb46_y0, bomb46_x1, bomb46_y1, X*32, Y*32, 1);
			break;
		case 47:
			draw_driver(bomb47_x0, bomb47_y0, bomb47_x1, bomb47_y1, X*32, Y*32, 1);
			break;
		case 48:
			draw_driver(bomb48_x0, bomb48_y0, bomb48_x1, bomb48_y1, X*32, Y*32, 1);
			break;

		default:
			break;
	}
}



//notice that X and Y corresponds to cell index not pixel index
void drawFiringWall(unsigned short int counter, unsigned short int X, unsigned short int Y){
	switch(counter){
		case 0:
			draw_driver(firingWall0_x0, firingWall0_y0, firingWall0_x1, firingWall0_y1, X*32, Y*32, 1);
			break;
		case 1:
			draw_driver(firingWall1_x0, firingWall1_y0, firingWall1_x1, firingWall1_y1, X*32, Y*32, 1);
			break;
		case 2:
			draw_driver(firingWall2_x0, firingWall2_y0, firingWall2_x1, firingWall2_y1, X*32, Y*32, 1);
			break;
		case 3:
			draw_driver(firingWall3_x0, firingWall3_y0, firingWall3_x1, firingWall3_y1, X*32, Y*32, 1);
			break;
		case 4:
			draw_driver(firingWall4_x0, firingWall4_y0, firingWall4_x1, firingWall4_y1, X*32, Y*32, 1);
			break;
		case 5:
			draw_driver(firingWall5_x0, firingWall5_y0, firingWall5_x1, firingWall5_y1, X*32, Y*32, 1);
			break;
		case 6:
			draw_driver(firingWall6_x0, firingWall6_y0, firingWall6_x1, firingWall6_y1, X*32, Y*32, 1);
			break;
		case 7:
			draw_driver(firingWall7_x0, firingWall7_y0, firingWall7_x1, firingWall7_y1, X*32, Y*32, 1);
			break;
		case 8:
			draw_driver(firingWall8_x0, firingWall8_y0, firingWall8_x1, firingWall8_y1, X*32, Y*32, 1);
			break;
		case 9:
			draw_driver(firingWall9_x0, firingWall9_y0, firingWall9_x1, firingWall9_y1, X*32, Y*32, 1);
			break;
		case 10:
			draw_driver(firingWall10_x0, firingWall10_y0, firingWall10_x1, firingWall10_y1, X*32, Y*32, 1);
			break;
		case 11:
			draw_driver(firingWall11_x0, firingWall11_y0, firingWall11_x1, firingWall11_y1, X*32, Y*32, 1);
			break;
		case 12:
			draw_driver(firingWall12_x0, firingWall12_y0, firingWall12_x1, firingWall12_y1, X*32, Y*32, 1);
			break;
		case 13:
			draw_driver(firingWall13_x0, firingWall13_y0, firingWall13_x1, firingWall13_y1, X*32, Y*32, 1);
			break;
		case 14:
			draw_driver(firingWall14_x0, firingWall14_y0, firingWall14_x1, firingWall14_y1, X*32, Y*32, 1);
			break;
		case 15:
			draw_driver(firingWall15_x0, firingWall15_y0, firingWall15_x1, firingWall15_y1, X*32, Y*32, 1);
			break;
		case 16:
			draw_driver(firingWall16_x0, firingWall16_y0, firingWall16_x1, firingWall16_y1, X*32, Y*32, 1);
			break;
		case 17:
			draw_driver(firingWall17_x0, firingWall17_y0, firingWall17_x1, firingWall17_y1, X*32, Y*32, 1);
			break;
		case 18:
			draw_driver(firingWall18_x0, firingWall18_y0, firingWall18_x1, firingWall18_y1, X*32, Y*32, 1);
			break;
		case 19:
			draw_driver(firingWall19_x0, firingWall19_y0, firingWall19_x1, firingWall19_y1, X*32, Y*32, 1);
			break;
		case 20:
			draw_driver(firingWall20_x0, firingWall20_y0, firingWall20_x1, firingWall20_y1, X*32, Y*32, 1);
			break;
		case 21:
			draw_driver(firingWall21_x0, firingWall21_y0, firingWall21_x1, firingWall21_y1, X*32, Y*32, 1);
			break;
		case 22:
			draw_driver(firingWall22_x0, firingWall22_y0, firingWall22_x1, firingWall22_y1, X*32, Y*32, 1);
			break;
		case 23:
			draw_driver(firingWall23_x0, firingWall23_y0, firingWall23_x1, firingWall23_y1, X*32, Y*32, 1);
			break;
		case 24:
			draw_driver(firingWall24_x0, firingWall24_y0, firingWall24_x1, firingWall24_y1, X*32, Y*32, 1);
			break;
		case 25:
			draw_driver(firingWall25_x0, firingWall25_y0, firingWall25_x1, firingWall25_y1, X*32, Y*32, 1);
			break;
		case 26:
			draw_driver(firingWall26_x0, firingWall26_y0, firingWall26_x1, firingWall26_y1, X*32, Y*32, 1);
			break;
		case 27:
			draw_driver(firingWall27_x0, firingWall27_y0, firingWall27_x1, firingWall27_y1, X*32, Y*32, 1);
			break;
		case 28:
			draw_driver(firingWall28_x0, firingWall28_y0, firingWall28_x1, firingWall28_y1, X*32, Y*32, 1);
			break;
		case 29:
			draw_driver(firingWall29_x0, firingWall29_y0, firingWall29_x1, firingWall29_y1, X*32, Y*32, 1);
			break;
		case 30:
			draw_driver(firingWall30_x0, firingWall30_y0, firingWall30_x1, firingWall30_y1, X*32, Y*32, 1);
			break;
		case 31:
			draw_driver(firingWall31_x0, firingWall31_y0, firingWall31_x1, firingWall31_y1, X*32, Y*32, 1);
			break;
		case 32:
			draw_driver(firingWall32_x0, firingWall32_y0, firingWall32_x1, firingWall32_y1, X*32, Y*32, 1);
			break;
		case 33:
			draw_driver(firingWall33_x0, firingWall33_y0, firingWall33_x1, firingWall33_y1, X*32, Y*32, 1);
			break;
		case 34:
			draw_driver(firingWall34_x0, firingWall34_y0, firingWall34_x1, firingWall34_y1, X*32, Y*32, 1);
			break;
		case 35:
			draw_driver(firingWall35_x0, firingWall35_y0, firingWall35_x1, firingWall35_y1, X*32, Y*32, 1);
			break;
		default:
			break;
	}
}



void drawBombAndExplosion(unsigned short int index, unsigned short int counter, unsigned short int X, unsigned short int Y,
cell**stage, cellXY**head, cellXY **tail){
	if(counter < 0){return;}
	if(counter <= 48){
		cleanCell(X, Y);
		drawBomb(counter, X, Y);
		if(counter == 47){Bomb();}
	}
	else if (counter >900){
		stage[X][Y].type=0;
		cleanCell(X, Y);
		for(short int X0 = (short int)X-1; X0>=(short int)X-2; X0--){
			if(X0<0){break;}
			if(stage[X0][Y].type==index){stage[X0][Y].type=0;cleanCell(X0,Y);}
			else if(stage[X0][Y].type==1){break;}
			else if(stage[X0][Y].type>=234){
				stage[X0][Y].type=6;
				stage[X0][Y].ptr =(coin*)malloc(sizeof(coin));
				stage[X0][Y].ptr->counter=0;
				pushToCoinList(X0, Y, head, tail);
				cleanCell(X0,Y);
				break;}
		}
		for(short int X0 = (short int)X+1; X0<=(short int)X+2; X0++){
			if(X0>19){break;}
			if(stage[X0][Y].type==index){stage[X0][Y].type=0;cleanCell(X0,Y);}
			else if(stage[X0][Y].type==1){break;}
			else if(stage[X0][Y].type>=234){
				stage[X0][Y].type=6;
				stage[X0][Y].ptr =(coin*)malloc(sizeof(coin));
				stage[X0][Y].ptr->counter=0;
				pushToCoinList(X0, Y, head, tail);
				cleanCell(X0,Y);
				break;
			}
		}
		for(short int Y0 = (short int)Y-1; Y0>=(short int)Y-2; Y0--){
			if(Y0<0){break;}
			if(stage[X][Y0].type==index){stage[X][Y0].type=0;cleanCell(X,Y0);}
			else if(stage[X][Y0].type==1){break;}
			else if(stage[X][Y0].type>=234){
				stage[X][Y0].type=6;
				stage[X][Y0].ptr =(coin*)malloc(sizeof(coin));
				stage[X][Y0].ptr->counter=0;
				pushToCoinList(X, Y0, head, tail);
				cleanCell(X,Y0);
				break;
			}
		}
		for(short int Y0 = (short int)Y+1; Y0<=(short int)Y+2; Y0++){
			if(Y0>14){break;}
			if(stage[X][Y0].type==index){stage[X][Y0].type=0;cleanCell(X,Y0);}
			else if(stage[X][Y0].type==1){break;}
			else if(stage[X][Y0].type>=234){
				stage[X][Y0].type=6;
				stage[X][Y0].ptr =(coin*)malloc(sizeof(coin));
				stage[X][Y0].ptr->counter=0;
				pushToCoinList(X, Y0, head, tail);
				cleanCell(X,Y0);
				break;
			}
		}
	}
	else{
		cleanCell(X, Y);
		drawExplosion(counter-49, X, Y);
		stage[X][Y].type=index;
        for(short int X0 = (short int)X-1; X0>=(short int)X-2; X0--){
            if(X0<0){break;}
            //nothing
            else if(stage[X0][Y].type==0){
            	stage[X0][Y].type=index;
                cleanCell(X0,Y);
                drawExplosion(counter-49, X0, Y);
            }
            //solid wall
            else if(stage[X0][Y].type==1){break;}
            //soft wall
            else if(stage[X0][Y].type==2){
                cleanCell(X0,Y);
                drawFiringWall(counter-49, X0, Y);
                stage[X0][Y].type = 200;
            	break;
            }
            else if(stage[X0][Y].type>=200 && stage[X0][Y].type<300){
            	if(counter-49+200 < stage[X0][Y].type){break;}
                cleanCell(X0,Y);
                drawFiringWall(counter-49, X0, Y);
                stage[X0][Y].type++;
            	break;
            }
            //bomb
            else if(stage[X0][Y].type==3){break;}
            //explosion
            else if(stage[X0][Y].type==index){
            	cleanCell(X0,Y);
            	drawExplosion(counter-49, X0, Y);
            }
        }
        for(short int X0 = (short int)X+1; X0<=(short int)X+2; X0++){
            if(X0>19){break;}
            //nothing
			else if(stage[X0][Y].type==0){
				stage[X0][Y].type=index;
				cleanCell(X0,Y);
				drawExplosion(counter-49, X0, Y);

			}
			//solid wall
			else if(stage[X0][Y].type==1){break;}
			//soft wall
			else if(stage[X0][Y].type==2){
				cleanCell(X0,Y);
				drawFiringWall(counter-49, X0, Y);
				stage[X0][Y].type=200;
				break;
			}
            else if(stage[X0][Y].type>=200 && stage[X0][Y].type<300){
            	if(counter-49+200 < stage[X0][Y].type){break;}
                cleanCell(X0,Y);
                drawFiringWall(counter-49, X0, Y);
                stage[X0][Y].type++;
            	break;
            }
			//bomb
			else if(stage[X0][Y].type==3){break;}
            //explosion
			else if(stage[X0][Y].type==index){
				cleanCell(X0,Y);
				drawExplosion(counter-49, X0, Y);
			}
        }
        for(short int Y0 = (short int)Y-1; Y0>=(short int)Y-2; Y0--){
            if(Y0<0){break;}
            //nothing
			else if(stage[X][Y0].type==0){
				stage[X][Y0].type=index;
				cleanCell(X,Y0);
				drawExplosion(counter-49, X, Y0);

			}
			//solid wall
			else if(stage[X][Y0].type==1){break;}
			//soft wall
			else if(stage[X][Y0].type==2){
				cleanCell(X,Y0);
				drawFiringWall(counter-49, X, Y0);
				stage[X][Y0].type=200;
				break;
			}
            else if(stage[X][Y0].type>=200 && stage[X][Y0].type<300){
            	if(counter-49+200 < stage[X][Y0].type){break;}
                cleanCell(X,Y0);
                drawFiringWall(counter-49, X, Y0);
                stage[X][Y0].type++;
            	break;
            }
			//bomb
			else if(stage[X][Y0].type==3){break;}
            //explosion
			else if(stage[X][Y0].type==index){
				cleanCell(X,Y0);
				drawExplosion(counter-49, X, Y0);
			}
        }
        for(short int Y0 = (short int)Y+1; Y0<=(short int)Y+2; Y0++){
            if(Y0>14){break;}
            //nothing
			else if(stage[X][Y0].type==0){
				stage[X][Y0].type=index;
				cleanCell(X,Y0);
				drawExplosion(counter-49, X, Y0);
			}
			//solid wall
			else if(stage[X][Y0].type==1){break;}
			//soft wall
			else if(stage[X][Y0].type==2){
				cleanCell(X,Y0);
				drawFiringWall(counter-49, X, Y0);
				stage[X][Y0].type=200;
				break;
			}
            else if(stage[X][Y0].type>=200 && stage[X][Y0].type<300){
            	if(counter-49+200 < stage[X][Y0].type){break;}
                cleanCell(X,Y0);
                drawFiringWall(counter-49, X, Y0);
                stage[X][Y0].type++;
            	break;
            }
			//bomb
			else if(stage[X][Y0].type==3){break;}
            //explosion
			else if(stage[X][Y0].type==index){
				cleanCell(X,Y0);
				drawExplosion(counter-49, X, Y0);
			}
        }
	}
}

void pushToCoinList(unsigned short int X, unsigned short int Y, cellXY**head, cellXY**tail){
	cellXY *one = (cellXY *)malloc(sizeof(cellXY));
	one->X = X;
	one->Y = Y;
	if(*tail ==NULL){
		*tail = one;
		*head = one;
		one->next = NULL;
		one->prev = NULL;
	}
	else{
		(*tail)->next = one;
		one->next = NULL;
		one->prev = *tail;
		*tail = one;
	}
	//printf("Try to push into coin list\n");
}

void drawCoin(unsigned short int X, unsigned short int Y, coin *ptr){
	unsigned int x0 = X*32+5;
	unsigned int y0 = Y*32+5;
    switch(ptr->counter/10%10){
    	case(0):
				draw_driver(coin0_x0, coin0_y0, coin0_x1, coin0_y1, x0, y0, 1);
    			break;
    	case(1):
				draw_driver(coin1_x0, coin1_y0, coin1_x1, coin1_y1, x0, y0, 1);
    			break;
    	case(2):
				draw_driver(coin2_x0, coin2_y0, coin2_x1, coin2_y1, x0, y0, 1);
    			break;
    	case(3):
				draw_driver(coin3_x0, coin3_y0, coin3_x1, coin3_y1, x0, y0, 1);
    			break;
    	case(4):
				draw_driver(coin4_x0, coin4_y0, coin4_x1, coin4_y1, x0, y0, 1);
    			break;
    	case(5):
				draw_driver(coin5_x0, coin5_y0, coin5_x1, coin5_y1, x0, y0, 1);
    			break;
    	case(6):
				draw_driver(coin6_x0, coin6_y0, coin6_x1, coin6_y1, x0, y0, 1);
    			break;
    	case(7):
				draw_driver(coin7_x0, coin7_y0, coin7_x1, coin7_y1, x0, y0, 1);
    			break;
    	case(8):
				draw_driver(coin8_x0, coin8_y0, coin8_x1, coin8_y1, x0, y0, 1);
    			break;
    	case(9):
				draw_driver(coin9_x0, coin9_y0, coin9_x1, coin9_y1, x0, y0, 1);
    			break;
    }
    ptr->counter ++;
}

void cleanCoin(unsigned short int X, unsigned short int Y){
	unsigned int x0 = X*32+5;
	unsigned int y0 = Y*32+5;
	draw_driver(x0, y0, x0+21, y0+21, x0, y0, 0);
}
