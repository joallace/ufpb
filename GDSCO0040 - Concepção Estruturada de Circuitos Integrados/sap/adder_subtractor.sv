module adder_subtractor(input output_to_bus,		//Eu
								input mode,				   //Su (0 = sum, 1 = sub)
								input [7:0] a,
								input [7:0] b,
								output logic [7:0] out);

	always_comb
		if(mode)
			out = a - b;
		else
			out = a + b;
endmodule
