library IEEE;
use IEEE.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use work.p_MI0.all;

entity forward_pipeline is
	port 	(
			clk:				in	std_logic;
			EX_RegRd:			in	std_logic_vector(4 downto 0);
			EX_rs:				in  std_logic_vector(4 downto 0);
			EX_rt:				in  std_logic_vector(4 downto 0);
			MEM_RegWrite:		in  std_logic;
			WB_RegWrite:		in  std_logic;
			MEM_RegRd:			in  std_logic_vector(4 downto 0);
			WB_RegRD:			in  std_logic_vector(4 downto 0);
			ID_MemWrite:		in	std_logic;
			EX_RegWrite:		in	std_logic;
			ID_rt:				in  std_logic_vector(4 downto 0);
			EX_forward_ctl_A:	out std_logic_vector(1 downto 0); 
			EX_forward_ctl_B:	out std_logic_vector(1 downto 0);
			ID_MemForward_ctl:	out std_logic
		);
end forward_pipeline;


architecture arq_forward_pipeline of forward_pipeline is

    --input			clk, EX_RegRd, EX_rs, EX_rt, MEM_RegWrite, WB_RegWrite, MEM_RegRd, WB_RegRd, ID_MemWrite, EX_RegWrite, ID_rt;
    --output[1:0]	EX_forward_ctl_A, EX_forward_ctl_B;
    --output		ID_MemForward_ctl;

begin
	process
    begin
    	wait until rising_edge(clk);
    	wait for 50 ns; -- Delay evita forward em estágios c/ bolhas
		-- FORWARD REGISTRADOR A
		if ((MEM_RegRd /= "00000") and (MEM_RegWrite = '1') and (MEM_RegRd = EX_rs)) then
			EX_forward_ctl_A	<= "10";
		else if ((WB_RegRd /= "00000") and (WB_RegWrite = '1') and (MEM_RegRd /= EX_rs) and (WB_RegRd = EX_rs)) then
				 EX_forward_ctl_A	<= "01";
	    	 else
	    		 EX_forward_ctl_A	<= "00";
	    	 end if;
	    end if;
		-- FORWARD REGISTRADOR B
		if ((MEM_RegRd /= "00000") and (MEM_RegWrite = '1') and (MEM_RegRd = EX_rt)) then
			EX_forward_ctl_B	<= "10";
		else if ((WB_RegRd /= "00000") and (WB_RegWrite = '1') and (MEM_RegRd /= EX_rt) and (WB_RegRd = EX_rt))	then
				 EX_forward_ctl_B	<= "01";
			 else
		   		 EX_forward_ctl_B	<= "00";
		   	 end if;
		end if;
		-- FORWARD COPIA DE MEMORIA (LW NO ESTAGIO EX E SW NO ESTAGIO ID P/ EVITAR STALL)
		if ((ID_rt /= "00000") and (ID_MemWrite = '1') and (EX_RegWrite = '1')  and (EX_RegRd = ID_rt)) then
			ID_MemForward_ctl	<= '1';
		else
			ID_MemForward_ctl	<= '0';
		end if;
	end process;

end arq_forward_pipeline;
