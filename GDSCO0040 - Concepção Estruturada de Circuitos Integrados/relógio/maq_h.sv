module maq_h (
    input maqh_clock,
    input maqh_reset,
    input inc_hora,
	 input inc_minuto,
    output [3:0] maqh_lsd,
    output [2:0] maqh_msd
);

	always_ff @(posedge maqh_clock or negedge maqh_reset) begin
		  if (!maqh_reset) begin
				maqh_lsd <= 4'd0;
				maqh_msd <= 3'd0;
		  end
		  else begin
				if (inc_hora && inc_minuto)  begin
					if(maqh_msd == 3'd2 && maqh_lsd == 4'd3)begin
						maqh_lsd <= 4'd0;
						maqh_msd <= 3'd0;
					end
					else begin
						 if (maqh_lsd == 4'd9) begin
							  maqh_lsd <= 4'd0;
							  if (maqh_msd == 3'd2)
									maqh_msd <= 3'd0;
							  else
									maqh_msd <= maqh_msd + 3'd1;
						 end
						 else
							  maqh_lsd <= maqh_lsd + 4'd1;
					end
				end
		  end
	 end

endmodule
