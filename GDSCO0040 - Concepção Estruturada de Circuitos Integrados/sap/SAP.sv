module SAP(input clock, 
			  input reset,
			  output logic [7:0] binary_out)
			  
logic [7:0] ram [15:0]
wire [7:0] w_bus

