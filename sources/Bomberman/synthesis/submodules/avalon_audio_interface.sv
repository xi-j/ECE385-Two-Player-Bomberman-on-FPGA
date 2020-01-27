// This is the module that handle the connection between the NIOS
//	and the outside audio interface. An FIFO buffer is included so 
// that the CPU could prepare more data in advanced.
// The data register map is shown below
//	ADDR:
//		Write 00:	FIFO Buffer (L + R)
//		Read 	01:	Read full signals
//		Read 	10:	Read Empty signals
//		Write 11:	SoftReset


module avalon_audio_interface
(
	input logic CLOCK,
	
	// Avalon Reset Input
	input logic RESET,
	//	All controls are high acive
	// Avalon-MM Slave Signals
	input  logic AVL_WRITE,					// Avalon-MM Write
	input  logic AVL_CS,						// Avalon-MM Chip Select

	input  logic [1:0]		AVL_ADDR,			// Avalon-MM Address				
	input  logic [31:0] 		AVL_WRITEDATA,	// Avalon-MM Write Data
	
	input  logic 				AVL_READ,
	output logic [31:0]		AVL_READDATA,
	
	output 	logic [31:0] 	Audio_fifo_Out,
	input 	logic 			Audio_DQ_Require,
	
	output 	logic [31:0]			DEBUG
	
);
//


	
	
//FIFO Reset 
	logic Soft_Reset;

	assign Soft_Reset = AVL_CS & AVL_WRITE & AVL_ADDR[0] & AVL_ADDR[1];
	
//Read Status

	logic FIFO_Full, FIFO_AEmpty;
	logic [7:0]	Usage;

	always_comb begin
	
		if (AVL_ADDR == 2'b01)
			AVL_READDATA = {24'd0, Usage};
		else if (AVL_ADDR == 2'b10)
			AVL_READDATA = {31'd0, FIFO_Full};
		else
			AVL_READDATA = 32'hx;

	end

///////////////////////////////////////////////Edge Detect and Preload Register
	
	assign DEBUG = Preload_Out;
	
	//Preload Register
	logic [31:0]	Preload_Out;
	logic 			Preload_LD;
	
	assign	Preload_LD = AVL_CS & AVL_WRITE & (~AVL_ADDR[0]) & ~(AVL_ADDR[1]);
	
	REG_ #(32)	Preload(.Clk(CLOCK), .Reset(RESET), .Data_In(AVL_WRITEDATA), .Data_Out(Preload_Out),  .LD_Enable(Preload_LD));	

	//Edge Detection
	logic Fall_Edge, LD_Delay;
	
	always_ff @ (posedge CLOCK) begin
		LD_Delay <= Preload_LD;
	end
	
	assign Fall_Edge = (~(Preload_LD)) & LD_Delay;
	

///////////////////////////////////////////////Call FIFO	
	
	
	logic [15:0]	FIFO_L_Out, FIFO_R_Out;
	
	logic Audio_Read_Req;
	
	assign Audio_fifo_Out = {FIFO_L_Out, FIFO_R_Out};
	
	logic Virtual0, Virtual1;
	

	
	
//	fifo_v2	audio_bufferL (.clock(CLOCK), .data(Preload_Out[31:16]), .wrreq(Fall_Edge), .full(FIFO_Full),
//								.almost_empty(FIFO_AEmpty), .q(FIFO_L_Out), .rdreq(Audio_Read_Req),
//								.sclr(Soft_Reset | RESET));
//	
//	fifo_v2	audio_bufferR (.clock(CLOCK), .data(Preload_Out[15:0]), .wrreq(Fall_Edge), .full(Virtual0),
//								.almost_empty(Virtual1), .q(FIFO_R_Out), .rdreq(Audio_Read_Req),
//								.sclr(Soft_Reset | RESET));
//	
	fifo_v3	audio_bufferL (.clock(CLOCK), .data(Preload_Out[31:16]), .wrreq(Fall_Edge), .usedw(Usage),
								.full(FIFO_Full), .q(FIFO_L_Out), .rdreq(Audio_Read_Req),
								.sclr(Soft_Reset | RESET));
	
	fifo_v3	audio_bufferR (.clock(CLOCK), .data(Preload_Out[15:0]), .wrreq(Fall_Edge), .usedw(Virtual0),
								.full(Virtual1), .q(FIFO_R_Out), .rdreq(Audio_Read_Req),
								.sclr(Soft_Reset | RESET));
	



////////////////////////////////////////////FSM part

	enum logic [1:0]	{Wait,Read,Wait_1}	state, next_state;
	
	always_ff @ (posedge CLOCK) begin
	
		if (RESET | Soft_Reset)
			state <= Wait;
		else
			state <= next_state;
	
	end
	
	always_comb begin
		//Next state case
		unique case (state)
		
			Wait: begin
				if (Audio_DQ_Require)
					next_state = Read;
				else
					next_state = Wait;
					end
			
			Read: begin
					next_state = Wait_1;
					end
					
			Wait_1: begin
				if (Audio_DQ_Require)
					next_state = Wait_1;
				else
					next_state = Wait;
					end
		
		endcase
		
		//Output case
		case (state)
			
			Wait:	
				Audio_Read_Req = 1'b0;
				
			Read:
				Audio_Read_Req = 1'b1;
				
			Wait_1:
				Audio_Read_Req = 1'b0;
				
		endcase
	end

endmodule

