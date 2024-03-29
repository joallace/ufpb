module instruction_register(input clock,
									 input reset,
									 input output_to_bus,			//Ei
									 input load_ir,				   //Su (0 = sum, 1 = sub)
									 output wire [3:0] instruction,
									 input wire [7:0] w_bus,
									 output wire [7:0] out);
			 
	logic [7:0] i_reg;
	
	assign instruction = i_reg[7:4];
	assign out = i_reg;
	
	always_ff @(posedge clock or posedge reset) begin
		if(reset)
			i_reg <= 8'b0;
		else if(~load_ir)
			i_reg <= w_bus;
	end	
endmodule
	