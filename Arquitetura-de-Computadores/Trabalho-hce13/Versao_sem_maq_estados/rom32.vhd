library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use work.p_MI0.all;



entity rom32 is
	port (
		address: in reg32;
		data_out: out reg32
	);
end rom32;

architecture arq_rom32 of rom32 is

	signal mem_offset: std_logic_vector(5 downto 0);
	signal address_select: std_logic;

begin
	mem_offset <= address(7 downto 2);
        
	add_sel: process(address)
	begin
		if address(31 downto 8) = x"000000" then 	
			address_select <= '1';
		else
			address_select <= '0';
		end if;
	end process;

	access_rom: process(address_select, mem_offset)
	begin
		if address_select = '1' then
			case mem_offset is
				when 	"000000" => data_out <= "111110" & "00000" & "00001" & x"0001"; -- lui $1, 1
				when 	"000001" => data_out <= "101011" & "00000" & "00001" & x"0000"; -- sw $1, 0($0) - Forward do MEM
				when 	"000010" => data_out <= "100101" & "00000" & "00010" & x"0000"; -- lw $2, 0($0) - Bolha entre este e o seguinte
				when 	"000011" => data_out <= "111111" & "00010" & "00000" & "00010" & "00000" & "000000"; -- addm $2, $0, $2
				when 	others  => data_out <= (others => 'X');
			end case;
    		end if;
  	end process; 

end arq_rom32;
