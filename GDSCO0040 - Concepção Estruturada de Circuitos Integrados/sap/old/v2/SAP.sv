module SAP(input clock, 
//			  input reset,							//clear					
			  output logic [7:0] output_reg);
			  
   logic [11:0] control_word;
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
	logic [7:0] a_reg;
	logic [7:0] i_reg;
	
	logic reset;
	
	wire [7:0] ula_result;
	wire [3:0] current_address;

	initial begin
		reset = 1;
		reset = 0;
	end

	
	bus w (.clock(clock), .pc_to_bus(pc_to_bus), .ram_to_bus(ram_to_bus), .ir_to_bus(ir_to_bus),
			 .a_to_bus(a_to_bus), .ula_to_bus(ula_to_bus), .pc(current_address), .ram(ram[1]), .ir(i_reg[3:0]), .acc(a_reg), .ula(ula_result), .w_bus(w_bus));
	
	program_counter pc (.clock(clock), .reset(reset), .output_to_bus(pc_to_bus), .increment(increment_pc), .address(current_address));
	
	controller ctrlr (.clock(clock), .instruction(i_reg[7:4]), .control_word(control_word));
	
	adder_subtractor ula (.output_to_bus(ula_to_bus), .mode(operation), .a(a_reg), .b(b_reg), .result(ula_result));

	assign {increment_pc, pc_to_bus, load_mem, ram_to_bus, load_ir, ir_to_bus, load_a, a_to_bus, operation, ula_to_bus, load_b, load_out} = control_word;
	
	always_ff @(posedge clock) begin
		if(reset)
			i_reg <= 8'bz;
			
		if(~load_a)
			a_reg <= w_bus;
			
		if(~load_b)
			b_reg <= w_bus;
			
		if(~load_ir)
			i_reg <= w_bus;
			
		if(~load_out)
			output_reg <= w_bus;
	end
endmodule
