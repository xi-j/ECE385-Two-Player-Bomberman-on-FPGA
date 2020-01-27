#pragma once

typedef struct{
	unsigned short int active;
	unsigned short int X;
	unsigned short int Y;
	unsigned short int counter;
}bomb;

//this is the player struct
typedef struct{
	//X and Y are relative index to cells
	//NOT absolute pixel index
	unsigned short int index; //player 1=>0, player2=>1
	unsigned short int x;
	unsigned short int y;
    unsigned short int HP;
    unsigned short int HPbuffer;
    unsigned int score;
    unsigned short int step;
    bomb* bombList;
    short int bombCounter;
    short int bombTimingCounter;
	unsigned short int lastMove;
	unsigned short int moveCounter;
	unsigned short int anyAction;
}player;

typedef struct coin{
	unsigned int counter;
}coin;

//this is the cell struct
//each cell corresponds to 32*32 pixels on VGA screen
//so there are in total 20*15 cells
typedef struct{
    //type == 0 => nothing
	//type == 1 => solid wall
	//type == 2 => soft wall
	//type ~[200.300) =>firing walls
	//type == 3 => bomb
	//type == 40  => player1's first explosion
	//type == 41  => player1's second explosion
	//type == 42  => player1's third explosion
	//type == 50  => player2's first explosion
	//type == 51  => player2's second explosion
	//type == 52  => player2's third explosion
    //type == 6   => coins
	//more to go...
    unsigned short int type;
    coin* ptr;
}cell;

typedef struct cellXY{
	unsigned short int X;
	unsigned short int Y;
	struct cellXY *prev;
	struct cellXY *next;
}cellXY;

