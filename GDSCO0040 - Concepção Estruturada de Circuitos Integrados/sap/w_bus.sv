module bus (input clock,
				input pc_to_bus,			// Ep
				input ram_to_bus,			// Ce
				input ir_to_bus,			// Ei
				input a_to_bus,			// Ea
				input ula_to_bus,	// Eu
				input [3:0] pc,
				input [7:0] ram,
				input [3:0] ir,
				input [7:0] acc,
				input [7:0] ula,
				output logic [7:0] w_bus);

always_comb begin
	if(pc_to_bus)
		w_bus = {4'b0, pc};
	else if(~ram_to_bus)
		w_bus = ram;
	else if(~ir_to_bus)
		w_bus = {4'b0, ir};
	else if(a_to_bus)
		w_bus = acc;
	else if(ula_to_bus)
		w_bus = ula;
	else
		w_bus = 8'b0;
end

endmodule
