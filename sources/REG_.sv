module REG_ #(parameter width)
(
	input logic [width-1:0]	Data_In,
	input logic Clk,
	input logic Reset,			//High active
	input logic LD_Enable,		//High active
	
	output logic [width-1:0] Data_Out

);


always_ff @ (posedge Clk)
	begin
	
	//Reset Case
	if(Reset)
		begin
		Data_Out <= {width{1'b0}};
		end
	
	//	Loading case
	else if(LD_Enable)
		begin
		Data_Out <= Data_In;
		end
	
	//Holding data case
	else
		begin
		Data_Out <= Data_Out;
		end
		
	end
	
endmodule



module Status_REG_
(
	input 	logic Reset,
	input 	logic Flip_NIOS,
	input 	logic Flip_Blitter,
	input 	logic Clk,
	
	output 	logic Status
);

	enum logic [3:0]	{Wait,Inter,Start,Inter1}state,next_state;

	
	always_ff @ (posedge Clk)
	begin
		if(Reset)
			state <= Wait;
		else
			state <= next_state;
	end
	
	
	always_comb begin
		unique case (state)
		
			Wait: begin
				if(Flip_NIOS)
					next_state = Inter;
				else
					next_state = Wait;
			end
			
			Inter: begin
				if (Flip_NIOS)
					next_state = Inter;
				else
					next_state = Start;
			end
			
			Start: begin
				if (Flip_Blitter)
					next_state = Inter1;
				else
					next_state = Start;
			end
			
			Inter1: begin
				if (Flip_Blitter)
					next_state = Inter1;
				else
					next_state = Wait;
			end
			
			default: begin
				next_state = Wait;
			end
			
		endcase
		
		//Output 
		case (state) 
			Wait:	Status = 1'b0;
			Inter: Status = 1'b1;
			Start: Status = 1'b1;
			Inter1: Status = 1'b0;
			default: Status = 1'b0;
		endcase
		
	end
endmodule





