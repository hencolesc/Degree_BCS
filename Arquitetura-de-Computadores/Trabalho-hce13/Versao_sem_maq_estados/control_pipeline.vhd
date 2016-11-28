library IEEE;
use IEEE.std_logic_1164.all;
use work.p_MI0.all;

entity control_pipeline is
	port 	(
			ID_stall:	in  std_logic;
			opcode:		in  std_logic_vector(5 downto 0);
		 	RegDst:		out std_logic_vector(1 downto 0);
			ALUSrc:		out std_logic; 
			MemtoReg:	out std_logic_vector(1 downto 0);
			RegWrite:	out std_logic; 
			MemRead:	out std_logic; 
			MemWrite:	out std_logic; 
			Branch:		out std_logic; 
			ALUOp:		out std_logic_vector(2 downto 0)
		);
end control_pipeline;


architecture arq_control_pipeline of control_pipeline is

	signal opcode_stall: std_logic_vector(5 downto 0); -- Permite transformaçao da inst. no ID p/ bolha caso ID_stall = '1'

    --input		[5:0] opcode;
    --input		ID_stall;
    --output	RegWrite, MemRead, MemWrite, Branch, ALUSrc;
    --output	[1:0] ALUOp, MemtoReg, RegDst;
    --reg		RegWrite, MemRead, MemWrite, Branch, ALUSrc;
    --reg		[1:0] ALUOp, MemtoReg, RegDst;

begin
    process (ID_stall, opcode)
    begin
			if ID_stall = '1' then
				opcode_stall <= BOLHA;	-- Instrução vira bolha
			else
				opcode_stall <= opcode;
			end if;
    end process;

    process (opcode_stall)
    begin
        case opcode_stall is
        when R_FORMAT	=>	RegDst <= "01"; ALUSrc <= '0'; MemtoReg <= "00"; RegWrite <='1'; MemRead<='0'; MemWrite<='0'; Branch<='0'; ALUOp <= "010";	-- R type / NOP
        when LW			=>	RegDst <= "00"; ALUSrc <= '1'; MemtoReg <= "01"; RegWrite <='1'; MemRead<='1'; MemWrite<='0'; Branch<='0'; ALUOp <= "000";	-- LW
		when SW			=>	RegDst <= "XX"; ALUSrc <= '1'; MemtoReg <= "XX"; RegWrite <='0'; MemRead<='0'; MemWrite<='1'; Branch<='0'; ALUOp <= "000";	-- SW
		when BEQ		=>	RegDst <= "XX"; ALUSrc <= '0'; MemtoReg <= "XX"; RegWrite <='0'; MemRead<='0'; MemWrite<='0'; Branch<='1'; ALUOp <= "001";	-- BEQ
		when LUI		=>	RegDst <= "00"; ALUSrc <= '1'; MemtoReg <= "00"; RegWrite <='1'; MemRead<='0'; MemWrite<='0'; Branch<='0'; ALUOp <= "011";	-- LUI
		when ADDM		=>	RegDst <= "01"; ALUSrc <= '0'; MemtoReg <= "10"; RegWrite <='1'; MemRead<='1'; MemWrite<='0'; Branch<='0'; ALUOp <= "101";	-- ADDM
		when others		=>	RegDst <= "10"; ALUSrc <= '0'; MemtoReg <= "00"; RegWrite <='0'; MemRead<='0'; MemWrite<='0'; Branch<='0'; ALUOp <= "000";	-- Instruções inválidas / Bolha / Etecetera
	end case;
    end process;

end arq_control_pipeline;
