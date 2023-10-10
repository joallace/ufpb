module SAP(input clock, 
			  input reset,							//clear
			  input load_b,						//Lb
			  input Ea,
			  input load_out,						//Lo
			  output logic [7:0] output_reg);
			  
	logic [7:0] ram [15:0];
	logic [7:0] rem;
	logic [7:0] w_bus;
	logic [7:0] b_reg;
	
//	program_counter pc (.clock(clock), .reset(reset))
	
	always_ff @(posedge clock) begin
		if(~load_b)
			b_reg <= w_bus;
			
		if(Ea && ~load_out)
			output_reg <= w_bus;
	end
endmodule
