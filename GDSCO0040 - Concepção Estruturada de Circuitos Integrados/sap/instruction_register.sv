module instruction_register(input clock,
									 input reset,
									 input output_to_bus,		//Ei
									 input load_ir,				   //Su (0 = sum, 1 = sub)
									 output logic [3:0] instruction,
									 inout logic [7:0] w_bus);
			 
	logic [7:0] i_reg;

	always_ff @(posedge clock or posedge reset) begin
		if(reset)
			i_reg <= 0;
			
		if(output_to_bus)
			w_bus <= i_reg[3:0];
			
		if(load_ir)
			i_reg <= w_bus;
			
		instruction <= i_reg[7:4];
	end	
endmodule
	