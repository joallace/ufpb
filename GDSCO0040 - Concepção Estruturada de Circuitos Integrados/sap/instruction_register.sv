module instruction_register(input clock,
									 input reset,
									 input output_to_bus,			//Ei
									 input load_ir,				   //Su (0 = sum, 1 = sub)
									 output wire [3:0] instruction,
									 output logic [7:0] w_bus);
			 
	logic [7:0] i_reg;
	
	assign instruction = i_reg[7:4];
	
	always_ff @(posedge clock or posedge reset) begin
		if(reset)
			i_reg <= 8'bz;
		else begin
			if(~load_ir)
				i_reg <= w_bus;
			else
				i_reg <= i_reg;
				
			if(~output_to_bus)
				w_bus <= {4'b0, i_reg[3:0]};
			else
				w_bus <= 8'bz;
		end
	end	
endmodule
	