module adder_subtractor(input output_to_bus,		//Eu
								input mode,				   //Su (0 = sum, 1 = sub)
								input [7:0] a,
								input [7:0] b,
								output [7:0] result);

	always_comb
		if(output_to_bus)
			if(mode)
				result = a + b;
			else
				result = a - b;
		else
			result = 8'bz;
endmodule
