-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- UFPR, BCC, ci210                        autor: Roberto Hexsel, 17nov2012
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- multiplica por 1
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
library IEEE; use IEEE.std_logic_1164.all; use work.p_wires.all;

entity m_p_1 is
  port(A,B : in  reg16;                 -- entradas A,B
       S : in bit;                      -- bit por multiplicar
       R : out reg17);                  -- produto parcial
end m_p_1;

architecture funcional of m_p_1 is 

  component adderAdianta16 is port(inpA, inpB : in bit_vector;
                          outC : out bit_vector;
                          vem  : in  bit;
                          vai  : out bit);
  end component adderAdianta16;

  signal somaAB : reg17;

begin

  U_soma: adderAdianta16
    port map(A, B , somaAB(15 downto 0), '0', somaAB(16)); 

  -- defina a constante t_mux2 em packageWires.vhd
  R <= somaAB when S = '1' else ('0' & B) after t_mux2;

end funcional;
-- -------------------------------------------------------------------


-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- multiplicador combinacional
-- +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
library IEEE; use IEEE.std_logic_1164.all; use work.p_wires.all;

entity mult16x16 is
  port(A, B : in  reg16;   -- entradas A,B
       prod : out reg32);  -- produto
end mult16x16;

architecture estrutural of mult16x16 is 

  component m_p_1 is port(A,B : in  bit_vector;   -- reg16
                          S   : in  bit;
                          R   : out bit_vector);  -- reg17
  end component m_p_1;

  signal p01,p02,p03,p04,p05,p06,p07,p08: reg17;
  signal p09,p10,p11,p12,p13,p14,p15,p16: reg17;

begin

  -- U_00: m_p_1( , , , );
  -- U_01: m_p_1( , , , );
  -- U_02: m_p_1( , , , );
  -- ...
  -- U_15: m_p_1( , , , );

  -- prod <=    ;
  
end estrutural;
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
