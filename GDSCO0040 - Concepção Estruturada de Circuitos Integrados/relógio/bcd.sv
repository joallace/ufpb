module bcd( input[3:0] bcd_bcd_in,
				output logic[6:0] bcd_display_out);
				
always_comb
	case(bcd_bcd_in)
		4'd0:bcd_display_out<=7'b1111110; 
		4'd1:bcd_display_out<=7'b0110000;
		4'd2:bcd_display_out<=7'b1101101;
		4'd3:bcd_display_out<=7'b1111001;
		4'd4:bcd_display_out<=7'b0110011;
		4'd5:bcd_display_out <= 7'b1011011;
		4'd6:bcd_display_out <= 7'b1011111;
		4'd7:bcd_display_out <= 7'b1110000;
		4'd8:bcd_display_out <= 7'b1111111;
		4'd9:bcd_display_out <= 7'b1111011;
		default: bcd_display_out <= 7'b0000000;
	endcase
endmodule