library IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use work.p_MI0.all;

entity stall_pipeline is
	port 	(
			ID_MemForward_ctl:	in	std_logic;
			EX_MemRead:			in  std_logic;
			EX_rt:				in  std_logic_vector(4 downto 0);
			ID_rt:				in  std_logic_vector(4 downto 0);
			ID_rs:				in  std_logic_vector(4 downto 0);
			ID_stall:			out std_logic
			);
end stall_pipeline;


architecture arq_stall_pipeline of stall_pipeline is



    --input			ID_MemForward_ctl, EX_MemRead;
    --input[4:0]	EX_rt, ID_rt, ID_rs;
    --output		ID_stall;

begin
   
    process (ID_MemForward_ctl, EX_MemRead, EX_rt, ID_rt, ID_rs)
    begin

    	-- Detector de hazard/stall - O forward da copia de memoria dispensa a necessidade do stall, e por isso, ID_MemForward_ctl o inibe
       		if ((ID_MemForward_ctl = '0') and (EX_MemRead = '1')) then
       			if ((EX_rt = ID_rt) or (EX_rt = ID_rs)) then
        			ID_stall <= '1';
       			else
					ID_stall <= '0';
        		end if;
        	end if;

    end process;

end arq_stall_pipeline;
