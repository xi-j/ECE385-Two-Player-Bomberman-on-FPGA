//------------------------------------------------------------------------------
// Engineer:		 Jerry Wang & Xilin Jiang
//
// Create Date:    
// Design Name:    Bomberman_final_project--avalon_blitter_interface 
// Module Name:    avalon_blitter_interface
//
// Comments:
//    Revised 11-07-2019
//------------------------------------------------------------------------------
////
module Bomberman_top (
		input  logic        CLOCK_50,    
		input  logic [1:0]  KEY,
		
		output logic [7:0]  LEDG,	
		output logic [1:0]  LEDR,
		        
		//SDRAM For NIOS-II Program
		output logic [12:0] DRAM_ADDR,
		output logic [1:0]  DRAM_BA,
		output logic        DRAM_CAS_N,
		output logic        DRAM_CKE,
		output logic        DRAM_CS_N,
		inout  logic [31:0] DRAM_DQ,
		output logic [3:0]  DRAM_DQM,
		output logic        DRAM_RAS_N,
		output logic        DRAM_WE_N,
		output logic        DRAM_CLK,  
		
		//SRAM Sprite Sheet access
		output logic 		  SRAM_CE_N,    //chip enable: active low
								  SRAM_UB_N,    //upper byte enable: active low
								  SRAM_LB_N,    //lower byte enable: active low
								  SRAM_OE_N,    //read enable; active low
								  SRAM_WE_N,    //write enable: active low
		output logic [19:0] SRAM_ADDR, 	
		inout  wire  [15:0] SRAM_DQ, 
		
		//Flash Memory Audio Data
		output logic [22:0] FL_ADDR,
		inout	 wire	[7:0]	  FL_DQ,
		output logic 		  FL_WE_N, FL_OE_N, FL_CE_N, FL_RST_N,
		output logic 		  FL_WP_N,
		input logic 		  FL_RY,	
	
		//HEX
		output logic [6:0]  HEX0,
		output logic [6:0]  HEX1,
		output logic [6:0]  HEX2,
		output logic [6:0]  HEX3,
		output logic [6:0]  HEX4,
		output logic [6:0]  HEX5,
		output logic [6:0]  HEX6,
		output logic [6:0]  HEX7,
		
		//VGA
		output logic [7:0]  VGA_R,        //VGA Red
                          VGA_G,        //VGA Green
                          VGA_B,        //VGA Blue
      output logic        VGA_CLK,      //VGA Clock
                          VGA_SYNC_N,   //VGA Sync signal
                          VGA_BLANK_N,  //VGA Blank signal
                          VGA_VS,       //VGA virtical sync signal
                          VGA_HS,       //VGA horizontal sync signal
					  
	   //CY7C67200 USB
	   inout  wire  [15:0] OTG_DATA,     //CY7C67200 Data bus 16 Bits
	   output logic [1:0]  OTG_ADDR,     //CY7C67200 Address 2 Bits
	   output logic        OTG_CS_N,     //CY7C67200 Chip Select
								  OTG_RD_N,     //CY7C67200 Write
	 	 						  OTG_WR_N,     //CY7C67200 Read
	 	 						  OTG_RST_N,    //CY7C67200 Reset
	   input  logic        OTG_INT,      //CY7C67200 Interrupt
	
		//Audio
		input 	logic 	  AUD_BCLK,		 //Bitstream Clock
		input	 	logic 	  AUD_ADCDAT,   //A/D input (Not used
		output 	logic 	  AUD_DACDAT,   //D/A output 
		input 	logic 	  AUD_DACLRCK, AUD_ADCLRCK,	//A/D a
		output 	logic 	  I2C_SDAT, 
		output 	logic 	  I2C_SCLK, 			//I2C communication
		output 	logic 	  AUD_XCK
	
		                   
);


	 logic [31:0] BI_TEST,Virtual2;
	 logic Reset_h, Clk;
    logic [7:0] keycode;
    
    assign Clk = CLOCK_50;
    always_ff @ (posedge Clk) begin
        Reset_h <= ~(KEY[0]);        // The push buttons are active low
    end
    
    logic [1:0] hpi_addr;
    logic [15:0] hpi_data_in, hpi_data_out;
    logic hpi_r, hpi_w, hpi_cs, hpi_reset;
    
    // Interface between NIOS II and EZ-OTG chip
    hpi_io_intf hpi_io_inst(
				 .Clk(Clk),
				 .Reset(Reset_h),
				 // signals connected to NIOS II
				 .from_sw_address(hpi_addr),
				 .from_sw_data_in(hpi_data_in),
				 .from_sw_data_out(hpi_data_out),
				 .from_sw_r(hpi_r),
				 .from_sw_w(hpi_w),
				 .from_sw_cs(hpi_cs),
				 .from_sw_reset(hpi_reset),
				 // signals connected to EZ-OTG chip
				 .OTG_DATA(OTG_DATA),    
				 .OTG_ADDR(OTG_ADDR),    
				 .OTG_RD_N(OTG_RD_N),    
				 .OTG_WR_N(OTG_WR_N),    
				 .OTG_CS_N(OTG_CS_N),
				 .OTG_RST_N(OTG_RST_N)
     );



//Blitter and Blitter interface connection
	logic [63:0]	Data_to_Blitter;
	logic 			Blitter_Finish_Flip;
	logic 			Status_REG;
	
	//VGA Portion		
	logic [17:0]	VGA_R_ADDR;		
	logic [31:0]	VGA_R_DQ;
	logic [9:0]		DrawX,DrawY;
	
	
	logic[7:0] fakeLEDG; 
	// Blitter Interface
	Bomberman Bomberman_0 (
		.clk_clk(CLOCK_50),								// Clock input
		.reset_reset_n(KEY[0]),							// Reset key
		.export_data_new_signal({LEDR[0],fakeLEDG}),	// Exported data
		.export_data_new_signal_1(Virtual2),
		.export_data_new_signal_2(Data_to_Blitter),
		.export_data_new_signal_3(Blitter_Finish_Flip), 
		.export_data_new_signal_4(Status_REG),
		.led_wire_export(LEDG),
		.sdram_wire_addr(DRAM_ADDR),					// sdram_wire.addr
		.sdram_wire_ba(DRAM_BA),						// sdram_wire.ba
		.sdram_wire_cas_n(DRAM_CAS_N),				// sdram_wire.cas_n
		.sdram_wire_cke(DRAM_CKE),						// sdram_wire.cke
		.sdram_wire_cs_n(DRAM_CS_N),					// sdram.cs_n
		.sdram_wire_dq(DRAM_DQ),						// sdram.dq
		.sdram_wire_dqm(DRAM_DQM),						// sdram.dqm
		.sdram_wire_ras_n(DRAM_RAS_N),				// sdram.ras_n
		.sdram_wire_we_n(DRAM_WE_N),					// sdram.we_n
		.sdram_pll_clk(DRAM_CLK),						// Clock out to SDRAM 
		.otg_hpi_address_export(hpi_addr),
		.otg_hpi_data_in_port(hpi_data_in),
		.otg_hpi_data_out_port(hpi_data_out),
		.otg_hpi_cs_export(hpi_cs),
		.otg_hpi_r_export(hpi_r),
		.otg_hpi_w_export(hpi_w),
		.otg_hpi_reset_export(hpi_reset),
		.audio_back_vol_export(Audio_Back_Vol),
		.audio_bomb_vol_export(Audio_Bomb_Vol),
		.audio_bomb_active_export(Audio_Bomb_Active),
		.audio_select_export(Audio_Select),
		
		
		.player1score1_wire_export(player1Score1), 
		.player1score0_wire_export(player1Score0), 
		.player2score1_wire_export(player2Score1), 
		.player2score0_wire_export(player2Score0), 

	   .timescreen2_wire_export(timeScreen2), 
	   .timescreen1_wire_export(timeScreen1), 
      .timescreen0_wire_export(timeScreen0),

		.boot_up_export(~KEY[1])
	); 
		
////////////////////////////////////////////////////////////////////Blitter Part////////////////////////////////////////////////////////////////////	
		
	//Blitter Core
	Blitter_v2 Blitter_0 (
		.SRAM_CE_N(SRAM_CE_N),	.SRAM_UB_N(SRAM_UB_N), .SRAM_LB_N(SRAM_LB_N),
		.SRAM_WE_N(SRAM_WE_N),	.SRAM_OE_N(SRAM_OE_N),
		.SRAM_ADDR(SRAM_ADDR),	.SRAM_DQ(SRAM_DQ),
		.Coordinate(Data_to_Blitter), .Copy_Finish(Blitter_Finish_Flip),
		.Clk(CLOCK_100), .Reset(~KEY[0]), .Start(Status_REG),
		.VGA_R_ADDR(VGA_R_ADDR), .VGA_R_DQ(VGA_R_DQ), .VGA_CLK(VGA_CLK)
		);

//////////////////////////////////////////////////////////////////////VGA_Part//////////////////////////////////////////////////////////////////////
	//VGA Pulling data from frame buffer	
	VGA_Pull_Out_v2	VGA_Pull_Out0 (
		.VGA_Clk(VGA_CLK), .Reset(~KEY[0]),
		.VGA_R_ADDR(VGA_R_ADDR), .VGA_R_DQ(VGA_R_DQ),
		.DrawX(DrawX), .DrawY(DrawY),
		.VGA_R(VGA_R), .VGA_B(VGA_B), .VGA_G(VGA_G)
		);
		
	
	VGA_controller	VGA_controller0 (
		.Reset(~KEY[0]), 
		.VGA_HS(VGA_HS), .VGA_VS(VGA_VS), .VGA_CLK(VGA_CLK),
		.VGA_BLANK_N(VGA_BLANK_N), .VGA_SYNC_N(VGA_SYNC_N),
		.DrawX(DrawX), .DrawY(DrawY)
		);

////////////////////////////////////////////////////////////////////PLL
	
	logic CLOCK_100, CLOCK_25,CLOCK_12_288;
	assign VGA_CLK = CLOCK_25;
	logic CLOCK_200;
	
	pll_global 	pll0 (.inclk0(CLOCK_50), .c0(CLOCK_100), .c1(CLOCK_25), .c2(CLOCK_12_288));
//	test			pll1 (.inclk0(CLOCK_50), .c0(CLOCK_200));
////	Audio_clk	A_clk(.inclk0(CLOCK_50), .c0(CLOCK_12_288));
	
////////////////////////////////////////////////////////////////////Audio Part///////////////////////////////////////////////////////////////////////
	
	//To Driver
	logic [15:0]	LDATA,RDATA;
	logic 			Audio_INIT, Audio_INIT_F;
	logic 			data_over;
	
	logic [2:0]		Audio_Back_Vol, Audio_Bomb_Vol;
	logic 			Audio_Bomb_Active;
	
	logic [2:0]		Audio_Select;
	
	assign AUD_XCK = CLOCK_12_288;

	//Audio Driver, only connect the necessary DAC part
	audio_interface audio_interface0(	.LDATA(LDATA), .RDATA(RDATA),
									.clk(CLOCK_50), .Reset(~KEY[0]), .INIT(Audio_INIT),
									.INIT_FINISH(Audio_INIT_F),
									.adc_full(1'bx),
									.data_over(data_over),
									.AUD_MCLK(1'hx),
									.AUD_BCLK(AUD_BCLK),
									.AUD_ADCDAT(AUD_ADCDAT),
									.AUD_DACDAT(AUD_DACDAT),
									.AUD_DACLRCK(AUD_DACLRCK), .AUD_ADCLRCK(AUD_ADCLRCK),
									.I2C_SDAT(I2C_SDAT), .I2C_SCLK(I2C_SCLK),
									.ADCDATA(32'hx));		
							
	Audio_Controller	AU0 (	.Clk(CLOCK_50), .Reset(~KEY[0]),
									.FL_ADDR(FL_ADDR), .FL_DQ(FL_DQ), .FL_WE_N(FL_WE_N), .FL_OE_N(FL_OE_N),
									.FL_CE_N(FL_CE_N), .FL_RST_N(FL_RST_N), .FL_WP_N(FL_WP_N), .FL_RY(FL_RY),
									.LDATA(LDATA), .RDATA(RDATA), .data_over(data_over),
									.INIT(Audio_INIT), .INIT_F(Audio_INIT_F),
//									.DEBUG(BI_TEST[4:0]), .DEBUG1(BI_TEST[31:24]), 
									.Back_Vol(Audio_Back_Vol), .Bomb_Active(Audio_Bomb_Active), .Bomb_Vol(Audio_Bomb_Vol),
									.Audio_Select(Audio_Select));
	
	
////////////////////////////////////////////////////////////////////LED and HEX//////////////////////////////////////////////////////////////////////
	

//Debug
	
	//assign BI_TEST = FL_ADDR;
	logic[4:0] player1Score1, player1Score0, player2Score1, player2Score0, timeScreen2, timeScreen1, timeScreen0;
	
	
	decdriver decdrv0 (
		.In(timeScreen0),
		.Out(HEX0)
	);
	decdriver decdrv1 (
		.In(timeScreen1),
		.Out(HEX1)
	);
	decdriver decdrv2 (
		.In(timeScreen2),
		.Out(HEX2)
	);
	decdriver decdrv3 (
		.In(4'b0),
		.Out(HEX3)
	);
	decdriver decdrv4 (
		.In(player2Score0),
		.Out(HEX4)
	);
	decdriver decdrv5 (
		.In(player2Score1),
		.Out(HEX5)
	);
	decdriver decdrv6 (
		.In(player1Score0),
		.Out(HEX6)
	);
	decdriver decdrv7 (
		.In(player1Score1),
		.Out(HEX7)
	);

	
	

endmodule

