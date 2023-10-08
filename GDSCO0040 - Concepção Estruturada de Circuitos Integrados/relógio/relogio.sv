module relogio (input clock, 
                      input reset, 
                      output logic [6:0] s_lsd,
                      output logic [6:0] s_msd,
                      output logic [6:0] m_lsd,
                      output logic [6:0] m_msd,
                      output logic [6:0] h_lsd,
                      output logic [6:0] h_msd);

							 
logic enable1hz;

enable_clock meuhabilitador (.clk_in(clock), .rst(reset), .clk_out(enable1hz));

logic [3:0] bcd_s_lsd;
logic [2:0] bcd_s_msd;
logic incrementa_minuto;

maq_s maqs_display_s(.maqs_clock(clock), .maqs_reset(reset), .maqs_lsd(bcd_s_lsd), .maqs_msd(bcd_s_msd), .maqs_inc_minuto(incrementa_minuto));

bcd display_s_lsd(.bcd_bcd_in(bcd_s_lsd), .bcd_display_out(s_lsd));

bcd display_s_msd(.bcd_bcd_in({1'b0, bcd_s_msd}), .bcd_display_out(s_msd));

logic [3:0] bcd_m_lsd;
logic [2:0] bcd_m_msd;
logic incrementa_hora;

maq_m maqm_display_m(.maqm_clock(clock), .maqm_reset(reset), .inc_minuto(incrementa_minuto), .maqm_lsd(bcd_m_lsd), .maqm_msd(bcd_m_msd), .maqm_inc_hora(incrementa_hora));

bcd display_m_lsd(.bcd_bcd_in(bcd_m_lsd), .bcd_display_out(m_lsd));

bcd display_m_msd(.bcd_bcd_in({1'b0, bcd_m_msd}), .bcd_display_out(m_msd));

logic [3:0] bcd_h_lsd;
logic [2:0] bcd_h_msd;

maq_h maqm_display_h(.maqh_clock(clock), .maqh_reset(reset), .inc_minuto(incrementa_minuto) ,.inc_hora(incrementa_hora), .maqh_lsd(bcd_h_lsd), .maqh_msd(bcd_h_msd));

bcd display_h_lsd(.bcd_bcd_in(bcd_h_lsd), .bcd_display_out(h_lsd));

bcd display_h_msd(.bcd_bcd_in({2'b0, bcd_h_msd}), .bcd_display_out(h_msd));


endmodule