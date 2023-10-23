module SAP(input clock, 
//			  input reset,							//clear					
			  output logic [7:0] output_reg);
			  
   wire [11:0] control_word;
	logic increment_pc,		// Cp
			pc_to_bus,			// Ep
			load_mem,			// Lm
			ram_to_bus,			// Ce
			load_ir,				// Li
			ir_to_bus,			// Ei
			load_a,				// La
			a_to_bus,			// Ea
			operation,			// Su
			ula_to_bus,			// Eu
			load_b,				// Lb
			load_out;			// Lo
	logic [7:0] ram [15:0];
	logic [7:0] rem;
	logic [7:0] w_bus;
	logic [7:0] b_reg;
	
	wire [7:0] ula_input;
	wire [3:0] instruction;
	
	logic reset;

	initial begin
		reset = 1;
		reset = 0;
		
		ram = '{8'b00001111,
				  8'b00011110,
				  8'b00011101,
				  8'b00101100,
				  8'b1110xxxx,
				  8'b1111xxxx,
				  8'b0,
				  8'b0,
				  8'b0,
				  8'b0,
				  8'b0,
				  8'b0,
				  8'b00000110,
				  8'b00000010,
				  8'b00001000,
				  8'b00001010};
	end
	
	program_counter pc (.clock(clock), .reset(reset), .output_to_bus(pc_to_bus), .increment(increment_pc), .w_bus(w_bus));
	
	controller ctrlr (.clock(clock), .instruction(instruction), .control_word(control_word));
	
	accumulator acc (.clock(clock), .output_to_bus(a_to_bus), .load_a(load_a), .ula_input(ula_input), .w_bus(w_bus));
	
	adder_subtractor ula (.output_to_bus(ula_to_bus), .mode(operation), .a(ula_input), .b(b_reg), .w_bus(w_bus));
	
	instruction_register ir (.clock(clock), .reset(reset), .output_to_bus(ir_to_bus), .load_ir(load_ir), .instruction(instruction), .w_bus(w_bus));
	
	assign {increment_pc, pc_to_bus, load_mem, ram_to_bus, load_ir, ir_to_bus, load_a, a_to_bus, operation, ula_to_bus, load_b, load_out} = control_word;

	always_ff @(posedge clock) begin
		if(~load_mem)
			rem <= w_bus[3:0];
		else
			rem <= rem;
			
		if(ram_to_bus)
			w_bus <= ram[rem];
		else
			w_bus <= 8'bz;
	
		if(~load_b)
			b_reg <= w_bus;
		else
			b_reg <= b_reg;
			
		if(~load_out)
			output_reg <= w_bus;
		else
			output_reg <= 8'bz;
	end
endmodule
