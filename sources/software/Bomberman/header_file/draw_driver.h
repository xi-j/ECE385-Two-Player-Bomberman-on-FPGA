/*
 * draw.h
 *
 *  Created on: 2019��11��7��
 *      Author: Jerry-H
 */

#pragma once

#include <time.h>
#include <stdio.h>



int draw_driver(unsigned int Sx, unsigned int Sy, unsigned int Ex, unsigned int Ey, unsigned int Tx, unsigned int Ty, unsigned int Mem_index);
int draw_driver_init();
int draw_driver_speed();
void delay(int milli_seconds);


