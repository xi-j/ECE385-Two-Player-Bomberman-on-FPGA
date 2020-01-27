
module Bomberman (
	audio_back_vol_export,
	audio_bomb_active_export,
	audio_bomb_vol_export,
	audio_init_export,
	audio_init_f_export,
	audio_select_export,
	clk_clk,
	export_data_new_signal,
	export_data_new_signal_1,
	export_data_new_signal_2,
	export_data_new_signal_3,
	export_data_new_signal_4,
	led_wire_export,
	otg_hpi_address_export,
	otg_hpi_cs_export,
	otg_hpi_data_in_port,
	otg_hpi_data_out_port,
	otg_hpi_r_export,
	otg_hpi_reset_export,
	otg_hpi_w_export,
	player1score0_wire_export,
	player1score1_wire_export,
	player2score0_wire_export,
	player2score1_wire_export,
	reset_reset_n,
	sdram_pll_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	timescreen0_wire_export,
	timescreen1_wire_export,
	timescreen2_wire_export,
	boot_up_export);	

	output	[7:0]	audio_back_vol_export;
	output		audio_bomb_active_export;
	output	[2:0]	audio_bomb_vol_export;
	output		audio_init_export;
	input		audio_init_f_export;
	output	[2:0]	audio_select_export;
	input		clk_clk;
	output	[8:0]	export_data_new_signal;
	output	[31:0]	export_data_new_signal_1;
	output	[63:0]	export_data_new_signal_2;
	input		export_data_new_signal_3;
	output		export_data_new_signal_4;
	output	[7:0]	led_wire_export;
	output	[1:0]	otg_hpi_address_export;
	output		otg_hpi_cs_export;
	input	[15:0]	otg_hpi_data_in_port;
	output	[15:0]	otg_hpi_data_out_port;
	output		otg_hpi_r_export;
	output		otg_hpi_reset_export;
	output		otg_hpi_w_export;
	output	[3:0]	player1score0_wire_export;
	output	[3:0]	player1score1_wire_export;
	output	[3:0]	player2score0_wire_export;
	output	[3:0]	player2score1_wire_export;
	input		reset_reset_n;
	output		sdram_pll_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[3:0]	timescreen0_wire_export;
	output	[3:0]	timescreen1_wire_export;
	output	[3:0]	timescreen2_wire_export;
	input		boot_up_export;
endmodule
