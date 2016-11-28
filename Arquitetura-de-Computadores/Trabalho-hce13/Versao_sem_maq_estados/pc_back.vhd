library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use work.p_MI0.all;

entity pc_back is
       	   	port( 
				IF_pc:			in	reg32;
				ID_stall:		in	std_logic;
				IF_pc_stall :   out reg32
           		);
end pc_back;

architecture pc_back_arq of pc_back is 

begin
	process(IF_pc, ID_stall)
	begin
		if ID_stall = '1' then
			IF_pc_stall		<=	IF_pc - x"00000004";
		else
			IF_pc_stall		<=	IF_pc;
		end if;
	end process;
end pc_back_arq;
