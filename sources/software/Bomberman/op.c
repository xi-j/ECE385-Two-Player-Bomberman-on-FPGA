#include "./header_file/op.h"


	static int vol = 2;
	static int B_vol = 3;
	static int vol_counter =0;
	static int B_vol_counter =0;

void initOP(){
	*player1Score1 = 0;
	*player1Score0 = 0;
	*player2Score1 = 0;
	*player2Score0 = 0;
	*timeScreen2 = 3;
	*timeScreen1 = 0;
	*timeScreen0 = 0;
	draw_driver(0,0,639,479,0,0,2);
	Audio_Select('o');
	changeBackVolume(2);

}

int op(unsigned int keycode[],unsigned int counter){
	if(vol_counter!=0){vol_counter--;}
	if(B_vol_counter!=0){B_vol_counter--;}

	if(PLUS_en(keycode)&&!vol_counter){
		vol = (vol == 7) ? 7:vol + 1;
		changeBackVolume(vol);
		vol_counter = 200;
	}
	if(MINOR_en (keycode)&&!vol_counter){
		vol = (vol == 0) ? 0:vol - 1;
		changeBackVolume(vol);
		vol_counter = 200;
	}
	if(NINE_en(keycode)&&!B_vol_counter){
		B_vol = (B_vol == 7) ? 7:B_vol + 1;
		changeBombVolume(B_vol);
		Bomb();
		B_vol_counter = 200;

	}
	if(ZERO_en(keycode)&&!B_vol_counter){
		B_vol = (B_vol == 0) ? 0:B_vol - 1;
		changeBombVolume(B_vol);
		Bomb();
		B_vol_counter = 200;
	}

	if(counter%400==0){
		draw_driver(PETS_x0,PETS_y0,PETS_x1,PETS_y1,270,300,1);
	}
	if(counter%400==200){
		draw_driver(270,300,545,324,270,300,2);
	}
	if(ENTER_en(keycode)){return 1;}
	else{return 0;}
}

