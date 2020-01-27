#include "./header_file/USB_Keyboard_Driver.h"
#include "./header_file/draw_driver.h"

alt_u16 usb_ctl_val;
alt_u8 	data_size;
static	alt_u16 ctl_reg;
static 	alt_u16 no_device;
alt_u8 	hot_plug_count;

int keycode_read;


void Keyboard_INIT(){

	IO_init();



		/*while(1)
		{
			IO_write(HPI_MAILBOX,COMM_EXEC_INT);
			printf("[ERROR]:routine mailbox data is %x\n",IO_read(HPI_MAILBOX));
			//UsbWrite(0xc008,0x000f);
			//UsbRead(0xc008);
			usleep(10*10000);
		}*/

		alt_u16 intStat;
		alt_u16 fs_device = 0;
		alt_u16 code;

		ctl_reg = 0;
		no_device = 0;


		printf("USB keyboard setup...\n\n");
		USB_HOT_PLUG:


		draw_driver(414,7,414+160,7+40,12,130,4);
		draw_driver(414,7,414+160,7+40,12+160,130,4);

		for (int i = 20; i < 61; i++){
			draw_driver(414,7,414+30,7+30,i*10,400,4);
			delay(30);
		}



		//----------------------------------------SIE1 initial---------------------------------------------------//
		UsbSoftReset();

		// STEP 1a:
		UsbWrite (HPI_SIE1_MSG_ADR, 0);
		UsbWrite (HOST1_STAT_REG, 0xFFFF);

		/* Set HUSB_pEOT time */
		UsbWrite(HUSB_pEOT, 600); // adjust the according to your USB device speed

		usb_ctl_val = SOFEOP1_TO_CPU_EN | RESUME1_TO_HPI_EN;// | SOFEOP1_TO_HPI_EN;
		UsbWrite(HPI_IRQ_ROUTING_REG, usb_ctl_val);

		intStat = A_CHG_IRQ_EN | SOF_EOP_IRQ_EN ;
		UsbWrite(HOST1_IRQ_EN_REG, intStat);
		// STEP 1a end

		// STEP 1b begin
		UsbWrite(COMM_R0,0x0000);//reset time
		UsbWrite(COMM_R1,0x0000);  //port number
		UsbWrite(COMM_R2,0x0000);  //r1
		UsbWrite(COMM_R3,0x0000);  //r1
		UsbWrite(COMM_R4,0x0000);  //r1
		UsbWrite(COMM_R5,0x0000);  //r1
		UsbWrite(COMM_R6,0x0000);  //r1
		UsbWrite(COMM_R7,0x0000);  //r1
		UsbWrite(COMM_R8,0x0000);  //r1
		UsbWrite(COMM_R9,0x0000);  //r1
		UsbWrite(COMM_R10,0x0000);  //r1
		UsbWrite(COMM_R11,0x0000);  //r1
		UsbWrite(COMM_R12,0x0000);  //r1
		UsbWrite(COMM_R13,0x0000);  //r1
		UsbWrite(COMM_INT_NUM,HUSB_SIE1_INIT_INT); //HUSB_SIE1_INIT_INT
		IO_write(HPI_MAILBOX,COMM_EXEC_INT);

		while (!(IO_read(HPI_STATUS) & 0xFFFF) )  //read sie1 msg register
		{
		}
		while (IO_read(HPI_MAILBOX) != COMM_ACK)
		{
			printf("[ERROR]:routine mailbox data is %x\n",IO_read(HPI_MAILBOX));
			goto USB_HOT_PLUG;
		}
		// STEP 1b end

		printf("STEP 1 Complete");

		//Loading
		for (int i = 20; i < 24; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}


		// STEP 2 begin
		UsbWrite(COMM_INT_NUM,HUSB_RESET_INT); //husb reset
		UsbWrite(COMM_R0,0x003c);//reset time
		UsbWrite(COMM_R1,0x0000);  //port number
		UsbWrite(COMM_R2,0x0000);  //r1
		UsbWrite(COMM_R3,0x0000);  //r1
		UsbWrite(COMM_R4,0x0000);  //r1
		UsbWrite(COMM_R5,0x0000);  //r1
		UsbWrite(COMM_R6,0x0000);  //r1
		UsbWrite(COMM_R7,0x0000);  //r1
		UsbWrite(COMM_R8,0x0000);  //r1
		UsbWrite(COMM_R9,0x0000);  //r1
		UsbWrite(COMM_R10,0x0000);  //r1
		UsbWrite(COMM_R11,0x0000);  //r1
		UsbWrite(COMM_R12,0x0000);  //r1
		UsbWrite(COMM_R13,0x0000);  //r1

		IO_write(HPI_MAILBOX,COMM_EXEC_INT);

		while (IO_read(HPI_MAILBOX) != COMM_ACK)
		{
			printf("[ERROR]:routine mailbox data is %x\n",IO_read(HPI_MAILBOX));
			goto USB_HOT_PLUG;
		}
		// STEP 2 end

		ctl_reg = USB1_CTL_REG;
		no_device = (A_DP_STAT | A_DM_STAT);
		fs_device = A_DP_STAT;
		usb_ctl_val = UsbRead(ctl_reg);

		if (!(usb_ctl_val & no_device))
		{
			for(hot_plug_count = 0 ; hot_plug_count < 5 ; hot_plug_count++)
			{
				usleep(5*1000);
				usb_ctl_val = UsbRead(ctl_reg);
				if(usb_ctl_val & no_device) break;
			}
			if(!(usb_ctl_val & no_device))
			{
				printf("\n[INFO]: no device is present in SIE1!\n");
				printf("[INFO]: please insert a USB keyboard in SIE1!\n");
				draw_driver(11,301,312,321,12,130,4);



				while (!(usb_ctl_val & no_device))
				{
					usb_ctl_val = UsbRead(ctl_reg);
					if(usb_ctl_val & no_device)
						goto USB_HOT_PLUG;

					usleep(2000);
				}
			}
		}
		else
		{
			/* check for low speed or full speed by reading D+ and D- lines */
			if (usb_ctl_val & fs_device)
			{
				printf("[INFO]: full speed device\n");
			}
			else
			{
				printf("[INFO]: low speed device\n");
			}
		}

		for (int i = 24; i < 28; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}



		// STEP 3 begin
		//------------------------------------------------------set address -----------------------------------------------------------------
		UsbSetAddress();

		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			UsbSetAddress();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506); // i
		printf("[ENUM PROCESS]:step 3 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508); // n
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 3 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03) // retries occurred
		{
			usb_ctl_val = UsbGetRetryCnt();

			goto USB_HOT_PLUG;
		}

		printf("------------[ENUM PROCESS]:set address done!---------------\n");
		for (int i = 28; i < 32; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}

		// STEP 4 begin
		//-------------------------------get device descriptor-1 -----------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbGetDeviceDesc1(); 	// Get Device Descriptor -1

		//usleep(10*1000);
		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetDeviceDesc1();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 4 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 4 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}

		printf("---------------[ENUM PROCESS]:get device descriptor-1 done!-----------------\n");


		//--------------------------------get device descriptor-2---------------------------------------------//
		//get device descriptor
		// TASK: Call the appropriate function for this step.
		UsbGetDeviceDesc2(); 	// Get Device Descriptor -2

		//if no message
		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			//resend the get device descriptor
			//get device descriptor
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetDeviceDesc2();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 4 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 4 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}

		printf("------------[ENUM PROCESS]:get device descriptor-2 done!--------------\n");
		for (int i = 32; i < 36; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}


		// STEP 5 begin
		//-----------------------------------get configuration descriptor -1 ----------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbGetConfigDesc1(); 	// Get Configuration Descriptor -1

		//if no message
		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			//resend the get device descriptor
			//get device descriptor

			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetConfigDesc1();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 5 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 5 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}
		printf("------------[ENUM PROCESS]:get configuration descriptor-1 pass------------\n");
		for (int i = 36; i < 40; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}

		// STEP 6 begin
		//-----------------------------------get configuration descriptor-2------------------------------------//
		//get device descriptor
		// TASK: Call the appropriate function for this step.
		UsbGetConfigDesc2(); 	// Get Configuration Descriptor -2

		usleep(100*1000);
		//if no message
		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetConfigDesc2();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 6 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 6 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}


		printf("-----------[ENUM PROCESS]:get configuration descriptor-2 done!------------\n");
		for (int i = 40; i < 44; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}


		// ---------------------------------get device info---------------------------------------------//

		// TASK: Write the address to read from the memory for byte 7 of the interface descriptor to HPI_ADDR.
		IO_write(HPI_ADDR,0x056c);
		code = IO_read(HPI_DATA);
		code = code & 0x003;
		printf("\ncode = %x\n", code);

		if (code == 0x01)
		{
			printf("\n[INFO]:check TD rec data7 \n[INFO]:Keyboard Detected!!!\n\n");
		}
		else
		{
			printf("\n[INFO]:Keyboard Not Detected!!! \n\n");
		}

		// TASK: Write the address to read from the memory for the endpoint descriptor to HPI_ADDR.

		IO_write(HPI_ADDR,0x0576);
		IO_write(HPI_DATA,0x073F);
		IO_write(HPI_DATA,0x8105);
		IO_write(HPI_DATA,0x0003);
		IO_write(HPI_DATA,0x0008);
		IO_write(HPI_DATA,0xAC0A);
		UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0576); //HUSB_SIE1_pCurrentTDPtr

		//data_size = (IO_read(HPI_DATA)>>8)&0x0ff;
		//data_size = 0x08;//(IO_read(HPI_DATA))&0x0ff;
		//UsbPrintMem();
		IO_write(HPI_ADDR,0x057c);
		data_size = (IO_read(HPI_DATA))&0x0ff;
		printf("[ENUM PROCESS]:data packet size is %d\n",data_size);

		for (int i = 44; i < 48; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}




		// STEP 7 begin
		//------------------------------------set configuration -----------------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbSetConfig();		// Set Configuration

		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbSetConfig();		// Set Configuration
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 7 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 7 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}

		printf("------------[ENUM PROCESS]:set configuration done!-------------------\n");

		for (int i = 48; i < 52; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}



		//----------------------------------------------class request out ------------------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbClassRequest();

		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbClassRequest();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 8 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 8 TD Control Byte is %x\n",usb_ctl_val);
		int i = 0;
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
			i++;
			if (i == 10000){
				draw_driver(6,205,327,229,12,130,4);
			}
		}


		printf("------------[ENUM PROCESS]:class request out done!-------------------\n");

		for (int i = 52; i < 56; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}



		// STEP 8 begin
		//----------------------------------get descriptor(class 0x21 = HID) request out --------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbGetHidDesc();

		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetHidDesc();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]:step 8 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]:step 8 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}

		printf("------------[ENUM PROCESS]:get descriptor (class 0x21) done!-------------------\n");


		for (int i = 56; i < 60; i++){
			draw_driver(12,260,28,276,i*10,400,4);
			delay(30);
		}



		// STEP 9 begin
		//-------------------------------get descriptor (class 0x22 = report)-------------------------------------------//
		// TASK: Call the appropriate function for this step.
		UsbGetReportDesc();
		//if no message
		while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
		{
			// TASK: Call the appropriate function again if it wasn't processed successfully.
			UsbGetReportDesc();
			usleep(10*1000);
		}

		UsbWaitTDListDone();

		IO_write(HPI_ADDR,0x0506);
		printf("[ENUM PROCESS]: step 9 TD Status Byte is %x\n",IO_read(HPI_DATA));

		IO_write(HPI_ADDR,0x0508);
		usb_ctl_val = IO_read(HPI_DATA);
		printf("[ENUM PROCESS]: step 9 TD Control Byte is %x\n",usb_ctl_val);
		while (usb_ctl_val != 0x03)
		{
			usb_ctl_val = UsbGetRetryCnt();
		}

		printf("---------------[ENUM PROCESS]:get descriptor (class 0x22) done!----------------\n");
		printf("\n-------------------USB Keyboard INIT Finished--------------------------------\n");


}


int FetchKey(unsigned int keycode[]){

	alt_u8 	toggle = 0;

//	usleep(10000);

			toggle++;
			IO_write(HPI_ADDR,0x0500); //the start address
			//data phase IN-1
			IO_write(HPI_DATA,0x051c); //500

			IO_write(HPI_DATA,0x000f & data_size);//2 data length

			IO_write(HPI_DATA,0x0291);//4 //endpoint 1
			if(toggle%2)
			{
				IO_write(HPI_DATA,0x0001);//6 //data 1
			}
			else
			{
				IO_write(HPI_DATA,0x0041);//6 //data 1
			}
			IO_write(HPI_DATA,0x0013);//8
			IO_write(HPI_DATA,0x0000);//a
			UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr

			while (!(IO_read(HPI_STATUS) & HPI_STATUS_SIE1msg_FLAG) )  //read sie1 msg register
			{
				IO_write(HPI_ADDR,0x0500); //the start address
				//data phase IN-1
				IO_write(HPI_DATA,0x051c); //500

				IO_write(HPI_DATA,0x000f & data_size);//2 data length

				IO_write(HPI_DATA,0x0291);//4 //endpoint 1
				if(toggle%2)
				{
					IO_write(HPI_DATA,0x0001);//6 //data 1
				}
				else
				{
					IO_write(HPI_DATA,0x0041);//6 //data 1
				}
				IO_write(HPI_DATA,0x0013);//8
				IO_write(HPI_DATA,0x0000);//
				UsbWrite(HUSB_SIE1_pCurrentTDPtr,0x0500); //HUSB_SIE1_pCurrentTDPtr
				//usleep(1000);
				usleep(400);
			}//end while

			usb_ctl_val = UsbWaitTDListDone();

			// The first two keycodes are stored in 0x051E. Other keycodes are in
			// subsequent addresses.

			keycode[0] = UsbRead(0x051e) & 0x00ff;
			keycode[1] = UsbRead(0x051e) >> 8;
			keycode[2] = UsbRead(0x051f) & 0x00ff;
			keycode[3] = UsbRead(0x051f) >> 8;
			keycode[4] = UsbRead(0x0520) & 0x00ff;
			keycode[5] = UsbRead(0x0520) >> 8;

			usleep(200);//usleep(5000);
			usb_ctl_val = UsbRead(ctl_reg);

			if(!(usb_ctl_val & no_device))
			{
				//USB hot plug routine
				for(hot_plug_count = 0 ; hot_plug_count < 7 ; hot_plug_count++)
				{
					usleep(5*1000);
					usb_ctl_val = UsbRead(ctl_reg);
					if(usb_ctl_val & no_device) break;
				}
				if(!(usb_ctl_val & no_device))
				{
					printf("\n[INFO]: the keyboard has been removed!!! \n");
					printf("[INFO]: please insert again!!! \n");
					return -1;
				}
			}


		return 0;
}



