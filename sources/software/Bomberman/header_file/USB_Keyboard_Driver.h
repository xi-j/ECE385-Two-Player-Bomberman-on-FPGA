#include "../USB_Keyboard_Driver_Sup/cy7c67200.h"
#include "../USB_Keyboard_Driver_Sup/io_handler.h"
#include "../USB_Keyboard_Driver_Sup/lcp_cmd.h"
#include "../USB_Keyboard_Driver_Sup/lcp_data.h"
#include "../USB_Keyboard_Driver_Sup/usb.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>

#include "system.h"
#include "alt_types.h"
#include <unistd.h>  // usleep
//#include "sys/alt_irq.h"



void Keyboard_INIT();

int FetchKey(unsigned int keycode[]);

