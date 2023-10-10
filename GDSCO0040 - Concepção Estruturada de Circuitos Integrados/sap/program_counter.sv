module program_counter(input clock,
							  input reset,
							  input output_to_bus,  //Ep
							  input increment,		//Cp
							  output logic [3:0] w_bus)

	  
	logic [3:0] address

	always_ff @(negedge clock) begin
		if(output_to_bus)
			w_bus <= address;
		if(increment)
			address <= address + 1;
	end	
endmodule
