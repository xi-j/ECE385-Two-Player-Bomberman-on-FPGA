#include "draw_driver.h"
#include "USB_Keyboard_Driver.h"
#include "audio_driver.h"
#include "LEDandHEX.h"

#include "drawing.h"
#include "readKey.h"
#include <time.h>

//if user presses replay, return 1
//else return 0
void initED(int ending);

int ed(unsigned int keycode[],unsigned int counter);
