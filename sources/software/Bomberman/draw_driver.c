/*
 * draw.c
 *
 *  Created on: 11-07-2019
 *      Author: Jerry
 */
#include "./header_file/draw_driver.h"


// Hex: 00080 0000 0000 0000	32-bit


unsigned int BI_counter = 0;
volatile unsigned int * BI = (unsigned int *) 0x08001000;


//draw(starting x on sheet, starting y on sheet,
//     ending x on sheet, ending y on sheet
//     starting x on screen, starting y on screen
//     sheet index 0(0004B000), 1(00070800), 2, 3)
//    x and y belongs to [640, 480]
int draw_driver(	unsigned int Sx, unsigned int Sy, unsigned int Ex,
					unsigned int Ey, unsigned int Tx, unsigned int Ty,
					unsigned int Mem_index){

	unsigned int Mem_index1 = Mem_index >> 2;


	unsigned int Hex1 = (Mem_index1 << 30) + (Sx << 20) + (Sy << 10) + (Ex);
	unsigned int Hex0 = (Mem_index << 30) +(Ey << 20) + (Tx << 10) + (Ty);

	//If Blitter Buffer is full, return error
	if(BI[16] == 0xff){
		printf("Buffer Full");
		return -1;
	}

	//If still have space:
	BI[2*BI_counter] = Hex1;
	BI[2*BI_counter + 1] = Hex0;

	BI_counter = (BI_counter + 1) % 8;


	return 0;
}

int draw_driver_init(){
	BI[31] = 0xff;

	//Detect Data Initialization
	for (int i = 0; i <8;i++){
		if (BI[2*i] != 0x0){
			printf("Data register %i cannot be initialized\n", 2*i);
			return -1;
		}
		else if(BI[2*i+1] != 0x0){
			printf("Data register %i cannot be initialized\n", 2*i+1);
			return -1;
		}
	}

	printf("Data register initialization successful\n");

	//Detect Status Initialization
	if (BI[16] != 0x0){
		printf("Status register cannot be initialized, the content is %02x\n", BI[16]);
		return -1;
	}
	else
		printf("Status register initialization successful!\n");

	return 0;

}


int draw_driver_speed(){
	//BI = 0x1111 => full
	return BI[16];
}




//very good function
void delay(int milli_seconds)
{
    // Converting time into milli_seconds
//    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds);
}
