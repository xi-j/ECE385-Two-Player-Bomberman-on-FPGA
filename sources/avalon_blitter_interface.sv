//------------------------------------------------------------------------------
// Engineer:		 Jerry Wang & Xilin Jiang
//
// Create Date:    
// Design Name:    Bomberman_final_project--avalon_blitter_interface 
// Module Name:    avalon_blitter_interface
//
// Comments:
//    Revised 11-07-2019
// 
//	This is the interface connecting the NIOS-II with the Blitter 
//	It provide the buffer for NIOS-II to put blitter instructions 
//	and the blitter will take the instruction to conduct 2D memory
//	copy.
//	
//	The register buffer size is tempoeraily set to 8, a.k.a we have 
//	8 groups of registers units. Each unit will have two data registers
//	and one status register. It will also have a global status register
//	to flag whether the NIOS-II have emit all the draw instructions.
//------------------------------------------------------------------------------


module avalon_blitter_interface 
(
	// Avalon Clock Input
	input logic CLOCK,
	
	// Avalon Reset Input
	input logic Hard_RESET,
	//	All controls are high acive
	// Avalon-MM Slave Signals
	input  logic AVL_READ,					// Avalon-MM Read
	input  logic AVL_WRITE,					// Avalon-MM Write
	input  logic AVL_CS,						// Avalon-MM Chip Select
	input  logic [3:0] AVL_BYTE_EN,		// Avalon-MM Byte Enable
	input  logic [4:0] AVL_ADDR,			// Avalon-MM Address				
	input  logic [31:0] AVL_WRITEDATA,	// Avalon-MM Write Data
	output logic [31:0] AVL_READDATA,	// Avalon-MM Read Data
	
	// Exported Conduit
	output logic [8:0] EXPORT_DATA,		// Exported status register to monitor
	output logic [31:0]EXPORT_TEST,
	
//	output 	logic [59:0]		Data_to_Blitter,
//	input  	logic 				Blitter_Finish_Flip

	//The Blitter Control output and input 
	output logic [63:0]		Data_to_Blitter,				//64 bit to make debug easier
	input	 logic 				Blitter_Finish_Flip,
	output logic 				Status_REG_Out

);

//Reset Signal
	logic Soft_Reset;
	
	assign RESET = Soft_Reset | Hard_RESET;
	always_comb begin
		if ((AVL_ADDR == 5'd31) && AVL_CS == 1 && AVL_WRITE == 1)
			Soft_Reset = 1'b1;
		else
			Soft_Reset = 1'b0;
	end
	

//Register Groups
	
	//Data register controlled_LD_Signal
	logic [31:0]		Data_to_REG;				//The top bit is used to indicate the stautus
	logic [7:0][63:0]	Data_from_REG;
	logic [16:0]		Controlled_LD_Signal;
	
	//Status register control
	logic [7:0]			REG_Status;
	logic [7:0]			REG_Status_Flip;



//////////////////////////Control Part

	logic [31:0]	ReadMux;
	logic [16:0]	LD_Signal;	//Need to AND with the CS and AVL_Write
	
	assign	AVL_READDATA = (AVL_CS && AVL_READ) ? ReadMux:32'dx;
	assign 	EXPORT_DATA = REG_Status; 
	assign 	EXPORT_TEST = Data_from_REG[0][31:0];  

	always_comb begin
		case (AVL_ADDR)
			
			//Data register control signals
			5'd0:	begin ReadMux = Data_from_REG[0][63:32]; LD_Signal = 17'h00001;		end
			5'd1:	begin ReadMux = Data_from_REG[0][31:0];  LD_Signal = 17'h00002;		end	
			
			5'd2:	begin ReadMux = Data_from_REG[1][63:32]; LD_Signal = 17'h00004;		end
			5'd3:	begin ReadMux = Data_from_REG[1][31:0];  LD_Signal = 17'h00008;		end
			
			5'd4:	begin ReadMux = Data_from_REG[2][63:32]; LD_Signal = 17'h00010;		end
			5'd5:	begin ReadMux = Data_from_REG[2][31:0];  LD_Signal = 17'h00020;		end	
			
			5'd6:	begin ReadMux = Data_from_REG[3][63:32]; LD_Signal = 17'h00040;		end
			5'd7:	begin ReadMux = Data_from_REG[3][31:0];  LD_Signal = 17'h00080;		end	
			
			5'd8:	begin ReadMux = Data_from_REG[4][63:32]; LD_Signal = 17'h00100;		end
			5'd9:	begin ReadMux = Data_from_REG[4][31:0];  LD_Signal = 17'h00200;		end	
			
			5'd10:begin ReadMux = Data_from_REG[5][63:32]; LD_Signal = 17'h00400;		end
			5'd11:begin ReadMux = Data_from_REG[5][31:0];  LD_Signal = 17'h00800;		end
			
			5'd12:begin ReadMux = Data_from_REG[6][63:32]; LD_Signal = 17'h01000;		end
			5'd13:begin ReadMux = Data_from_REG[6][31:0];  LD_Signal = 17'h02000;		end	
		
			5'd14:begin ReadMux = Data_from_REG[7][63:32]; LD_Signal = 17'h04000;		end
			5'd15:begin ReadMux = Data_from_REG[7][31:0];  LD_Signal = 17'h08000;		end	
			
			5'd16:begin ReadMux = {24'h0,REG_Status}; LD_Signal = 17'h10000;				end			//This LD signal will directly flip the Status Register
			
			default: begin ReadMux = 32'hx; LD_Signal = 17'h00000;							end
		endcase 
			    
		
		Controlled_LD_Signal = ({17{(AVL_CS)}}& {17{(AVL_WRITE)}} & LD_Signal); 
	
		case (AVL_BYTE_EN)
			4'b1111:	Data_to_REG = AVL_WRITEDATA;
			4'b1100:	Data_to_REG = {AVL_WRITEDATA[31:16], 16'h0000};
			4'b0011: Data_to_REG = {16'h0000, AVL_WRITEDATA[15:0]};
			4'b1000: Data_to_REG = {AVL_WRITEDATA[31:24], 24'h000000};
			4'b0100: Data_to_REG = {8'h00, AVL_WRITEDATA[23:16], 16'h0000};			
			4'b0010: Data_to_REG = {16'h0000, AVL_WRITEDATA[15:8], 8'h00};		
			4'b0001: Data_to_REG = {24'h000000, AVL_WRITEDATA[7:0]};
			default:	Data_to_REG = 32'dx;
		endcase
	end
///////////////////////////////////////////

/////////////To blitter wiring part

	logic [2:0]		Data_to_Blitter_Select;

	always_comb begin
	
		case(Data_to_Blitter_Select)
			3'd0:	begin Data_to_Blitter = Data_from_REG[0]; REG_Status_Flip = {7'h0,Blitter_Finish_Flip};		Status_REG_Out = REG_Status[0];	end
			3'd1:	begin Data_to_Blitter = Data_from_REG[1];	REG_Status_Flip = {6'h0,Blitter_Finish_Flip,1'h0};	Status_REG_Out = REG_Status[1];	end
			3'd2:	begin Data_to_Blitter = Data_from_REG[2]; REG_Status_Flip = {5'h0,Blitter_Finish_Flip,2'h0};	Status_REG_Out = REG_Status[2];	end
			3'd3:	begin Data_to_Blitter = Data_from_REG[3]; REG_Status_Flip = {4'h0,Blitter_Finish_Flip,3'h0};	Status_REG_Out = REG_Status[3];	end
			3'd4:	begin Data_to_Blitter = Data_from_REG[4]; REG_Status_Flip = {3'h0,Blitter_Finish_Flip,4'h0};	Status_REG_Out = REG_Status[4];	end
			3'd5:	begin Data_to_Blitter = Data_from_REG[5]; REG_Status_Flip = {2'h0,Blitter_Finish_Flip,5'h0};	Status_REG_Out = REG_Status[5];	end
			3'd6:	begin Data_to_Blitter = Data_from_REG[6]; REG_Status_Flip = {1'h0,Blitter_Finish_Flip,6'h0};	Status_REG_Out = REG_Status[6];	end
			3'd7:	begin Data_to_Blitter = Data_from_REG[7]; REG_Status_Flip = {Blitter_Finish_Flip,7'h0};		Status_REG_Out = REG_Status[7];	end
		endcase
	
	end
	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////Blitter Feeding part//////////////////////////////////////////////////////////////
	
	enum logic [3:0]	{W0,R0,W1,R1,W2,R2,W3,R3,W4,R4,W5,R5,W6,R6,W7,R7}state,next_state;
	
	//Basic of Finite State Machine
	always_ff @ (posedge CLOCK)
	begin
		
		if(RESET)
			state <= W0;
		else
			state <= next_state;
	end
	
	
	always_comb begin	
		//next_state allocation
		unique case(state)
			W0: 	begin 	if(REG_Status[0])
									next_state = R0;
								else
									next_state = W0;
					end
			R0: 	begin 	if(REG_Status[0])
									next_state = R0;
								else
									next_state = W1;
					end
			W1: 	begin 	if(REG_Status[1])
									next_state = R1;
								else
									next_state = W1;
					end
			R1: 	begin 	if(REG_Status[1])
									next_state = R1;
								else
									next_state = W2;
					end	
			W2: 	begin 	if(REG_Status[2])
									next_state = R2;
								else
									next_state = W2;
					end
			R2: 	begin 	if(REG_Status[2])
									next_state = R2;
								else
									next_state = W3;
					end
			W3: 	begin 	if(REG_Status[3])
									next_state = R3;
								else
									next_state = W3;
					end
			R3: 	begin 	if(REG_Status[3])
									next_state = R3;
								else
									next_state = W4;
					end		
			W4: 	begin 	if(REG_Status[4])
									next_state = R4;
								else
									next_state = W4;
					end
			R4: 	begin 	if(REG_Status[4])
									next_state = R4;
								else
									next_state = W5;
					end
			W5: 	begin 	if(REG_Status[5])
									next_state = R5;
								else
									next_state = W5;
					end	
			R5: 	begin 	if(REG_Status[5])
									next_state = R5;
								else
									next_state = W6;
					end	
			W6: 	begin 	if(REG_Status[6])
									next_state = R6;
								else
									next_state = W6;
					end
			
			R6: 	begin 	if(REG_Status[6])
									next_state = R6;
								else
									next_state = W7;
					end				
			W7: 	begin 	if(REG_Status[7])
									next_state = R7;
								else
									next_state = W7;
					end		
			R7: 	begin 	if(REG_Status[7])
									next_state = R7;
								else
									next_state = W0;
					end			
					
			default: next_state = W7;
		endcase
		
		
		
		//Output allocation
		case (state)
			W0:	begin	
					Data_to_Blitter_Select = 3'd0;
					end
			R0:	begin	
					Data_to_Blitter_Select = 3'd0;
					end
			W1:	begin	
					Data_to_Blitter_Select = 3'd1;
					end
			R1:	begin	
					Data_to_Blitter_Select = 3'd1;
					end
			W2:	begin	
					Data_to_Blitter_Select = 3'd2;
					end
			R2:	begin	
					Data_to_Blitter_Select = 3'd2;
					end
			W3:	begin	
					Data_to_Blitter_Select = 3'd3;
					end
			R3:	begin	
					Data_to_Blitter_Select = 3'd3;
					end	
			W4:	begin	
					Data_to_Blitter_Select = 3'd4;
					end
			R4:	begin	
					Data_to_Blitter_Select = 3'd4;
					end
			W5:	begin	
					Data_to_Blitter_Select = 3'd5;
					end
			R5:	begin	
					Data_to_Blitter_Select = 3'd5;
					end
			W6:	begin	
					Data_to_Blitter_Select = 3'd6;
					end
			R6:	begin	
					Data_to_Blitter_Select = 3'd6;
					end
			W7:	begin	
					Data_to_Blitter_Select = 3'd7;
					end
			R7:	begin	
					Data_to_Blitter_Select = 3'd7;
					end		
			default: Data_to_Blitter_Select = 3'd0;
		endcase
	end
	



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////Register File Part////////////////////////////////////////////////////////////////

	//Register group 
	REG_ #(32)	BI0_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[0][63:32]), .LD_Enable(Controlled_LD_Signal[0]));
	REG_ #(32)	BI0_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[0][31:0]),  .LD_Enable(Controlled_LD_Signal[1]));
	
	REG_ #(32)	BI1_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[1][63:32]), .LD_Enable(Controlled_LD_Signal[2]));
	REG_ #(32)	BI1_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[1][31:0]),  .LD_Enable(Controlled_LD_Signal[3]));
	
	REG_ #(32)	BI2_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[2][63:32]), .LD_Enable(Controlled_LD_Signal[4]));
	REG_ #(32)	BI2_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[2][31:0]),  .LD_Enable(Controlled_LD_Signal[5]));
	
	REG_ #(32)	BI3_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[3][63:32]), .LD_Enable(Controlled_LD_Signal[6]));
	REG_ #(32)	BI3_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[3][31:0]),  .LD_Enable(Controlled_LD_Signal[7]));
	
	REG_ #(32)	BI4_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[4][63:32]), .LD_Enable(Controlled_LD_Signal[8]));
	REG_ #(32)	BI4_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[4][31:0]),  .LD_Enable(Controlled_LD_Signal[9]));
	
	REG_ #(32)	BI5_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[5][63:32]), .LD_Enable(Controlled_LD_Signal[10]));
	REG_ #(32)	BI5_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[5][31:0]),  .LD_Enable(Controlled_LD_Signal[11]));
	
	REG_ #(32)	BI6_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[6][63:32]), .LD_Enable(Controlled_LD_Signal[12]));
	REG_ #(32)	BI6_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[6][31:0]),  .LD_Enable(Controlled_LD_Signal[13]));	
	
	REG_ #(32)	BI7_0(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[7][63:32]), .LD_Enable(Controlled_LD_Signal[14]));
	REG_ #(32)	BI7_1(.Clk(CLOCK), .Reset(RESET), .Data_In(Data_to_REG), .Data_Out(Data_from_REG[7][31:0]),  .LD_Enable(Controlled_LD_Signal[15]));	

	//Status Register		//when input one,
	Status_REG_ BI0_S(.Clk(CLOCK), .Status(REG_Status[0]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[1]),  .Flip_Blitter(REG_Status_Flip[0]));
	Status_REG_ BI1_S(.Clk(CLOCK), .Status(REG_Status[1]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[3]),  .Flip_Blitter(REG_Status_Flip[1]));
	Status_REG_ BI2_S(.Clk(CLOCK), .Status(REG_Status[2]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[5]),  .Flip_Blitter(REG_Status_Flip[2]));
	Status_REG_ BI3_S(.Clk(CLOCK), .Status(REG_Status[3]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[7]),  .Flip_Blitter(REG_Status_Flip[3]));	
	Status_REG_ BI4_S(.Clk(CLOCK), .Status(REG_Status[4]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[9]),  .Flip_Blitter(REG_Status_Flip[4]));
	Status_REG_ BI5_S(.Clk(CLOCK), .Status(REG_Status[5]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[11]), .Flip_Blitter(REG_Status_Flip[5]));
	Status_REG_ BI6_S(.Clk(CLOCK), .Status(REG_Status[6]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[13]), .Flip_Blitter(REG_Status_Flip[6]));
	Status_REG_ BI7_S(.Clk(CLOCK), .Status(REG_Status[7]), .Reset(RESET), .Flip_NIOS(Controlled_LD_Signal[15]), .Flip_Blitter(REG_Status_Flip[7]));		

endmodule
	








