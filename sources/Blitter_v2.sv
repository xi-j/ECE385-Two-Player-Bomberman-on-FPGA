//------------------------------------------------------------------------------
// Engineer:		 Jerry Wang & Xilin Jiang
//
// Create Date:    
// Design Name:    Bomberman_final_project--Blitter
// Module Name:    Blitter
//
// Comments:
//    Revised 11-07-2019
//
//	Version:	V.1
//
// 
//	This is the Blitter module that actually doing the 2D memory copying. The 
//	background, and resource images exist in the SRAM, while the frame exist in 
// in the On_chip memory. 
// 
//	SRAM (2048KBytes) have 20 bit address, each address 16-bit data. 
//	Frame buffer is in On_chip (153600x16) Memory(486KByts), start at 0x00000 to 0x257FF (0-153599) [17:0] ADDR
//
//	Resource image   (640 x 480) starts at 0x4B000 to 0x707FF. (307200-460799)		[19:0]	ADDR
// Background image (640 x 480) starts at 0x70800 to 0x95FFF. (460800-614399)
// 
//
//	 This module will also include the singel frame buffer itself.
//	
//------------------------------------------------------------------------------

module Blitter_v2 #(parameter ResWidth = 10'd640, parameter ResHeight = 10'd480, parameter BufferWidth = 10'd640, parameter BufferHeight = 10'd480)
(

	//SRAM frame buffer access
	output logic 			SRAM_CE_N,
								SRAM_UB_N,		//Set to Low in default
								SRAM_LB_N,		//Set to Low in default
								SRAM_WE_N,
								SRAM_OE_N,
								
	output logic [19:0]	SRAM_ADDR,
	inout  wire [15:0]	SRAM_DQ,

	//From avalon_blitter_interface
	input  logic [63:0]	Coordinate,
	output logic 			Copy_Finish,
	
	//General input 
	input  logic 			Clk,
	input  logic			Reset, 
	input  logic 			Start,
	
	//VGA_feedback and control
	input  logic [17:0]	VGA_R_ADDR,			
	output logic [15:0]	VGA_R_DQ,
	input  logic 			VGA_CLK
);


	//Copy_R
	logic [9:0]		Sx,Sy,Ex,Ey;
	logic [9:0]		Dh,Dv;
	logic [20:0]	ADDR_R,ADDR_R_next;	//SRAM
	
	//Copy_W
	logic [9:0]		Tx,Ty;
	logic [19:0]	ADDR_W,ADDR_W_next;	//On_chip
	
	
	
///////////////////////////////////////////////////Auto Color Deleting/////////////////////////////////////////////////////////////////////
	
	logic [1:0]	On_chip_ByteE;
	always_comb begin
		if ((Blitter_W_to_On_chip[15:8] == 8'd255) && (Blitter_W_to_On_chip[7:0] == 8'd255))
			On_chip_ByteE = 2'b00;
		else if (Blitter_W_to_On_chip[15:8] == 8'd255)
			On_chip_ByteE = 2'b01;
		else if (Blitter_W_to_On_chip[7:0] == 8'd255)
			On_chip_ByteE = 2'b10;
		else
			On_chip_ByteE = 2'b11;		
	end
	


///////////////////////////////////////////////////Memory and DATA Portion//////////////////////////////////////////////////////////////////


	logic [15:0]	Blitter_R_from_SRAM;
	
	//On_chip memory data flow
	//Blitter Writing side
	logic [15:0]	Blitter_W_to_On_chip;
	logic 			On_chip_WE;
	
	
//////////////////////////////////////SRAM
	//tristate for SRAM Data
	//Honestly, this tristate is useless since we only pull data from it 
	//Attention, the tristate register is replaced by the Pixel register. 
	tristate #(16)	tristate_SRAM (.Clk(Clk), .tristate_output_enable(1'b0), .Data_write(16'hx), .Data_read(Blitter_R_from_SRAM), .Data(SRAM_DQ));
	assign SRAM_ADDR = ADDR_R[19:0];
	assign SRAM_CE_N = 1'b0;		//Default to select chip,Low and High bytes
	assign SRAM_LB_N = 1'b0;
	assign SRAM_UB_N = 1'b0;
	assign SRAM_WE_N = 1'b1;		//Never write the SDRAM
	assign SRAM_OE_N = 1'b0;		//Keep output enable high

	assign Blitter_W_to_On_chip = Blitter_R_from_SRAM;
	
	//RAM Selection, Select the Resource Section.
	logic [3:0]		RAM_Selection;
	logic [19:0]	SRAM_Offset;
	assign RAM_Selection = {Coordinate[63:62],Coordinate[31:30]};	
	
	always_comb begin
		case (RAM_Selection)
			4'b0000: SRAM_Offset = 20'h4B000;
			4'b0001: SRAM_Offset = 20'h70800;
			4'b0010: SRAM_Offset = 20'h25800;
			4'b0011: SRAM_Offset = 20'h00000;
			4'b0100:	SRAM_Offset = 20'h96000;
			default: SRAM_Offset = 20'h00000;
		endcase
	end
	
	

//	ram_153601x16 Buffer0 (	.Readdata(VGA_R_DQ), .Writedata(Blitter_W_to_On_chip), .Read_ADDR(VGA_R_ADDR), .Write_ADDR(ADDR_W),
//									.WE(On_chip_WE), .CLK_R(VGA_CLK), .CLK_W(Clk));
//	
//				

	logic [19:0]	ADDR_W_F;
	logic 			ADDR_REG_LD;
	
																											//VGA_CLK Need to be negated
	On_chip_buffer_v3 Buffer0 (.data (Blitter_W_to_On_chip), .rdaddress(VGA_R_ADDR), .rdclock(~VGA_CLK),
										.wraddress(ADDR_W[17:0]), .wrclock(Clk), .wren(On_chip_WE), .q(VGA_R_DQ),
										.byteena_a(On_chip_ByteE));	
										
										
////////////////////////////////////////////////////Memory Address FSM//////////////////////////////////////////////////////////////////////

		
	assign Sx = Coordinate[61:52];
	assign Sy = Coordinate[51:42];
	assign Ex = Coordinate[41:32];
	assign Ey = Coordinate[29:20];	
	assign Tx = Coordinate[19:10];
	assign Ty = Coordinate[9:0];
	
	//Setup the difference counter
	logic [9:0]	H_counter,V_counter,H_counter_next,V_counter_next;
	
	//Setup the Finite State Machine
	enum logic [2:0]	{Wait,R0,Copy_R,Copy_W,Copy_W_F,Done} state,next_state;

	always_ff @ (posedge Clk) begin
		
		//Reset condition
		if(Reset) begin
			state <= Wait;
			ADDR_R <= 21'h0;
			ADDR_W <= 20'h0;
			H_counter <=10'h0;
			V_counter <=10'h0;
		end
			
		//
		else begin
			state = next_state;
			ADDR_R <= ADDR_R_next;
			ADDR_W <= ADDR_W_next;
			H_counter <= H_counter_next;
			V_counter <= V_counter_next;
		end	
	end
	
	
	always_comb begin
	
		//Next_state allocation
		unique case(state)
			Wait: begin
			
				if (Start) begin
					next_state = R0;
					ADDR_R_next = (((Sy * ResWidth) + Sx) >> 1) + (SRAM_Offset);	
					ADDR_W_next = ((Ty * BufferWidth) + Tx) >> 1;
					H_counter_next = ((Ex-Sx) >> 1);				//Each ADDR store 2 pixel
					V_counter_next = Ey-Sy;
				end
				
				else begin
					next_state = Wait;
					ADDR_R_next = 21'h0;
					ADDR_W_next = 20'h0;
					H_counter_next = 10'h0;
					V_counter_next = 10'h0;
				end
			end
			
			R0: begin
					next_state = Copy_R;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W;
					H_counter_next = H_counter;
					V_counter_next = V_counter;
			end
				
			Copy_R: begin	
					//Finishing Copying
				if (H_counter == 10'h0 && V_counter == 10'h0) begin
					next_state = Copy_W_F;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W;
					H_counter_next = 10'h0;
					V_counter_next = 10'h0;
				end
				
				//Finishing Copying one line
				else if (H_counter == 10'h0) begin
					next_state = Copy_W;
					ADDR_R_next = ADDR_R + (ResWidth >> 1) - ((Ex-Sx) >> 1);
					ADDR_W_next = ADDR_W;// + (BufferWidth >> 1) - ((Ex-Sx) >> 1);
					H_counter_next = ((Ex-Sx) >> 1);	
					V_counter_next = V_counter - 1'd1;
				end
				
				else begin
					next_state = Copy_W;
					ADDR_R_next = ADDR_R + 1'd1;
					ADDR_W_next = ADDR_W; //+ 1'd1;				
					H_counter_next = H_counter - 1'd1;
					V_counter_next = V_counter;
				end	
			end
			
			
			Copy_W: begin	
				
				//Finishing Copying one line
				if (H_counter == (Ex-Sx) >> 1) begin
					next_state = Copy_R;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W + (BufferWidth >> 1) - ((Ex-Sx) >> 1);
					H_counter_next = H_counter;	
					V_counter_next = V_counter;
				end
				
				else begin
					next_state = Copy_R;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W + 1'd1;				
					H_counter_next = H_counter;
					V_counter_next = V_counter;
				end	
			end

			Copy_W_F: begin	
				next_state = Done;
				ADDR_R_next = ADDR_R;
				ADDR_W_next = ADDR_W;
				H_counter_next = H_counter;
				V_counter_next = V_counter;
			end
				
			Done: begin
			
				if (Start == 1'b0) begin
					next_state = Wait;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W;
					H_counter_next = 10'h0;
					V_counter_next = 10'h0;
				end
				
				else	begin
					next_state = Done;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W;
					H_counter_next = 10'h0;
					V_counter_next = 10'h0;
				end
				
			end
			
			default: begin
					next_state = Wait;
					ADDR_R_next = ADDR_R;
					ADDR_W_next = ADDR_W;
					H_counter_next = 10'h0;
					V_counter_next = 10'h0;
			end
			
		endcase			//End of the unique case		
			
			
		//Allocation of Output
		case (state)
			Wait: begin
				On_chip_WE = 1'b0;
				Copy_Finish = 1'b0;
			end
			
			R0: begin
				On_chip_WE = 1'b0;
				Copy_Finish = 1'b0;
			end
			
			Copy_R: begin
				On_chip_WE = 1'b0;
				Copy_Finish = 1'b0;
			end
			
			Copy_W: begin
				On_chip_WE = 1'b1;
				Copy_Finish = 1'b0;
			end
			
			Copy_W_F: begin
				On_chip_WE = 1'b1;
				Copy_Finish = 1'b0;
			end
			
			Done: begin
				On_chip_WE = 1'b0;
				Copy_Finish = 1'b1;
			end
			
			default: begin
				On_chip_WE = 1'b0;
				Copy_Finish = 1'b0;
			end	
			
		endcase
	end
	
	
	
endmodule





