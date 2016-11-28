program AlgLista7Ex1; // Exercicio 1 da lista 7 de ALgoritmos. Autor: Henrique Colodetti Escanferla.

uses crt; // Biblioteca para melhor visualisação do resultado.

const maxbolas=9; PI=3.14159265; // Constantes globais.

type vetor=array[1..maxbolas] of integer; // Criação do tipo de variavel vetor.

var mesa: vetor; // mesa=> guarda posições das bolas.
    c, l, numb: integer; // c=> comp. da mesa, l=> largura da mesa e numb=> nº d bolas na mesa.
    vel, ang: real; // vel=> velocidade da bola e ang=> angulo de direção e sentido da bola.

procedure le_posicao_das_bolas(var mesa:vetor; l, c, numb: integer); // Le posições das bolas salvando-as em "mesa".

var n, lb, cb: integer; // n=> nº da bola p/ inserção de dados, lb=> linha da posição da bola e cl=> coluna da posição da bola.

begin // Inicio deste procedimento.
n:=1;
write('Entre com a posição da largura da bola branca em pixels (no maximo ',l,'): '); // Pedido de "lb".
read(lb); // Leitura de "lb".
writeln; // Pula linha na tela.
write('Entre com a posição do comprimento da bola branca em pixels (no maximo ',c,'): '); // Pedido de "cb".
read(cb); // Leitura de "cb".
writeln; // Pula linha na tela.
mesa[1]:=lb*100+cb; // Guarda posição da bola branca.
while n<>numb do
	begin // Inicio deste loop.
	n:=n+1; // Nº da bola atual.
	write('Entre com a posição da largura da bola ',n,' em pixels (no maximo ',l,'): '); // Pedido de "lb".
	read(lb); // Leitura de "lb".
	writeln; // Pula linha na tela.
	write('Entre com a posição do comprimento da bola ',n,' em pixels (no maximo ',c,'): '); // Pedido de 																								 "cb".
	read(cb); // Leitura de "cb".
	writeln; // Pula linha na tela.
	mesa[n]:=lb*100+cb; // Guarda posição da bola.
	end; // Fim deste loop.
end; // Fim deste procedimento.

procedure imprime_mesa(mesa:vetor; l, c, numb:integer); // Imprime mesa com as bolas em suas posições.

var i,j, n: integer; // i=> linha da mesa; j=> coluna da mesa e n=> nº da bola.
    aux: boolean; // aux=> indica existencia de bola em (i,j).

begin // Inicio deste procedimento.
delay(500); // Um certo atraso para melhor visualização.
clrscr; // Limpa tela.
for i:=1 to l do
	begin // Inicio deste for.
	for j:=1 to c do
		begin // Inicio deste for.
		aux:=true;
		for n:=1 to numb do
			begin // Inicio deste for.
			if ((trunc(mesa[n]) div 100)=i)and((trunc(mesa[n]) mod 100)=j)and aux then // Caso exista bola na posição (i,j).
				begin // Inicio deste if-then.
				aux:=false; // Achou bola, imprimirá asterisco só uma vez.
				write('*'); // Bola é asterisco na tela. Sobrepõe qualquer outra possibilidade.
				end // Fim deste if-then.
			end; // Fim deste for.
		if aux then if (j=1)or(j=c) then
			    	write('|') // Paredes das colunas são representadas por pipes. Sobrepõe tudo exceto 								  bolas.
		else if (i=1)or(i=l) then
		     		write('-') // Paredes das linhas são representadas por pipes. Sobrepõe apenas 									  espaços vazios.
		     else
			   		write(' '); // Todos os outros casos é espaço em branco.
		end; // Fim deste for.
	writeln; // Pula linha na tela.
	end; // Fim deste for.
end; // Fim deste procedimento.

procedure simula(var mesa:vetor; l, c: integer; var vel, ang: real); // Simulador de movimentação.

var i,j: integer; // Variaveis locais. i=> linha da bola e j=> coluna da bola.

begin // Inicio deste procedimento.
i:=mesa[1] div 100;
j:=mesa[1] mod 100;
while vel>0.01 do // Condição para termino da simulação.
	begin // Inicio deste loop.
	if (i=1)or(i=l)or(j=1)or(j=c) then
		if (ang=0)or(ang=90)or(ang=180)or(ang=270) then
			ang:=ang+180
		else if (ang>0)and(ang<90)and(i<=1)or(ang>270)and(ang<360)and(i>=l) then
		 	     ang:=360-ang
		 	 else if (ang>90)and(ang<180)and(i<=1)or(ang>180)and(ang<270)and(i>=l) then
						ang:=-1*ang
				  else if (ang>90)and(ang<180)and(j<=1) then
							ang:=-1*ang-180
					   else if (j<=1)or(j>=c) then
								ang:=-1*ang+180; // A condição foi simplificada pelos "ifs" anteriores.		
	(* -p/ "ang" entre 0 e 90 na linha um ou menos: ang:=360-ang;
	   -p/ "ang" entre 90 e 180 na linha um ou menos: ang:=ang+2*(180-ang); => ang:=-ang;
	   -p/ "ang" entre 180 e 270 na coluna um ou menos: ang:=ang+2*(270-ang); => ang:=-ang+180;
	   -p/ "ang" entre 90 e 180 na coluna um ou menos: ang:=ang-2*(ang-90) => ang:=-ang-180;
	   -p/ "ang" entre 270 e 360 na linha "l" ou depois: ang:=360-ang;
	   -p/ "ang" entre 180 e 270 na linha "l" ou depois: ang:=ang-2*(ang-180); => ang:=-ang;
	   -p/ "ang" entre 0 e 90 na coluna "c" ou depois: ang:=ang+2*(90-ang); => -ang+180;
	   -p/ "ang" entre 270 e 360 na coluna "c" ou depois: ang:=ang-2*(ang-270); => -ang+180;
	   -p/ "ang" igual a 0, 90, 180 ou 270 em qlq linha/coluna: ang:=ang+180; *)
	ang:=ang-(360*(trunc(ang) mod 360)); // "Ang" fica entre -359 e 359 caso ultrapasse-os.
	if ang<0 then // "Ang" fica entre 0 e 359 caso seja menor que 0.
		ang:=ang+360;
	vel:=vel*0.9; // Fator de perda de energia cinetica suposta.
	mesa[1]:=mesa[1]-trunc(sin(PI*ang/180)*vel*100)+trunc(cos(PI*ang/180)*vel); // Perda de valor real.
	i:=mesa[1] div 100;
	j:=mesa[1] mod 100;
	if i<1 then // Caso bola "saia" do tabuleiro, existe perda de movimento aqui.
		mesa[1]:=100+(mesa[1] mod 100);
	if i>l then
		mesa[1]:=100*l+(mesa[1] mod 100);
	if j<1 then
		mesa[1]:=(mesa[1] div 100)+1;
	if j>c then
		mesa[1]:=(mesa[1] div 100)+c;
	i:=mesa[1] div 100;
	j:=mesa[1] mod 100;
	imprime_mesa(mesa, l, c, numb); // Chama-se "imprime-mesa".
	end; // Fim deste loop.
end; // Fim deste procedimento.

begin // Inicio do processo.
write('Entre com a Largura da mesa em pixels (no maximo 40): '); // Pedido de "l".
read(l); // Leitura de "l".
writeln; // Pula linha na tela.
write('Entre com o Comprimento da mesa em pixels (no maximo 40): '); // Pedido de "c".
read(c); // Leitura de "c".
writeln; // Pula linha na tela.
write('Entre com a quantidade de Bolas da mesa (no maximo 9): '); // Pedido de "numb".
read(numb); // Leitura de "numb".
writeln; // Pula linha na tela.
le_posicao_das_bolas(mesa, l, c, numb); // Chama-se "le_posicao_das_bolas".
write('Entre com a Velocidade Inicial da Bola Branca em pixels/s (de 0.01 a 3.0): '); // Pedido de "vel".
read(vel); // Leitura de "vel".
writeln; // Pula linha na tela.
write('Entre com o Angulo Inicial da Bola Branca em graus (de 0 a 359): '); // Pedido de "ang".
read(ang); // Leitura de "ang".
writeln; // Pula linha na tela.
clrscr; // Limpa tela.
imprime_mesa(mesa, l, c, numb); // Chama-se "imprime-mesa".
simula(mesa, l, c, vel, ang); // Chama-se "simula".
writeln('FIM!'); // App. término do programa.
end. // Fim do processo.
