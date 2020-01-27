#include "draw_driver.h"
#include "USB_Keyboard_Driver.h"
#include "audio_driver.h"
#include "LEDandHEX.h"

#include "drawing.h"
#include "readKey.h"
#include <time.h>



void initOP();

int op(unsigned int keycode[],unsigned int counter);
