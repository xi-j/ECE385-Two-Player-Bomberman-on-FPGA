#include "./header_file/game.h"

//index, x, y, HP, score, step, bombList, bombCounter, lastMove, MoveCounter,keyCounter
static player player1 = {0, 3,  3,  3,0,0,1, NULL, 3,0, 1,1,1};
static player player2 = {1, 606,447,3,0,0,1, NULL, 3,0, 0,1,1};
static cell **stage;
static cellXY *coinHead=NULL;
static cellXY *coinTail=NULL;
static clock_t begin;
static int currentSec=180;
static size_t beginFlag=1;
static size_t bgmFlag=1;

int game(unsigned int keycode[]){

	//part 0: update time
    if(beginFlag){beginFlag=0;begin=clock();currentSec=180;}
    else if(currentSec>0){
    	double time_spent = (double)(clock()-begin)/CLOCKS_PER_SEC;
    	currentSec = 180 - (unsigned int)time_spent;
    	displayTime(currentSec);
    }
    //part 0.5: change BGM?
    if(bgmFlag && (currentSec <90 || player1.HP<2 || player2.HP<2)){Audio_Select('2');bgmFlag =0;}
	//part 1: update bomb and coins
	UpdateBomb(&player1, &player2);
    UpdateCoins(&coinHead, &coinTail, &stage);
    if(player1.bombTimingCounter!=0){player1.bombTimingCounter--;}
    if(player2.bombTimingCounter!=0){player2.bombTimingCounter--;}
    //part 2: player catch coins?
    unsigned int player1get = getCoins(player1.x, player1.y, &coinHead, &coinTail, &stage);

    unsigned int player2get = getCoins(player2.x, player2.y, &coinHead, &coinTail, &stage);

    if (player1get){
    	printf("player1's score is %d\n", player1.score);
    	player1.score += player1get;
    }

    if (player2get){
    	printf("player2's score is %d\n", player2.score);
    	player2.score += player2get;
    }

    displayScore(&player1, &player2);

	//part 3A: player1 key control
	if(player1.HPbuffer<250){
		unsigned int flag = 0;
		if(W_en(keycode)){move(&player1, &player2, 0);flag=1;}
		if(S_en(keycode)){move(&player1, &player2, 1);flag=1;}
		if(A_en(keycode)){move(&player1, &player2, 2);flag=1;}
		if(D_en(keycode)){move(&player1, &player2, 3);flag=1;}
		if(SPACE_en(keycode)){
			placeBomb(&player1, &player2);
			cleanPlayer(&player1);
			drawPlayer(player1.lastMove, &player1,0);
			player1.anyAction =1;
			flag=1;
		}
		if(!flag && player1.anyAction==1){
			if(player1.HPbuffer==0){
				player1.anyAction =0;
			}
			cleanPlayer(&player1);
			drawPlayer(player1.lastMove, &player1,0);
		}
	}
	else{
		drawPlayerHurt(&player1);
		player1.anyAction =1;
	}
	//part 3B: player2 key control
	if(player2.HPbuffer<250){
		unsigned int flag = 0;
		if(UP_en(keycode))   {move(&player2,&player1, 0);flag=1;}
	    if(DOWN_en(keycode)) {move(&player2,&player1, 1);flag=1;}
		if(LEFT_en(keycode)) {move(&player2,&player1, 2);flag=1;}
		if(RIGHT_en(keycode)){move(&player2,&player1, 3);flag=1;}
		if(ENTER_en(keycode)){
			placeBomb(&player2, &player1);
			cleanPlayer(&player2);
			drawPlayer(player2.lastMove, &player2,0);
			player2.anyAction =1;
			flag=1;
		}
		if(!flag && player2.anyAction==1){
			if(player2.HPbuffer==0){
				player2.anyAction =0;
			}
			cleanPlayer(&player2);
			drawPlayer(player2.lastMove, &player2,0);
		}
	}
	else{
		drawPlayerHurt(&player2);
		player2.anyAction =1;
	}
	//part 4A: time check
	if(currentSec <=0){
		return scoreCompare(&player1, &player2);
	}
	//part 4B: HP check
	return HPcheck(&player1, &player2);

}


void initStage(){

	draw_driver(0,0,639,479,0,0,0);
	stage = (cell**)malloc(20*sizeof(cell*));
	for(int i=0; i<20; i++){
		stage[i] = (cell*)malloc(15*sizeof(cell));
	}
	//generate a random stage
	//randomly generate walls for each 4*3 block
	srand(clock());
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			int arr[12]={0,1,2,3,10,11,12,13,20,21,22,23};
			shuffle(arr, 12);
			for(int count = 0; count<12; count++){
				int randCell = arr[count];
				int offsetY = randCell/10;
				int offsetX = randCell - offsetY*10;
				int X = i*4+offsetX;
				int Y = j*3+offsetY;
				if(count < 3){
					stage[X][Y].type=0;
				}
				else if (count<6){
					if(!((X<2&&Y<2)||(X>=18&&Y>=13))){
						drawSolidWall(X,Y,stage);
						delay(20);
					}
				}
				else{
					if(!((X<2&&Y<2)||(X>=18&&Y>=13))){
						drawSoftWall(X,Y,stage);
						delay(20);
					}
				}
			}
		}
	}
	delay(1);
	Audio_Select('1');
	//leave some space for player
	stage[0][0].type=0;
	cleanCell(0,0);
	stage[1][0].type=0;
	cleanCell(1,0);
	stage[0][1].type=0;
	cleanCell(0,1);
	stage[1][1].type=0;
	cleanCell(1,1);
	stage[19][14].type=0;
	cleanCell(19,14);
	stage[19][13].type=0;
	cleanCell(19,13);
	stage[18][14].type=0;
	cleanCell(18,14);
	stage[18][13].type=0;
	cleanCell(18,13);

	beginFlag=1;
	bgmFlag=1;
	coinHead = NULL;
	coinTail = NULL;


}

void initPlayer(){

	player1.index =0;
	player1.x = 3;
	player1.y = 3;
	player1.HP = 3;
    player1.HPbuffer = 0;
    player1.score = 0;
    player1.step = 1;
    player1.bombList = NULL;
    player1.bombCounter = 3;
    player1.bombTimingCounter = 0;
	player1.lastMove = 1;
	player1.moveCounter = 1;
	player1.anyAction = 1;

	player2.index =1;
	player2.x = 606;
	player2.y = 447;
	player2.HP = 3;
    player2.HPbuffer = 0;
    player2.score = 0;
    player2.step = 1;
    player2.bombList = NULL;
    player2.bombCounter = 3;
    player2.bombTimingCounter = 0;
	player2.lastMove = 0;
	player2.moveCounter = 1;
	player2.anyAction = 1;


	player1.bombList= malloc(3*sizeof(bomb));
	player2.bombList= malloc(3*sizeof(bomb));
    for(unsigned short int i =0 ; i<3; i++){
    	player1.bombList[i].active = 0;
    	player2.bombList[i].active = 0;
    }
    player1.bombCounter = 3;
    player2.bombCounter = 3;
}


//dir == 0 => move to up    increment y
//dir == 1 => move to down  decrement y
//dir == 2 => move to left  increment x
//dir == 3 => move to right decrement x
void move(player* playerA, player* playerB, unsigned short int dir){
	playerA->lastMove = dir;
	cleanPlayer(playerA);

	if(dir==0){
		if(playerA->y>=3){
			if(canMove(playerA->x, playerA->y-playerA->step, playerB)){playerA->y-=playerA->step;}
		}
	}
	//move down
	else if(dir==1){
		if(playerA->y<=451){
			if(canMove(playerA->x, playerA->y+playerA->step, playerB)){playerA->y+=playerA->step;}
		}
	}
	//move left
	else if(dir==2){
		if(playerA->x>=3){
			if(canMove(playerA->x-playerA->step, playerA->y, playerB)){playerA->x-=playerA->step;}
		}
	}
	//move right
	else if(dir==3){
		if(playerA->x<=611){
			if(canMove(playerA->x+playerA->step, playerA->y, playerB)){playerA->x+=playerA->step;}
		}
	}
    playerA->anyAction =1;
    drawPlayer(dir, playerA,1);
}


int canMove(unsigned short int x, unsigned short int y, player *playerB){
	short int Ax0 = (short int)x;
	short int Ay0 = (short int)y;
	short int Ax1 = (short int)x+25;
	short int Ay1 = (short int)y+25;

	short int Bx0 = (short int)playerB->x;
	short int By0 = (short int)playerB->y;

    short int delta_x = Ax0>Bx0 ? Ax0-Bx0 : Bx0-Ax0;
    short int delta_y = Ay0>By0 ? Ay0-By0 : By0-Ay0;
    if(delta_x <= 26 && delta_y <= 26){return 0;}
	return (
			  ((stage[Ax0/32][Ay0/32].type==0)||(stage[Ax0/32][Ay0/32].type==6)||onFire(Ax0,Ay0))
			&&((stage[Ax0/32][Ay1/32].type==0)||(stage[Ax0/32][Ay1/32].type==6)||onFire(Ax0,Ay1))
			&&((stage[Ax1/32][Ay0/32].type==0)||(stage[Ax1/32][Ay0/32].type==6)||onFire(Ax1,Ay0))
			&&((stage[Ax1/32][Ay1/32].type==0)||(stage[Ax1/32][Ay1/32].type==6)||onFire(Ax1,Ay1))
			);
}

int onFire(unsigned short int x, unsigned short int y){
	return stage[x/32][y/32].type==40 || stage[x/32][y/32].type==41 || stage[x/32][y/32].type==42
	   ||stage[x/32][y/32].type==50 || stage[x/32][y/32].type==51 || stage[x/32][y/32].type==52;
}

int catchFire(player* playerA){
	unsigned short int x0 = playerA->x;
	unsigned short int y0 = playerA->y;
    unsigned short int x1 = x0+25;
    unsigned short int y1 = y0+25;
    return (onFire(x0,y0)||onFire(x0,y1)||onFire(x1,y0)||onFire(x1,y1));
}


int placeBomb(player* playerA, player* playerB){
	if(playerA->bombCounter == 0 || playerA->bombTimingCounter != 0){return 0;}
	unsigned short int AX =   (playerA->x+12)/32;
	unsigned short int AY =   (playerA->y+12)/32;
	unsigned short int AX0 =  (playerA->x)/32;
	unsigned short int AY0 =  (playerA->y)/32;
	unsigned short int AX1 =  (playerA->x+25)/32;
	unsigned short int AY1 =  (playerA->y+25)/32;

	unsigned short int Bx0 =  playerB->x;
	unsigned short int By0 =  playerB->y;
    unsigned short int X, Y;
	unsigned short int lastMove = playerA->lastMove;
	switch(lastMove){
		case 0:
			if(AY-1<0){return 0;}
			if(stage[AX][AY-1].type==0){
				X = AX;
				Y = AY-1;
				if(AY0==Y){
					playerA->y = (Y+1)*32;
					cleanCell(X,Y);
					cleanCell(X,Y+1);
					drawPlayer(playerA->lastMove, playerA,0);
				}
				break;
			}
			else{return 0;}
		case 1:
			if(AY+1>14){return 0;}
			if(stage[AX][AY+1].type==0){
				X = AX;
				Y = AY+1;
				if(AY1==Y){
					playerA->y = (Y-1)*32;
					cleanCell(X,Y);
					cleanCell(X,Y-1);
					drawPlayer(playerA->lastMove, playerA,0);
				}
				break;
			}
			else{return 0;}
		case 2:
			if(AX-1<0){return 0;}
			if(stage[AX-1][AY].type==0){
				X = AX-1;
				Y = AY;
				if(AX0==X){
					playerA->x = (X+1)*32;
					cleanCell(X,Y);
					cleanCell(X+1,Y);
					drawPlayer(playerA->lastMove, playerA,0);
				}
				break;
			}
			else{return 0;}
		case 3:
			if(AX+1>19){return 0;}
			if(stage[AX+1][AY].type==0){
				X = AX+1;
				Y = AY;
				if(AX1==X){
					playerA->x = (X-1)*32;
					cleanCell(X,Y);
					cleanCell(X-1,Y);
					drawPlayer(playerA->lastMove, playerA,0);
				}
				break;
			}
			else{return 0;}
		default:
			return 0;
	}

	unsigned short int x = X*32;
	unsigned short int y = Y*32;
    unsigned short int delta_x = x>Bx0 ? x-Bx0 : Bx0-x;
    unsigned short int delta_y = y>By0 ? y-By0 : By0-y;
    if(delta_x <= 32 && delta_y <= 32){return 0;}

    //conditional check finish at this line
	playerA->bombCounter --;
	playerA->bombTimingCounter = 50;
	for(unsigned short int i=0; i<3; i++){
		if(playerA->bombList[i].active==0){
			playerA->bombList[i].active=1;
			playerA->bombList[i].counter=0;
			playerA->bombList[i].X=X;
			playerA->bombList[i].Y=Y;
			stage[X][Y].type=3;
			return 1;
		}
	}
	return 0;
}


void UpdateBomb(player* playerA, player* playerB){
	if(playerA->bombCounter<3){
		for(unsigned short int i =0; i<3; i++){
			bomb b = (playerA->bombList)[i];
			if(b.active == 0){continue;}
			unsigned short int index = 40+i;
			if(b.counter == 841){
				drawBombAndExplosion(index, 999, b.X, b.Y, stage, &coinHead, &coinTail);
				(playerA->bombList)[i].counter = 0;
				(playerA->bombList)[i].active = 0;
				playerA-> bombCounter ++;
				continue;
			}
			else if(b.counter%10==0){
				drawBombAndExplosion(index, b.counter/10, b.X, b.Y, stage, &coinHead, &coinTail);
				if(b.counter == 350){(playerA->bombList)[i].counter +=9;}
			}
			(playerA->bombList)[i].counter++;
		}
	}
	if(playerB->bombCounter<3){
		for(unsigned short int i =0; i<3; i++){
			bomb b = (playerB->bombList)[i];
			if(b.active == 0){continue;}
			unsigned short int index = 50+i;
			if(b.counter == 841){
				drawBombAndExplosion(index,999, b.X, b.Y, stage, &coinHead, &coinTail);
				(playerB->bombList)[i].counter = 0;
				(playerB->bombList)[i].active = 0;
				playerB-> bombCounter ++;
				continue;
			}
			else if(b.counter%10==0){
				drawBombAndExplosion(index, b.counter/10, b.X, b.Y, stage, &coinHead, &coinTail);
				if(b.counter == 350){(playerB->bombList)[i].counter+=9;}
			}
			(playerB->bombList)[i].counter++;

		}
	}
}

//return 0 =>nothing happens
//return 1 =>player 1 wins
//return 2 =>player 2 wins
//return 3 =>draw
int HPcheck(player* playerA, player* playerB){
	unsigned short int playerADies = 0;
	unsigned short int playerBDies = 0;
	if(playerA->HPbuffer != 0){
		playerA->HPbuffer--;
	}
	else{
		if(catchFire(playerA)){
			playerA->HP--;
			playerA->HPbuffer = 350;
			printf("playerA's HP is %d \n", playerA->HP);
            //drawPlayerHurt(playerA);
			if(playerA->HP == 0){playerADies=1;}
		}
	}
	if(playerB->HPbuffer != 0){
		playerB->HPbuffer--;
	}
	else{
		if(catchFire(playerB)){
			playerB->HP--;
			playerB->HPbuffer = 350;
			printf("playerB's HP is %d \n", playerB->HP);
			//drawPlayerHurt(playerB);
			if(playerB->HP == 0){playerBDies=1;}
		}
	}
	displayHP(playerA, playerB);
	if(playerADies==0 && playerBDies==0){return 0;}
	if(playerADies==0 && playerBDies==1){return 1;}
	if(playerADies==1 && playerBDies==0){return 2;}
	if(playerADies==1 && playerBDies==1){return 3;}
    return 0;
}

int scoreCompare(player* playerA, player* playerB){
	printf("Let us compare score!!!\n");
	if(playerA->score > playerB->score){return 1;}
	else if(playerB->score > playerA->score){return 2;}
	return 3;
}

void displayHP(player* playerA, player* playerB){
	if(playerA->HP==0 && playerB->HP==0){
		*LEDs = 0;
	}
	else if(playerA->HP==0 && playerB->HP==1){
		*LEDs = 1;
	}
	else if(playerA->HP==0 && playerB->HP==2){
		*LEDs = 3;
	}
	else if(playerA->HP==0 && playerB->HP==3){
		*LEDs = 7;
	}
	else if(playerA->HP==1 && playerB->HP==0){
		*LEDs = 32;
	}
	else if(playerA->HP==1 && playerB->HP==1){
		*LEDs = 33;
	}
	else if(playerA->HP==1 && playerB->HP==2){
		*LEDs = 35;
	}
	else if(playerA->HP==1 && playerB->HP==3){
		*LEDs = 39;
	}
	else if(playerA->HP==2 && playerB->HP==0){
		*LEDs = 96;
	}
	else if(playerA->HP==2 && playerB->HP==1){
		*LEDs = 97;
	}
	else if(playerA->HP==2 && playerB->HP==2){
		*LEDs = 99;
	}
	else if(playerA->HP==2 && playerB->HP==3){
		*LEDs = 103;
	}
	else if(playerA->HP==3 && playerB->HP==0){
		*LEDs = 224;
	}
	else if(playerA->HP==3 && playerB->HP==1){
		*LEDs =225;
	}
	else if(playerA->HP==3 && playerB->HP==2){
		*LEDs =227;
	}
	else if(playerA->HP==3 && playerB->HP==3){
		*LEDs = 231;
	}

}

