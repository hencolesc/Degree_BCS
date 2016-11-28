-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- UFPR, BCC, ci210                        autor: Roberto Hexsel, 17nov2012
-- ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

--++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
-- testbench para somador
--++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
library IEEE;
use IEEE.std_logic_1164.all;
use work.p_wires.all;

entity tb_somador is
end tb_somador;

architecture TB of tb_somador is

  component adderCadeia is port(inpA, inpB : in bit_vector;
                          outC : out bit_vector;
                          vem  : in bit;
                          vai  : out bit);
  end component adderCadeia;

  component adderAdianta4 is port(inpA, inpB : in bit_vector;
                          outC : out bit_vector;
                          vem  : in bit;
                          vai  : out bit);
  end component adderAdianta4;

  component adderAdianta16 is port(inpA, inpB : in bit_vector;
                          outC : out bit_vector;
                          vem  : in bit;
                          vai  : out bit);
  end component adderAdianta16;

  signal inpA,inpB : reg16;             -- entradas de teste
  signal resCad,resAd4,resAd16 : reg16; -- resultados
  signal vaiCad,vaiAd4,vaiAd16 : bit;
  signal addsub : bit;
  signal esp_res : reg16;               -- valores esperados
  signal esp_vai : bit;
  
  type test_record is record
                        a : reg16;      -- entrada
                        b : reg16;      -- entrada
                        f : bit;        -- funcao: 0=ADD, 1=SUB
                        c : reg16;      -- saida
                        v : bit;        -- vai-um
                      end record;
  type test_array is array(positive range <>) of test_record;
    
  constant test_vectors : test_array := (
    -- a,     b,      f, c,       vai-um
    -- testes para soma
    (x"0000",x"0000",'0',x"0000",'0'),
    -- acrescente novos valores aqui
    (x"0001",x"0001",'0',x"0002",'0'),
    (x"0fff",x"0001",'0',x"1000",'0'),  -- corrija valores de c e v
    (x"0000",x"0000",'0',x"0000",'0'),
    -- testes para diferença
    (x"0000",x"0000",'1',x"0000",'1'),  -- inverte vai-um (empresta)
    -- acrescente novos valores aqui
    (x"0000",x"0000",'1',x"0000",'1'),
    (x"0000",x"0000",'1',x"0000",'1'),
    -- nao alterar estes dois ultimos --
    (x"0000",x"0000",'1',x"0000",'1'),
    (x"0000",x"0000",'1',x"0000",'1')
    );

begin  -- TB

  U_addCad: adderCadeia     port map(inpA, inpB, resCad,  addsub, vaiCad);
  U_addAd4: adderAdianta4   port map(inpA, inpB, resAd4,  addsub, vaiAd4);
  U_addAd16: adderAdianta16 port map(inpA, inpB, resAd16, addsub, vaiAd16);

  U_testValues: process                -- test the circuit
    variable v : test_record;
  begin

    for i in test_vectors'range loop
      v := test_vectors(i);
      inpA <= v.a;
      if v.f = '0' then                 -- soma
        inpB <= v.b;
      else
        inpB <= not(v.b);               -- subtracao= A + not(B)+1
      end if;
      addsub <= v.f;                    -- vem-um(0)=1 na subtracao
      esp_res <= v.c;
      esp_vai <= v.v;

      assert resCad = esp_res
        report "cadeia:  saida errada A="& BV2STR(inpA) &" B="& BV2STR(inpB)
        &" soma="& BV2STR(resCAD) &" esperada="& BV2STR(esp_res)
        &" som0/1sub="& B2STR(v.f)
        severity error;

      assert vaiCad = esp_vai
        report "cadeia:  vai-um errado A="& BV2STR(inpA) &" B="& BV2STR(inpB)
        &" soma="& BV2STR(resCAD) &" esp="& BV2STR(esp_res)
        &" vai="& B2STR(vaiCAD) &" esp="& B2STR(esp_vai)
        &" som0/1sub="& B2STR(v.f)
        severity error;

      
      -- depois de implementar adderAdianta4, descomente as linhas com --x
      
--x       assert resAd4 = esp_res
--x         report "adiant4: saida errada A="& BV2STR(inpA) &" B="& BV2STR(inpB)
--x         &" soma="& BV2STR(resCAD) &" esperada="& BV2STR(esp_res)
--x         &" som0/1sub="& B2STR(v.f)
--x         severity error;
--x 
--x       assert vaiAd4 = esp_vai
--x         report "adiant4: vai-um errado A="& BV2STR(inpA) &" B="& BV2STR(inpB)
--x         &" vai="& B2STR(vaiCAD) &" esperada="& B2STR(esp_vai)
--x         &" som0/1sub="& B2STR(v.f)
--x         severity error;


      -- depois de implementar adderAdianta16, descomente as linhas com --z
--z       assert resAd16 = esp_res
--z         report "adian16: saida errada A="& BV2STR(inpA) &" B="& BV2STR(inpB)
--z         &" soma="& BV2STR(resCAD) &" esperada="& BV2STR(esp_res)
--z         &" som0/1sub="& B2STR(v.f)
--z         severity error;
--z 
--z       assert vaiAd16 = esp_vai
--z         report "adian16: vai-um errado A="& BV2STR(inpA) &" B="& BV2STR(inpB)
--z         &" vai="& B2STR(vaiCAD) &" esperada="& B2STR(esp_vai)
--z         &" som0/1sub="& B2STR(v.f)
--z         severity error;

      wait for 1 ns;                  -- se necessario, aumente este valor
    end loop;

    assert FALSE
      report " --###--fim da simulacao--###-- "
      severity failure;

    end process;
   
end TB;

----------------------------------------------------------------
configuration CFG_TB of TB_SOMADOR is
	for TB
        end for;
end CFG_TB;
----------------------------------------------------------------
