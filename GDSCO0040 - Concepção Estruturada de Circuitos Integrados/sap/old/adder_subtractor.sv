module adder_subtractor(input output_to_bus,		//Eu
								input mode,				   //Su (0 = sum, 1 = sub)
								input [7:0] a,
								input [7:0] b,
								output logic [7:0] w_bus);

	always_comb
		if(output_to_bus)
			if(mode)
				w_bus = a + b;
			else
				w_bus = a - b;
		else
			w_bus = 8'bz;
endmodule
