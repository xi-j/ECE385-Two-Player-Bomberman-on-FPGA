#include "./header_file/readKey.h"

int W_en(unsigned int* keycode)
{
	if(keycode[0]==26){return 1;}
	if(keycode[1]==26){return 1;}
	if(keycode[2]==26){return 1;}
	if(keycode[3]==26){return 1;}
	if(keycode[4]==26){return 1;}
	if(keycode[5]==26){return 1;}
	return 0;
}

int S_en(unsigned int* keycode)
{
	if(keycode[0]==22){return 1;}
	if(keycode[1]==22){return 1;}
	if(keycode[2]==22){return 1;}
	if(keycode[3]==22){return 1;}
	if(keycode[4]==22){return 1;}
	if(keycode[5]==22){return 1;}
	return 0;
}

int A_en(unsigned int* keycode)
{
	if(keycode[0]==4){return 1;}
	if(keycode[1]==4){return 1;}
	if(keycode[2]==4){return 1;}
	if(keycode[3]==4){return 1;}
	if(keycode[4]==4){return 1;}
	if(keycode[5]==4){return 1;}
	return 0;
}

int D_en(unsigned int* keycode)
{
	if(keycode[0]==7){return 1;}
	if(keycode[1]==7){return 1;}
	if(keycode[2]==7){return 1;}
	if(keycode[3]==7){return 1;}
	if(keycode[4]==7){return 1;}
	if(keycode[5]==7){return 1;}
	return 0;
}

int UP_en(unsigned int* keycode)
{
	if(keycode[0]==82){return 1;}
	if(keycode[1]==82){return 1;}
	if(keycode[2]==82){return 1;}
	if(keycode[3]==82){return 1;}
	if(keycode[4]==82){return 1;}
	if(keycode[5]==82){return 1;}
	return 0;
}

int DOWN_en(unsigned int* keycode)
{
	if(keycode[0]==81){return 1;}
	if(keycode[1]==81){return 1;}
	if(keycode[2]==81){return 1;}
	if(keycode[3]==81){return 1;}
	if(keycode[4]==81){return 1;}
	if(keycode[5]==81){return 1;}
	return 0;
}

int LEFT_en(unsigned int* keycode)
{
	if(keycode[0]==80){return 1;}
	if(keycode[1]==80){return 1;}
	if(keycode[2]==80){return 1;}
	if(keycode[3]==80){return 1;}
	if(keycode[4]==80){return 1;}
	if(keycode[5]==80){return 1;}
	return 0;
}

int RIGHT_en(unsigned int* keycode)
{
	if(keycode[0]==79){return 1;}
	if(keycode[1]==79){return 1;}
	if(keycode[2]==79){return 1;}
	if(keycode[3]==79){return 1;}
	if(keycode[4]==79){return 1;}
	if(keycode[5]==79){return 1;}
	return 0;
}

int SPACE_en(unsigned int* keycode)
{
	if(keycode[0]==44){return 1;}
	if(keycode[1]==44){return 1;}
	if(keycode[2]==44){return 1;}
	if(keycode[3]==44){return 1;}
	if(keycode[4]==44){return 1;}
	if(keycode[5]==44){return 1;}
	return 0;
}

int ENTER_en(unsigned int* keycode)
{
	if(keycode[0]==40){return 1;}
	if(keycode[1]==40){return 1;}
	if(keycode[2]==40){return 1;}
	if(keycode[3]==40){return 1;}
	if(keycode[4]==40){return 1;}
	if(keycode[5]==40){return 1;}
	return 0;
}

int PLUS_en(unsigned int* keycode)
{
	if(keycode[0]==46){return 1;}
	if(keycode[1]==46){return 1;}
	if(keycode[2]==46){return 1;}
	if(keycode[3]==46){return 1;}
	if(keycode[4]==46){return 1;}
	if(keycode[5]==46){return 1;}
	return 0;

}

int MINOR_en(unsigned int* keycode)
{
	if(keycode[0]==45){return 1;}
	if(keycode[1]==45){return 1;}
	if(keycode[2]==45){return 1;}
	if(keycode[3]==45){return 1;}
	if(keycode[4]==45){return 1;}
	if(keycode[5]==45){return 1;}
	return 0;

}

int ZERO_en(unsigned int* keycode){
	if(keycode[0]==39){return 1;}
	if(keycode[1]==39){return 1;}
	if(keycode[2]==39){return 1;}
	if(keycode[3]==39){return 1;}
	if(keycode[4]==39){return 1;}
	if(keycode[5]==39){return 1;}
	return 0;

}

int NINE_en(unsigned int* keycode){
	if(keycode[0]==38){return 1;}
	if(keycode[1]==38){return 1;}
	if(keycode[2]==38){return 1;}
	if(keycode[3]==38){return 1;}
	if(keycode[4]==38){return 1;}
	if(keycode[5]==38){return 1;}
	return 0;
}
