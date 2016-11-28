library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use work.p_MI0.all;

entity mux3 is generic(size: integer := 32);
		port(
				sel: in std_logic_vector(1 downto 0);
				a, b, c: in std_logic_vector(size-1 downto 0);
				f: out std_logic_vector(size-1 downto 0)
			);
end mux3;

architecture arq_mux3 of mux3 is

begin

    M: process(a, b, c, sel)
    
	begin
		case sel is

          	when "00" 	   => f <= a;
          	
          	when "01" 	   => f <= b;
          	
          	when others    => f <= c;

		end case;
	end process;

end arq_mux3;

