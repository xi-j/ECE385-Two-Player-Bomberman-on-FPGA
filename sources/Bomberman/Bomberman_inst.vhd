	component Bomberman is
		port (
			audio_back_vol_export     : out   std_logic_vector(7 downto 0);                     -- export
			audio_bomb_active_export  : out   std_logic;                                        -- export
			audio_bomb_vol_export     : out   std_logic_vector(2 downto 0);                     -- export
			audio_init_export         : out   std_logic;                                        -- export
			audio_init_f_export       : in    std_logic                     := 'X';             -- export
			audio_select_export       : out   std_logic_vector(2 downto 0);                     -- export
			clk_clk                   : in    std_logic                     := 'X';             -- clk
			export_data_new_signal    : out   std_logic_vector(8 downto 0);                     -- new_signal
			export_data_new_signal_1  : out   std_logic_vector(31 downto 0);                    -- new_signal_1
			export_data_new_signal_2  : out   std_logic_vector(63 downto 0);                    -- new_signal_2
			export_data_new_signal_3  : in    std_logic                     := 'X';             -- new_signal_3
			export_data_new_signal_4  : out   std_logic;                                        -- new_signal_4
			led_wire_export           : out   std_logic_vector(7 downto 0);                     -- export
			otg_hpi_address_export    : out   std_logic_vector(1 downto 0);                     -- export
			otg_hpi_cs_export         : out   std_logic;                                        -- export
			otg_hpi_data_in_port      : in    std_logic_vector(15 downto 0) := (others => 'X'); -- in_port
			otg_hpi_data_out_port     : out   std_logic_vector(15 downto 0);                    -- out_port
			otg_hpi_r_export          : out   std_logic;                                        -- export
			otg_hpi_reset_export      : out   std_logic;                                        -- export
			otg_hpi_w_export          : out   std_logic;                                        -- export
			player1score0_wire_export : out   std_logic_vector(3 downto 0);                     -- export
			player1score1_wire_export : out   std_logic_vector(3 downto 0);                     -- export
			player2score0_wire_export : out   std_logic_vector(3 downto 0);                     -- export
			player2score1_wire_export : out   std_logic_vector(3 downto 0);                     -- export
			reset_reset_n             : in    std_logic                     := 'X';             -- reset_n
			sdram_pll_clk             : out   std_logic;                                        -- clk
			sdram_wire_addr           : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba             : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n          : out   std_logic;                                        -- cas_n
			sdram_wire_cke            : out   std_logic;                                        -- cke
			sdram_wire_cs_n           : out   std_logic;                                        -- cs_n
			sdram_wire_dq             : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm            : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_wire_ras_n          : out   std_logic;                                        -- ras_n
			sdram_wire_we_n           : out   std_logic;                                        -- we_n
			timescreen0_wire_export   : out   std_logic_vector(3 downto 0);                     -- export
			timescreen1_wire_export   : out   std_logic_vector(3 downto 0);                     -- export
			timescreen2_wire_export   : out   std_logic_vector(3 downto 0);                     -- export
			boot_up_export            : in    std_logic                     := 'X'              -- export
		);
	end component Bomberman;

	u0 : component Bomberman
		port map (
			audio_back_vol_export     => CONNECTED_TO_audio_back_vol_export,     --     audio_back_vol.export
			audio_bomb_active_export  => CONNECTED_TO_audio_bomb_active_export,  --  audio_bomb_active.export
			audio_bomb_vol_export     => CONNECTED_TO_audio_bomb_vol_export,     --     audio_bomb_vol.export
			audio_init_export         => CONNECTED_TO_audio_init_export,         --         audio_init.export
			audio_init_f_export       => CONNECTED_TO_audio_init_f_export,       --       audio_init_f.export
			audio_select_export       => CONNECTED_TO_audio_select_export,       --       audio_select.export
			clk_clk                   => CONNECTED_TO_clk_clk,                   --                clk.clk
			export_data_new_signal    => CONNECTED_TO_export_data_new_signal,    --        export_data.new_signal
			export_data_new_signal_1  => CONNECTED_TO_export_data_new_signal_1,  --                   .new_signal_1
			export_data_new_signal_2  => CONNECTED_TO_export_data_new_signal_2,  --                   .new_signal_2
			export_data_new_signal_3  => CONNECTED_TO_export_data_new_signal_3,  --                   .new_signal_3
			export_data_new_signal_4  => CONNECTED_TO_export_data_new_signal_4,  --                   .new_signal_4
			led_wire_export           => CONNECTED_TO_led_wire_export,           --           led_wire.export
			otg_hpi_address_export    => CONNECTED_TO_otg_hpi_address_export,    --    otg_hpi_address.export
			otg_hpi_cs_export         => CONNECTED_TO_otg_hpi_cs_export,         --         otg_hpi_cs.export
			otg_hpi_data_in_port      => CONNECTED_TO_otg_hpi_data_in_port,      --       otg_hpi_data.in_port
			otg_hpi_data_out_port     => CONNECTED_TO_otg_hpi_data_out_port,     --                   .out_port
			otg_hpi_r_export          => CONNECTED_TO_otg_hpi_r_export,          --          otg_hpi_r.export
			otg_hpi_reset_export      => CONNECTED_TO_otg_hpi_reset_export,      --      otg_hpi_reset.export
			otg_hpi_w_export          => CONNECTED_TO_otg_hpi_w_export,          --          otg_hpi_w.export
			player1score0_wire_export => CONNECTED_TO_player1score0_wire_export, -- player1score0_wire.export
			player1score1_wire_export => CONNECTED_TO_player1score1_wire_export, -- player1score1_wire.export
			player2score0_wire_export => CONNECTED_TO_player2score0_wire_export, -- player2score0_wire.export
			player2score1_wire_export => CONNECTED_TO_player2score1_wire_export, -- player2score1_wire.export
			reset_reset_n             => CONNECTED_TO_reset_reset_n,             --              reset.reset_n
			sdram_pll_clk             => CONNECTED_TO_sdram_pll_clk,             --          sdram_pll.clk
			sdram_wire_addr           => CONNECTED_TO_sdram_wire_addr,           --         sdram_wire.addr
			sdram_wire_ba             => CONNECTED_TO_sdram_wire_ba,             --                   .ba
			sdram_wire_cas_n          => CONNECTED_TO_sdram_wire_cas_n,          --                   .cas_n
			sdram_wire_cke            => CONNECTED_TO_sdram_wire_cke,            --                   .cke
			sdram_wire_cs_n           => CONNECTED_TO_sdram_wire_cs_n,           --                   .cs_n
			sdram_wire_dq             => CONNECTED_TO_sdram_wire_dq,             --                   .dq
			sdram_wire_dqm            => CONNECTED_TO_sdram_wire_dqm,            --                   .dqm
			sdram_wire_ras_n          => CONNECTED_TO_sdram_wire_ras_n,          --                   .ras_n
			sdram_wire_we_n           => CONNECTED_TO_sdram_wire_we_n,           --                   .we_n
			timescreen0_wire_export   => CONNECTED_TO_timescreen0_wire_export,   --   timescreen0_wire.export
			timescreen1_wire_export   => CONNECTED_TO_timescreen1_wire_export,   --   timescreen1_wire.export
			timescreen2_wire_export   => CONNECTED_TO_timescreen2_wire_export,   --   timescreen2_wire.export
			boot_up_export            => CONNECTED_TO_boot_up_export             --            boot_up.export
		);

