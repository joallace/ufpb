module instruction_register(input clock,
									 input reset,
									 input output_to_bus,		//Ei
									 input load_i,				   //Su (0 = sum, 1 = sub)
									 inout logic [7:0] w_bus)
			 
	logic [7:0] ir;

	always_ff @(posedge clock or negedge reset) begin
		if(~reset)
			ir <= 0;
		if(output_to_bus)
			w_bus <= ir[3:0];
		if(load_i)
			ir <= w_bus;
	end	
endmodule
	