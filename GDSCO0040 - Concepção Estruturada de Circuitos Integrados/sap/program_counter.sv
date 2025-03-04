module program_counter(input clock,
							  input reset,
							  input output_to_bus,  //Ep
							  input increment,		//Cp
							  input wire [7:0] w_bus,
							  output wire [3:0] out);

	logic [3:0] address;

	assign out = address;
	
	always_ff @(posedge clock or posedge reset) begin
		if(reset)
			address <= 4'b0;
		else begin
			if(increment)
				address <= address + 1;
			else
				address <= address;
		end
	end	
endmodule
