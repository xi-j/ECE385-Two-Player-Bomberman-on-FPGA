#include "./header_file/LEDandHEX.h"


void displayScore(player* playerA, player* playerB){
	if(playerA->score<=99){
		unsigned int score0 = playerA->score%10;
		unsigned int score1 = playerA->score/10;
		*player1Score1 = score1;
		*player1Score0 = score0;
	}
	if(playerB->score<=99){
		unsigned int score0 = playerB->score%10;
		unsigned int score1 = playerB->score/10;
		*player2Score1 = score1;
		*player2Score0 = score0;
	}

}

void displayTime(unsigned int sec){
	if(sec>180){sec = 180;}
	unsigned int min = sec/60;
	unsigned int sec_offset = sec%60;
	unsigned int sec_1 =sec_offset/10;
	unsigned int sec_0 =sec_offset%10;
	*timeScreen2 = min;
	*timeScreen1 = sec_1;
	*timeScreen0 = sec_0;
}
