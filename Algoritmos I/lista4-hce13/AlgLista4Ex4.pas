program AlgLista4Ex4; // Exercicio 4 da lista 4 de algoritmos. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..27]of integer; // Criação do tipo de variavel vetor de 27 posições de inteiros.

var v:vetor; // Variaveis globais: v=> guardará numeros aleatorios de 1 a 365.
n,prob:real; // n=> receberá comandos do usuario; prob=> guarda o resultado pedido; den=> nº de randomizações de "v".
tamv:integer; // tamv=> tamanho util de "v";

procedure preenche(var v:vetor; tamv:integer); // "preenche" randomizará nºs e os colocará num dado vetor.

begin // Inicio deste procedimento.
while tamv<>0 do
	begin // Inicio deste loop.
	v[tamv]:=random(266); // Chama-se "random" que gera nº d 1 a 365 e coloca em "v".
	tamv:=tamv-1; // Prox indice de "v".
	end; // Fim deste loop.
end; // Fim deste procedimento.
function repeticoes(v:vetor; tamv:integer; num:real):boolean; // "repeticoes" le vetor e valor acusando incidencia de pelo menos 2 vezes um mesmo valor no veor "v".

var cont:integer; // Variaveis locais: cont=> contará o nº de repetições.

begin // Inicio desta função.
repeticoes:=false; // Começa como falso.
cont:=0; // Começa com zero.
while tamv<>0 do // Se "num" repetir o loop acaba.
	begin // Inicio deste loop.
	if v[tamv]=num then
		cont:=cont+1; // Houve ocorrencia de "num".
	tamv:=tamv-1; // Prox. indice do vetor.
	end; // Fim deste loop.
if cont>1 then
	repeticoes:=true; // Resultado positivo.
end; // Fim desta função.

begin // Começo do processo. 
prob:=0; // Começa com zero.
n:=0; // Começa com zero
while n<10000000 do // 10^7 dá um resultado de precisão boa.
	begin // Inicio deste loop.
	tamv:=27; // Começa com 27.
	preenche(v,tamv); // Chama-se "preenche".
	while tamv<>0 do
		begin // Inicio deste loop.
		if repeticoes(v,tamv,v[tamv]) then // Chama-se "repeticoes".
			begin // Inicio deste if-then.
			prob:=prob+1; // Incrementa o numerador pois o resultado é positivo.
			tamv:=1; // Interrompe o loop pois o resultado é positivo.
			end; // Fim deste if-then.
		tamv:=tamv-1; // Proximo indice de "v".
		end; // Fim deste loop.			
	n:=n+1; // Conta-se um ciclo.
	end; // Fim deste loop.
prob:=prob/10000000; // Calculo de "prob". É o nº de eventos confirmados sobre o nº de tentativas.
writeln('O resultado é ',prob:9:6); // app do resultado.
end. // Fim do processo.
