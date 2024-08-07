module accumulator(input clock,
						 input output_to_bus,		// Ea
						 input load_a,					// La
						 output wire [7:0] ula_input,
						 input wire [7:0] w_bus);
						 
	logic [7:0] a_reg;
	
	assign ula_input = a_reg;
						 
	always_ff @(posedge clock) begin
		if(~load_a)
			a_reg <= w_bus;
		else
			a_reg <= a_reg;
	end	
						 
endmodule
