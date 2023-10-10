module controller(inout clock,
						input [3:0] instruction,
						output logic [11:0] control_word);

	logic [2:0] current_state;
	parameter t1 = 0, t2 = 1, t3 = 2, t4 = 3, t5 = 4, t6 = 5;
	parameter LDA = 4'b0000, ADD = 4'b0001, SUB = 4'b0010, OUT = 4'b1110, HALT = 4'b1111;
	const logic [11:0] NOP = 12'b001111100011;

	always_ff @(posedge clock) begin
			if(current_state == t6)
				current_state <= t1;
			else
				current_state = current_state + 1;
	end
	
	always_comb begin
		case(current_state)
			t1:
				control_word <= 12'b010111100011;
			t2:
				control_word <= 12'b101111100011;
			t3:
				control_word <= 12'b001001100011;
			t4:
				case(instruction)
					LDA, ADD, SUB:
						control_word <= 12'b000110100011;
					OUT:
						control_word <= 12'b001111110010;
					HALT:
						clock <= clock & 0;
				endcase
			t5:
				case(instruction)
					LDA:
						control_word <= 12'b001011000011;
					ADD, SUB:
						control_word <= 12'b001011100001;
					OUT:
						control_word <= NOP;
				endcase
			t6:
				case(instruction)
					ADD:
						control_word <= 12'b001111000111;
					SUB	:
						control_word <= 12'b001111001111;
					LDA, OUT:
						control_word <= NOP;
				endcase
		endcase
	end
endmodule
