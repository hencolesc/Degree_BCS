-- Exercício de fixação de Projetos Digitais e Microprocessadores. Autor: Henrique Colodetti Escanferla.

library IEEE;
use IEEE.std_logic_1164.all;

entity inv is
  port( a: in std_logic;
        y: out std_logic );
end inv;

architecture estrutura_inv of inv is
begin
  y <= not a after 5 ns;
end estrutura_inv;


-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity and2 is
  port( a, b: in std_logic;
        y: out std_logic );
end and2;

architecture estrutura_and2 of and2 is
begin
  y <= a and b after 8 ns;
end estrutura_and2;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity and3 is
  port( a, b, c: in std_logic;
        y: out std_logic );
end and3;

architecture estrutura_and3 of and3 is
  component c_and2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  for n1: c_and2 use entity work.and2(estrutura_and2);
  for n2: c_and2 use entity work.and2(estrutura_and2);
  signal s1, s2: std_logic;
begin
  n1: c_and2 port map (a, b, s1);
  n2: c_and2 port map (s1, c, s2);
  y <= s2;
end estrutura_and3;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity or2 is
  port( a, b: in std_logic;
        y: out std_logic );
end or2;

architecture estrutura_or2 of or2 is
begin
  y <= a or b after 8 ns;
end estrutura_or2;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity xor2 is
  port( a, b: in std_logic;
        y: out std_logic );
end xor2;

architecture estrutura_xor2 of xor2 is
begin
  y <= a xor b after 8 ns;
end estrutura_xor2;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity latchsr is
  port( s, r: in std_logic;
        q, nq: out std_logic );
end latchsr;

architecture estrutura_latchsr of latchsr is
  component c_or2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  component c_inv
    port( a: in std_logic;
          y: out std_logic );
  end component;
  for n1: c_or2 use entity work.or2(estrutura_or2);  
  for n2: c_or2 use entity work.or2(estrutura_or2);  
  for i1: c_inv use entity work.inv(estrutura_inv);  
  for i2: c_inv use entity work.inv(estrutura_inv);  
  signal s1, s2, s3, s4: std_logic;
begin
  n1: c_or2 port map (r, s2, s3);
  n2: c_or2 port map (s, s1, s4);
  i1: c_inv port map (s3, s1);
  i2: c_inv port map (s4, s2);
  q <= s1;
  nq <= s2;
end estrutura_latchsr;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity latchd is
  port( clk, d: in std_logic;
        q, nq: out std_logic );
end latchd;

architecture estrutura_latchd of latchd is
  component c_latchsr
    port( s, r: in std_logic;
          q, nq: out std_logic );
  end component;
  component c_and2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  component c_inv
    port( a: in std_logic;
          y: out std_logic );
  end component;
  for n1: c_and2 use entity work.and2(estrutura_and2);  
  for n2: c_and2 use entity work.and2(estrutura_and2);  
  for i1: c_inv use entity work.inv(estrutura_inv);  
  for l1: c_latchsr use entity work.latchsr(estrutura_latchsr);  
  signal s1, s2, s3, s4, s5: std_logic;
begin
  n1: c_and2 port map (clk, d, s3);
  n2: c_and2 port map (clk, s1, s2);
  i1: c_inv port map (d, s1);
  l1: c_latchsr port map (s3, s2, s4, s5);
  q <= s4;
  nq <= s5;
end estrutura_latchd;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity flipflopd is
  port( clk, d: in std_logic;
        q, nq: out std_logic );
end flipflopd;

architecture estrutura_flipflopd of flipflopd is
  component c_latchd
    port( clk, d: in std_logic;
          q, nq: out std_logic );
  end component;
  component c_inv
    port( a: in std_logic;
          y: out std_logic );
  end component;
  for i1: c_inv use entity work.inv(estrutura_inv);  
  for l1: c_latchd use entity work.latchd(estrutura_latchd);  
  for l2: c_latchd use entity work.latchd(estrutura_latchd);  
  signal s1, s2, lixo: std_logic;
begin
  i1: c_inv port map (clk, s2);
  l1: c_latchd port map (s2, d, s1, lixo);
  l2: c_latchd port map (clk, s1, q, nq);
end estrutura_flipflopd;

-----------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;

entity flipflopr is
  port( clk, d, reset: in std_logic;
        q, nq: out std_logic );
end flipflopr;

architecture estrutura_flipflopr of flipflopr is
  component c_ffd
    port( clk, d: in std_logic;
          q, nq: out std_logic );
  end component;
  component c_inv
    port( a: in std_logic;
          y: out std_logic );
  end component;
  component c_and2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  for i1: c_inv use entity work.inv(estrutura_inv);
  for a1: c_and2 use entity work.and2(estrutura_and2);
  for f1: c_ffd use entity work.flipflopd(estrutura_flipflopd);
  signal s1, s2: std_logic;
begin
  i1: c_inv port map (reset, s1);
  a1: c_and2 port map (d, s1, s2);
  f1: c_ffd port map (clk, s2, q, nq);
end estrutura_flipflopr;

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;

entity exerc is
	port( clk, reset, a: in std_logic;
				y: out std_logic);
end exerc;

architecture estrutura_exerc of exerc is
	component c_ffr
    port( clk, d, reset: in std_logic;
          q, nq: out std_logic );
  end component;
  component c_and2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  component c_xor2
  port( a, b: in std_logic;
        y: out std_logic );
	end component;
	component c_inv
    port( a: in std_logic;
          y: out std_logic );
  end component;
  component c_or2
    port( a, b: in std_logic;
          y: out std_logic );
  end component;
  for f1: c_ffr use entity work.flipflopr(estrutura_flipflopr);
  for f0: c_ffr use entity work.flipflopr(estrutura_flipflopr);
  for i1: c_inv use entity work.inv(estrutura_inv);
  for xor1: c_xor2 use entity work.xor2(estrutura_xor2);
  for or1: c_or2 use entity work.or2(estrutura_or2);
  for a1: c_and2 use entity work.and2(estrutura_and2);
  for a2: c_and2 use entity work.and2(estrutura_and2);
  for a3: c_and2 use entity work.and2(estrutura_and2);
  signal s1, s2, s3, s4, s5, s6, s7, s8, lixo: std_logic;
begin
	f1: c_ffr port map (clk, s3, reset, s1, lixo);
	f0: c_ffr port map (clk, s7, reset, s2, s8);
	i1: c_inv port map (a, s5);
	xor1: c_xor2 port map (s1, s2, s4);
	or1: c_or2 port map (s5, s6, s7);
	a1: c_and2 port map (s1, s2, y);
	a2: c_and2 port map (a, s4, s3);
	a3: c_and2 port map (s1, s8, s6);
end estrutura_exerc;

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;

entity teste is
end teste;

architecture arq_teste of teste is
	component c_e1
		port( clk, reset, a: in std_logic;
	      	      y: out std_logic);
	end component;
	for e1: c_e1 use entity work.exerc(estrutura_exerc);
	signal clk_in, reset_in, a_in, y_out: std_logic;
begin
	e1: c_e1 port map ( clk_in, reset_in, a_in, y_out );
	reset_in <= '1', '0' after 600 ns;
	clk_in <= '0', '1' after 500 ns, '0' after 600 ns, '1' after 800 ns, '0' after 1000 ns, '1' after 1200 ns, '0' after 1400 ns,
	'1' after 1600 ns, '0' after 1800 ns, '1' after 2000 ns, '0' after 2200 ns, '1' after 2400 ns, '0' after 2600 ns, '1' after 2800 ns;
	a_in <= '1', '0' after 700 ns, '1' after 1500 ns, '0' after 1700 ns, '1' after 1800 ns;
end arq_teste;
