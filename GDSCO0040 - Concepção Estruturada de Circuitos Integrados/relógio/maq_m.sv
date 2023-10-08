module maq_m (	input maqm_clock,
					input maqm_reset,
					input inc_minuto,
					output [3:0] maqm_lsd,
					output [2:0] maqm_msd,
					output maqm_inc_hora);

	always_ff @(posedge maqm_clock or negedge maqm_reset)
		if (!maqm_reset)
			maqm_lsd <= 4'd0;
		else begin
			if(inc_minuto)
				if (maqm_lsd == 4'd9)
					maqm_lsd <= 4'd0;
				else
					maqm_lsd <= maqm_lsd + 4'd1;			
			else
				maqm_lsd <= maqm_lsd;
		end
				
	always_ff @(posedge maqm_clock or negedge maqm_reset)
		if (!maqm_reset)
			maqm_msd <= 3'd0;
		else begin
			if(inc_minuto) begin
				if (maqm_lsd == 4'd9 && maqm_msd == 3'd5)
					maqm_msd <= 3'd0;
				else begin
					if (maqm_lsd==4'd9)
						maqm_msd <= maqm_msd + 3'd1;
					else
						maqm_msd <= maqm_msd;
				end
			end
		end
					
	always_comb
		maqm_inc_hora <= (maqm_msd == 3'd5 && maqm_lsd == 4'd9);
	
	
endmodule
