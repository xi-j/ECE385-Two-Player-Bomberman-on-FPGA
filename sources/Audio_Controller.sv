//------------------------------------------------------------------------------
// Author:		 Jerry Wang & Xilin Jiang
//
// Create Date:    
// Design Name:    Bomberman_final_project
// Module Name:    Audio_COntroller
//
// Comments:
//    Revised 12-06-2019
//
//	Version:	V.1
//
// 
//	This is the Audio Controller module that handles the playing of music
// 
//	Audio_Select:
// 
//			0: 	OP
//			1:	Game0
//			2:	Game05
//			3: Game1
//			4:	FF
//
//
//	 This module will also include the singel frame buffer itself.
//	
//------------------------------------------------------------------------------

module Audio_Controller 
(
	//General
	input 	logic	 				Clk, Reset,

	//Flash Memory
	output 	logic [22:0]		FL_ADDR,
	inout	 	wire [7:0]			FL_DQ,
	output 	logic 				FL_WE_N, FL_OE_N, FL_CE_N, FL_RST_N,
	output 	logic 				FL_WP_N,
	input 	logic 				FL_RY,				//Not use during normal time
	
	//Audio Interface
	input 	logic 				INIT_F,
	output 	logic 				INIT,
	output 	logic [15:0]		LDATA,RDATA,
	input 	logic 				data_over,

	input 	logic [2:0]			Back_Vol,
	input 	logic 				Bomb_Active,
	input 	logic [2:0]			Bomb_Vol,
	input 	logic [2:0]			Audio_Select
);

//Always assign
	assign FL_WE_N = 1'b1;
	assign FL_CE_N = 1'b0;
	assign FL_OE_N = 1'b0;
	assign FL_RST_N = ~Reset;
	assign FL_WP_N = 1'bx;	
	
//////////////////////////////////////////FSM

	enum logic [5:0]	{	A_INIT,Wait,									//Four memory copy cycle, each delay 120ns
	
								//Background Music Copy
								Copy0,w00,w01,w02,w03,w04,w05,	
								Copy1,w10,w11,w12,w13,w14,w15,
//								Copy2,w20,w21,w22,w23,w24,w25,
//								Copy3,w30,w31,w32,w33,w34,w35,
								
								//Bomb_Sound Copy
								Copy4,w40,w41,w42,w43,w44,w45,	
								Copy5,w50,w51,w52,w53,w54,w55,
								
								//Finish State
								Done
							} state, next_state;
							
//For debUG

													
	logic [22:0]	ADDR_Counter, ADDR_Counter_next;
	logic [5:0]	REG_LD;
	logic G1_Flag,G1_Flag_next;
							
	always_ff @  (posedge Clk) begin
	
		if (Reset) begin
			state <= A_INIT;
			ADDR_Counter <= 23'd0;
			G1_Flag <= 1'b0;
			end
			
		else begin
			state <= next_state;
			ADDR_Counter <= ADDR_Counter_next;	
			G1_Flag <= G1_Flag_next;
		end
		
	end

	always_comb begin
	
		//next_state allocation
		unique case(state)
		
			A_INIT: begin
				if (INIT_F)
					next_state = Wait;
				else
					next_state = A_INIT;
				end
		
		
			Wait: begin
				if (data_over)
					next_state = Copy0;
				else
					next_state = Wait;
				end
			
			//L_MSB_8
			Copy0:	next_state = w00;
			
			w00:	 	next_state = w01;
			
			w01:	 	next_state = w02;			
	
			w02:	 	next_state = w03;
			
			w03:	 	next_state = w04;
			
			w04:	 	next_state = w05;	
	
			w05:	 	next_state = Copy1;	
		
			//L_LSB_8
			Copy1:	next_state = w10;
			
			w10:	 	next_state = w11;
			
			w11:	 	next_state = w12;			
	
			w12:	 	next_state = w13;
			
			w13:	 	next_state = w14;
			
			w14:	 	next_state = w15;	
			
//			w15:		next_state = Copy2;
	
			w15:	begin
						
				if (Bomb_Output_E)
					next_state = Copy4;
				else
					next_state = Done;
			end	
	
//			//R_MSB_8  Not Used since it is Mono
//			Copy2:	next_state = w20;
//			
//			w20:	 	next_state = w21;
//			
//			w21:	 	next_state = w22;			
//	
//			w22:	 	next_state = w23;
//			
//			w23:	 	next_state = w24;
//			
//			w24:	 	next_state = w25;	
//	
//			w25:	 	next_state = Copy3;			
		
			//R_LSB_8 Not used for MONO
//			Copy3:	next_state = w30;
//			
//			w30:	 	next_state = w31;
//			
//			w31:	 	next_state = w32;			
//	
//			w32:	 	next_state = w33;
//			
//			w33:	 	next_state = w34;
//			
//			w34:	 	next_state = w35;	
//	
//			w35:	begin
//						
//				if (Bomb_Output_E)
//					next_state = Copy4;
//				else
//					next_state = Done;
//			end
//			
			//Bomb_M
			Copy4:	next_state = w40;
			
			w40:	 	next_state = w41;
			
			w41:	 	next_state = w42;			
	
			w42:	 	next_state = w43;
			
			w43:	 	next_state = w44;
			
			w44:	 	next_state = w45;	
	
			w45:	 	next_state = Copy5;	

			//Bomb_L
			Copy5:	next_state = w50;
			
			w50:	 	next_state = w51;
			
			w51:	 	next_state = w52;			
	
			w52:	 	next_state = w53;
			
			w53:	 	next_state = w54;
			
			w54:	 	next_state = w55;	
	
			w55:	 	next_state = Done;	

			//Done State
			Done: begin
				if (data_over)
					next_state = Done;
				else
					next_state = Wait;
				end
		endcase
		
		
		//Output allocation
		case (state)
		
//			A_INIT:	REG_LD = 6'b000000;
//			Wait:		REG_LD = 6'b000000;
//			Copy0: 	REG_LD = 6'b000000;
//			w00:		REG_LD = 6'b000000;
//			w01:		REG_LD = 6'b000000;		
//			w02:		REG_LD = 6'b000000;		
//			w03:		REG_LD = 6'b000000;		
//			w04:		REG_LD = 6'b000000;		
			w05:		REG_LD = 6'b000001;	
			
//			Copy1: 	REG_LD = 6'b000000;
//			w10:		REG_LD = 6'b000000;
//			w11:		REG_LD = 6'b000000;		
//			w12:		REG_LD = 6'b000000;		
//			w13:		REG_LD = 6'b000000;		
//			w14:		REG_LD = 6'b000000;
			w15:		REG_LD = 6'b000010;				
		
//			Copy2: 	REG_LD = 6'b000000;
//			w20:		REG_LD = 6'b000000;
//			w21:		REG_LD = 6'b000000;		
//			w22:		REG_LD = 6'b000000;		
//			w23:		REG_LD = 6'b000000;		
//			w24:		REG_LD = 6'b000000;	
//			w25:		REG_LD = 6'b000100;			
			
//			Copy3: 	REG_LD = 6'b000000;
//			w30:		REG_LD = 6'b000000;
//			w31:		REG_LD = 6'b000000;		
//			w32:		REG_LD = 6'b000000;		
//			w33:		REG_LD = 6'b000000;		
//			w34:		REG_LD = 6'b000000;	
//			w35:		REG_LD = 6'b001000;		
			
//			Copy4: 	REG_LD = 6'b000000;
//			w40:		REG_LD = 6'b000000;
//			w41:		REG_LD = 6'b000000;		
//			w42:		REG_LD = 6'b000000;		
//			w43:		REG_LD = 6'b000000;		
//			w44:		REG_LD = 6'b000000;	
			w45:		REG_LD = 6'b010000;			
			
//			Copy5: 	REG_LD = 6'b000000;
//			w50:		REG_LD = 6'b000000;
//			w51:		REG_LD = 6'b000000;		
//			w52:		REG_LD = 6'b000000;		
//			w53:		REG_LD = 6'b000000;		
//			w54:		REG_LD = 6'b000000;	
			w55:		REG_LD = 6'b100000;	

//			Done:		REG_LD = 6'b000000;
			default:	REG_LD = 6'b000000;
		endcase
		

		
		//ADDR Counter increment
		//Accidental OP
		if ((Audio_Select == 3'd0) && (ADDR_Counter[0] == 1'b0)) begin
			ADDR_Counter_next = 23'h0; G1_Flag_next = 1'b0;
		end
		
		//Accidental FF
		else if ((Audio_Select == 3'd4) && (ADDR_Counter[0] == 1'b0)) begin
			ADDR_Counter_next = 23'h61b538; G1_Flag_next = 1'b0;
		end
			
		else if ((Audio_Select == 3'd1) && (ADDR_Counter[0] == 1'b0)) begin
			ADDR_Counter_next = 23'h13618a;G1_Flag_next = 1'b0;
		end
		
		//Returning point decided   Game0 Game05 Game1 FF OP
		else if ((ADDR_Counter == 23'h136188) || (ADDR_Counter == 23'h3873ea) || (ADDR_Counter == 23'h3e19d4) || (ADDR_Counter == 23'h61b536) || (ADDR_Counter == 23'h67c91a))begin
			case (Audio_Select)

				3'd2: begin 
							if (!G1_Flag) begin
								ADDR_Counter_next = 23'h3873ec; G1_Flag_next = 1'b1;   //ADDR of Game05
							end
							
							else 
								ADDR_Counter_next = 23'h3e19d6; G1_Flag_next = 1'b1;  //ADDR of Game1
						end		
						
				3'd3: begin ADDR_Counter_next = 23'h3e19d6; G1_Flag_next = 1'b0; end	//ADDR of Game1
				
				3'd5: begin ADDR_Counter_next = 23'h0; G1_Flag_next = 1'b0; end				//ADDR of OP
//				3'd6: begin ADDR_Counter_next = 23'h0; G1_Flag_next = 1'b0; end		//ADDR of FF
				3'd7: begin ADDR_Counter_next = 23'h13618a; G1_Flag_next = 1'b0; end
				default: begin ADDR_Counter_next = 23'hx; G1_Flag_next = 1'b0; end
			endcase
		end
		
		else if ((state == w05) || (state == w15) /*| (state == w25) | (state == w35)*/) begin	//Not use for MONO 
			ADDR_Counter_next = ADDR_Counter + 23'd1;
			G1_Flag_next = G1_Flag;
		end
		
		else begin
			ADDR_Counter_next = ADDR_Counter;
			G1_Flag_next = G1_Flag;
		end
			
		//INIT
		if (state == A_INIT)
			INIT = 1'b1;
		else
			INIT = 1'b0;
				
	end
	
	
//	assign FL_ADDR = ADDR_Counter;
	always_comb begin
		if ((state == Copy4)||(state == w40)||(state == w41)||(state == w42)||(state == w43)||(state == w44)||(state == w45)||
			(state == Copy5)||(state == w50)||(state == w51)||(state == w52)||(state == w53)||(state == w54)||(state == w55)) begin
			
			FL_ADDR = Bomb_ADDR_Counter;
		end
		
		else		
			FL_ADDR = ADDR_Counter;
	end
	
//////////////////////////////////////////Bomb_Active_Detection

//Tigger detaction
	logic Bomb_temp1, Bomb_Active_Trigger;

	always_ff @ (posedge Clk) begin
		Bomb_temp1 <= Bomb_Active;
	end
	
	//Generate the trigger signal
	assign Bomb_Active_Trigger = ~(Bomb_temp1) & Bomb_Active; 
	

//Counter 	

	//Bomb_Counter
	logic [22:0]	Bomb_ADDR_Counter;
	logic 			Bomb_Output_E;
	
	always_ff @ (posedge Clk) begin
	
		if (Bomb_Active_Trigger) begin
			Bomb_ADDR_Counter <= 23'h67c91c;
			Bomb_Output_E <= 1'd1;
		end
		
		else if (Bomb_ADDR_Counter == 23'h6cb40a) begin
			Bomb_ADDR_Counter <= 23'h67c91c;
			Bomb_Output_E <= 1'd0;
		end
		
		else if ((state == w45) || (state == w55)) begin
			Bomb_ADDR_Counter <= Bomb_ADDR_Counter + 23'd1;
			Bomb_Output_E <= Bomb_Output_E;
		end
		
		//Retain the value
		else begin
			Bomb_ADDR_Counter <= Bomb_ADDR_Counter;
			Bomb_Output_E <= Bomb_Output_E;
		end
		
	end
	
////////////////////////////////////////////////////Wiring

	logic [7:0]	Audio_R_from_FL;

	//Tristate buffer 
	tristate #(8)	tristate_FL (.Clk(Clk), .tristate_output_enable(1'b0), .Data_write(8'hx), .Data_read(Audio_R_from_FL), .Data(FL_DQ));
	
	
	//Data buffer
	REG_ #(8)	LM(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(LDATA_Post[15:8]), .LD_Enable(REG_LD[0]));	
	REG_ #(8)	LL(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(LDATA_Post[7:0]), 	.LD_Enable(REG_LD[1]));	
	
//	Not used for MONO
//	REG_ #(8)	RM(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(RDATA_Post[15:8]), .LD_Enable(REG_LD[2]));	
//	REG_ #(8)	RL(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(RDATA_Post[7:0]), 	.LD_Enable(REG_LD[3]));	
	
	REG_ #(8)	BombM(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(Bomb_Post[15:8]), .LD_Enable(REG_LD[4]));	
	REG_ #(8)	BombL(.Clk(Clk), .Reset(Reset), .Data_In(Audio_R_from_FL), .Data_Out(Bomb_Post[7:0]), 	.LD_Enable(REG_LD[5]));		

	

	logic [18:0]	LDATA_Post, /*RDATA_Post,*/ Bomb_Post;
	logic [18:0]	LDATA_Mid, /*RDATA_Mid,*/ Bomb_Mid;
	logic [18:0]	L_Reg,Bomb_Reg;
	logic [18:0]	LDATA_Final, /*RDATA_Final,*/ Bomb_Final;
	
	REG_ #(19)	L_Buffer(.Clk(Clk), .Reset(Reset), .Data_In(LDATA_Mid), .Data_Out(L_Reg), .LD_Enable(1));	
	REG_ #(19)	Bomb_Buffer(.Clk(Clk), .Reset(Reset), .Data_In(Bomb_Mid), .Data_Out(Bomb_Reg), .LD_Enable(1));

	assign LDATA_Post[18:16] = {3{LDATA_Post[15]}};
	assign Bomb_Post[18:16] = {3{Bomb_Post[15]}};
	
	
	always_comb begin
//////////////////////////////////////////Left Channel
	
//Volume Mutiply		
		if (LDATA_Post[18] == 1'b0)
			LDATA_Mid = LDATA_Post * Back_Vol;
		else
			LDATA_Mid = (~(LDATA_Post)+1'd1) * Back_Vol;
	
//Volume Divide
		if (LDATA_Post[18] == 1'b0) begin	//Positive
			
			if (L_Reg < 19'd64)
				LDATA_Final = 19'd1;
			else
				LDATA_Final = L_Reg >> 6;
		end
		
		else begin
		
			if (L_Reg < 19'd64)
				LDATA_Final = 19'h7ffff;
			else
				LDATA_Final = ~((L_Reg) >> 6)+19'd1;
		end
		
//////////////////////////////////////Right Channel   Not used for MONO
//		
//				
//		if (RDATA_Post[15] == 1'b0) begin	//Positive
//			
//			if (RDATA_Post < 16'd16)
//				RDATA_Mid = 16'd1;
//			else
//				RDATA_Mid = RDATA_Post/16'd16;
//		end
//		
//		else begin
//		
//			if ((~(RDATA_Post)+16'd1) < 16'd16)
//				RDATA_Mid = 16'd1;
//			else
//				RDATA_Mid = ((~RDATA_Post)+16'd1)/16'd16;
//		end
//		
////Vol mutiply
//
//		if (RDATA_Post[15] == 1'b0)
//			RDATA_Final = RDATA_Mid * Back_Vol;
//		else
//			RDATA_Final = ~(RDATA_Mid * Back_Vol) + 1'd1;
//		
//				
//
//	
//	
////////////////////////////////////////////////////////////////////////////////
	
///////////////////////////////////////Bomb_Sound_Vol
//Volume Mutiply		
		if (Bomb_Post[18] == 1'b0)
			Bomb_Mid = Bomb_Post * Bomb_Vol;
		else
			Bomb_Mid = (~(Bomb_Post)+1'd1) * Bomb_Vol;
	
//Volume Divide
		if (Bomb_Post[18] == 1'b0) begin	//Positive
			
			if (Bomb_Reg < 19'd64)
				Bomb_Final = 19'd1;
			else
				Bomb_Final = Bomb_Reg >> 6;
		end
		
		else begin
		
			if (Bomb_Reg < 19'd64)
				Bomb_Final = 19'h7ffff;
			else
				Bomb_Final = ~((Bomb_Reg) >> 6)+19'd1;
		end
		
		
	//End of always comb
	end
//////////////////////////////////////////Final Sound Combination
	
	always_comb begin
		if (Bomb_Output_E) begin
			LDATA = LDATA_Final[15:0] + Bomb_Final;
//			RDATA = RDATA_Final + Bomb_Final;		//Not Used for MONO
			RDATA = LDATA_Final[15:0] + Bomb_Final;
		end
		
		else begin
			LDATA = LDATA_Final[15:0];
			RDATA = LDATA_Final[15:0];
//			RDATA = RDATA_Final;							//Not Used for MONO
		end
	end
endmodule

