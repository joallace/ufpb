module program_counter(input clock,
							  input reset,
							  input output_to_bus,  //Ep
							  input increment,		//Cp
							  output [3:0] address);

	always_ff @(negedge clock or negedge reset) begin
		if(~reset)
			address <= 0;
			
		else if(increment)
			address <= address + 1;
	end	
endmodule
