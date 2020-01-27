//------------------------------------------------------------------------------
// Engineer:		 Jerry Wang & Xilin Jiang
//
// Create Date:    
// Design Name:    Bomberman_final_project--Palettes
// Module Name:    Palettes
//
// This module convert the 8_bit color to 24_bit color via Palettes
//	
//------------------------------------------------------------------------------

module Palettes
(
	input 	logic [7:0]		RGB_8,
	input 	Clk,
	
	output 	logic [7:0]	R_24,G_24,B_24

);

	logic [23:0]	out;
		
	assign R_24 = out[23:16];
	assign G_24 = out[15:8];
	assign B_24 = out[7:0];

	always_ff @ (posedge Clk) begin	
		case (RGB_8)
			8'd0:  out <= 24'h000000; 	   	8'd64:  out <= 24'h5f8700;    	8'd128: out <= 24'haf00d7;    	8'd192: out <= 24'hd7ff87;
			8'd1:  out <= 24'h800000;  	  	8'd65:  out <= 24'h5f875f;    	8'd129: out <= 24'haf00ff;    	8'd193: out <= 24'hd7ffaf;
			8'd2:  out <= 24'h008000;   		8'd66:  out <= 24'h5f8787;    	8'd130: out <= 24'haf5f00;    	8'd194: out <= 24'hd7ffd7;
			8'd3:  out <= 24'h808000;    		8'd67:  out <= 24'h5f87af;    	8'd131: out <= 24'haf5f5f;   		8'd195: out <= 24'hd7ffff;
			8'd4:  out <= 24'h000080;    		8'd68:  out <= 24'h5f87d7;    	8'd132: out <= 24'haf5f87;    	8'd196: out <= 24'hff0000;
			8'd5:  out <= 24'h800080;    		8'd69:  out <= 24'h5f87ff;    	8'd133: out <= 24'haf5faf;    	8'd197: out <= 24'hff005f;
			8'd6:  out <= 24'h008080;    		8'd70:  out <= 24'h5faf00;    	8'd134: out <= 24'haf5fd7;    	8'd198: out <= 24'hff0087;
			8'd7:  out <= 24'hc0c0c0;    		8'd71:  out <= 24'h5faf5f;    	8'd135: out <= 24'haf5fff;    	8'd199: out <= 24'hff00af;
			8'd8:  out <= 24'h808080;    		8'd72:  out <= 24'h5faf87;    	8'd136: out <= 24'haf8700;    	8'd200: out <= 24'hff00d7;
			8'd9:  out <= 24'hff0000;    		8'd73:  out <= 24'h5fafaf;    	8'd137: out <= 24'haf875f;    	8'd201: out <= 24'hff00ff;
			8'd10: out <= 24'h00ff00;    		8'd74:  out <= 24'h5fafd7;    	8'd138: out <= 24'haf8787;    	8'd202: out <= 24'hff5f00;
			8'd11: out <= 24'hffff00;    		8'd75:  out <= 24'h5fafff;    	8'd139: out <= 24'haf87af;    	8'd203: out <= 24'hff5f5f;
			8'd12: out <= 24'h0000ff;    		8'd76:  out <= 24'h5fd700;    	8'd140: out <= 24'haf87d7;    	8'd204: out <= 24'hff5f87;
			8'd13: out <= 24'hff00ff;    		8'd77:  out <= 24'h5fd75f;    	8'd141: out <= 24'haf87ff;    	8'd205: out <= 24'hff5faf;
			8'd14: out <= 24'h00ffff;    		8'd78:  out <= 24'h5fd787;    	8'd142: out <= 24'hafaf00;    	8'd206: out <= 24'hff5fd7;
			8'd15: out <= 24'hffffff;    		8'd79:  out <= 24'h5fd7af;    	8'd143: out <= 24'hafaf5f;    	8'd207: out <= 24'hff5fff;
			8'd16: out <= 24'h000000;    		8'd80:  out <= 24'h5fd7d7;    	8'd144: out <= 24'hafaf87;    	8'd208: out <= 24'hff8700;
			8'd17: out <= 24'h00005f;    		8'd81:  out <= 24'h5fd7ff;    	8'd145: out <= 24'hafafaf;    	8'd209: out <= 24'hff875f;
			8'd18: out <= 24'h000087;    		8'd82:  out <= 24'h5fff00;    	8'd146: out <= 24'hafafd7;    	8'd210: out <= 24'hff8787;
			8'd19: out <= 24'h0000af;    		8'd83:  out <= 24'h5fff5f;    	8'd147: out <= 24'hafafff;    	8'd211: out <= 24'hff87af;
			8'd20: out <= 24'h0000d7;    		8'd84:  out <= 24'h5fff87;    	8'd148: out <= 24'hafd700;    	8'd212: out <= 24'hff87d7;
			8'd21: out <= 24'h0000ff;    		8'd85:  out <= 24'h5fffaf;    	8'd149: out <= 24'hafd75f;    	8'd213: out <= 24'hff87ff;
			8'd22: out <= 24'h005f00;    		8'd86:  out <= 24'h5fffd7;    	8'd150: out <= 24'hafd787;    	8'd214: out <= 24'hffaf00;
			8'd23: out <= 24'h005f5f;    		8'd87:  out <= 24'h5fffff;    	8'd151: out <= 24'hafd7af;    	8'd215: out <= 24'hffaf5f;
			8'd24: out <= 24'h005f87;    		8'd88:  out <= 24'h870000;    	8'd152: out <= 24'hafd7d7;    	8'd216: out <= 24'hffaf87;
			8'd25: out <= 24'h005faf;    		8'd89:  out <= 24'h87005f;    	8'd153: out <= 24'hafd7ff;    	8'd217: out <= 24'hffafaf;
			8'd26: out <= 24'h005fd7;    		8'd90:  out <= 24'h870087;    	8'd154: out <= 24'hafff00;    	8'd218: out <= 24'hffafd7;
			8'd27: out <= 24'h005fff;    		8'd91:  out <= 24'h8700af;    	8'd155: out <= 24'hafff5f;    	8'd219: out <= 24'hffafff;
			8'd28: out <= 24'h008700;    		8'd92:  out <= 24'h8700d7;    	8'd156: out <= 24'hafff87;    	8'd220: out <= 24'hffd700;
			8'd29: out <= 24'h00875f;    		8'd93:  out <= 24'h8700ff;    	8'd157: out <= 24'hafffaf;    	8'd221: out <= 24'hffd75f;
			8'd30: out <= 24'h008787;    		8'd94:  out <= 24'h875f00;    	8'd158: out <= 24'hafffd7;    	8'd222: out <= 24'hffd787;
			8'd31: out <= 24'h0087af;    		8'd95:  out <= 24'h875f5f;    	8'd159: out <= 24'hafffff;    	8'd223: out <= 24'hffd7af;
			8'd32: out <= 24'h0087d7;    		8'd96:  out <= 24'h875f87;    	8'd160: out <= 24'hd70000;    	8'd224: out <= 24'hffd7d7;
			8'd33: out <= 24'h0087ff;    		8'd97:  out <= 24'h875faf;    	8'd161: out <= 24'hd7005f;    	8'd225: out <= 24'hffd7ff;
			8'd34: out <= 24'h00af00;    		8'd98:  out <= 24'h875fd7;    	8'd162: out <= 24'hd70087;    	8'd226: out <= 24'hffff00;
			8'd35: out <= 24'h00af5f;    		8'd99:  out <= 24'h875fff;    	8'd163: out <= 24'hd700af;    	8'd227: out <= 24'hffff5f;
			8'd36: out <= 24'h00af87;    		8'd100: out <= 24'h878700;    	8'd164: out <= 24'hd700d7;    	8'd228: out <= 24'hffff87;
			8'd37: out <= 24'h00afaf;    		8'd101: out <= 24'h87875f;    	8'd165: out <= 24'hd700ff;    	8'd229: out <= 24'hffffaf;
			8'd38: out <= 24'h00afd7;    		8'd102: out <= 24'h878787;    	8'd166: out <= 24'hd75f00;    	8'd230: out <= 24'hffffd7;
			8'd39: out <= 24'h00afff;    		8'd103: out <= 24'h8787af;    	8'd167: out <= 24'hd75f5f;    	8'd231: out <= 24'hffffff;
			8'd40: out <= 24'h00d700;    		8'd104: out <= 24'h8787d7;    	8'd168: out <= 24'hd75f87;    	8'd232: out <= 24'h080808;
			8'd41: out <= 24'h00d75f;    		8'd105: out <= 24'h8787ff;    	8'd169: out <= 24'hd75faf;    	8'd233: out <= 24'h121212;
			8'd42: out <= 24'h00d787;    		8'd106: out <= 24'h87af00;    	8'd170: out <= 24'hd75fd7;    	8'd234: out <= 24'h1c1c1c;
			8'd43: out <= 24'h00d7af;    		8'd107: out <= 24'h87af5f;    	8'd171: out <= 24'hd75fff;    	8'd235: out <= 24'h262626;
			8'd44: out <= 24'h00d7d7;    		8'd108: out <= 24'h87af87;    	8'd172: out <= 24'hd78700;    	8'd236: out <= 24'h303030;
			8'd45: out <= 24'h00d7ff;    		8'd109: out <= 24'h87afaf;    	8'd173: out <= 24'hd7875f;    	8'd237: out <= 24'h3a3a3a;
			8'd46: out <= 24'h00ff00;    		8'd110: out <= 24'h87afd7;    	8'd174: out <= 24'hd78787;    	8'd238: out <= 24'h444444;
			8'd47: out <= 24'h00ff5f;    		8'd111: out <= 24'h87afff;    	8'd175: out <= 24'hd787af;    	8'd239: out <= 24'h4e4e4e;
			8'd48: out <= 24'h00ff87;    		8'd112: out <= 24'h87d700;    	8'd176: out <= 24'hd787d7;    	8'd240: out <= 24'h585858;
			8'd49: out <= 24'h00ffaf;    		8'd113: out <= 24'h87d75f;    	8'd177: out <= 24'hd787ff;    	8'd241: out <= 24'h626262;
			8'd50: out <= 24'h00ffd7;    		8'd114: out <= 24'h87d787;    	8'd178: out <= 24'hd7af00;    	8'd242: out <= 24'h6c6c6c;
			8'd51: out <= 24'h00ffff;    		8'd115: out <= 24'h87d7af;    	8'd179: out <= 24'hd7af5f;    	8'd243: out <= 24'h767676;
			8'd52: out <= 24'h5f0000;    		8'd116: out <= 24'h87d7d7;    	8'd180: out <= 24'hd7af87;    	8'd244: out <= 24'h808080;
			8'd53: out <= 24'h5f005f;    		8'd117: out <= 24'h87d7ff;    	8'd181: out <= 24'hd7afaf;    	8'd245: out <= 24'h8a8a8a;
			8'd54: out <= 24'h5f0087;    		8'd118: out <= 24'h87ff00;    	8'd182: out <= 24'hd7afd7;    	8'd246: out <= 24'h949494;
			8'd55: out <= 24'h5f00af;    		8'd119: out <= 24'h87ff5f;    	8'd183: out <= 24'hd7afff;    	8'd247: out <= 24'h9e9e9e;
			8'd56: out <= 24'h5f00d7;    		8'd120: out <= 24'h87ff87;    	8'd184: out <= 24'hd7d700;    	8'd248: out <= 24'ha8a8a8;
			8'd57: out <= 24'h5f00ff;    		8'd121: out <= 24'h87ffaf;    	8'd185: out <= 24'hd7d75f;    	8'd249: out <= 24'hb2b2b2;
			8'd58: out <= 24'h5f5f00;    		8'd122: out <= 24'h87ffd7;    	8'd186: out <= 24'hd7d787;    	8'd250: out <= 24'hbcbcbc;
			8'd59: out <= 24'h5f5f5f;    		8'd123: out <= 24'h87ffff;    	8'd187: out <= 24'hd7d7af;    	8'd251: out <= 24'hc6c6c6;
			8'd60: out <= 24'h5f5f87;    		8'd124: out <= 24'haf0000;    	8'd188: out <= 24'hd7d7d7;    	8'd252: out <= 24'hd0d0d0;
			8'd61: out <= 24'h5f5faf;    		8'd125: out <= 24'haf005f;    	8'd189: out <= 24'hd7d7ff;    	8'd253: out <= 24'hdadada;
			8'd62: out <= 24'h5f5fd7;    		8'd126: out <= 24'haf0087;    	8'd190: out <= 24'hd7ff00;    	8'd254: out <= 24'he4e4e4;
			8'd63: out <= 24'h5f5fff;    		8'd127: out <= 24'haf00af;    	8'd191: out <= 24'hd7ff5f;    	8'd255: out <= 24'h000000;
		endcase
	end

endmodule






