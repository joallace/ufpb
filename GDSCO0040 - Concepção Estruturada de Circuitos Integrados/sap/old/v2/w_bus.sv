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

always_ff @(posedge clock) begin
	if(pc_to_bus)
		w_bus <= {4'bz, pc};
	else if(~ram_to_bus)
		w_bus <= ram;
	else if(~ir_to_bus)
		w_bus <= {4'bz, ir};
	else if(a_to_bus)
		w_bus <= acc;
	else if(ula_to_bus)
		w_bus <= ula;
	else
		w_bus = w_bus;
end

endmodule
