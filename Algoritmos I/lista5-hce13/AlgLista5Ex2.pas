program AlgLista5Ex2; // Exercicio 2 da lista 5. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..100]of integer; // Criação do tipo de variável "vetor".

var v: vetor; // Variáveis globais: v=> guarda a sequencia de entrada.
tamv, i, x, y:integer; // tamv=> tamanho util de "v"; i=> indices de "v"; x=> nº de repeticoes e y=> guarda valor verificado antes de ser zerado em "v". 

procedure ler_vetor(var v:vetor; var i:integer); // "ler_vetor" recebe vetor, indice inicial e le entrada retornando vetor com a entrada e seu tamanho.

var aux:integer; // Variáveis locais: aux=> recebera a sequencia.

begin // Inicio deste procedimento.
read(aux); // Le 1º numero da sequencia.
while aux<>0 do
	begin // Inicio deste loop.
	v[i]:=aux; // Insere valor no indice do vetor.
	i:=i+1; // Incrementa o indice.
	read(aux); // Le prox. nº da sequencia.
	end; // Fim deste loop.
i:=i-1; // Retira-se o 0 na contagem.
end; // Fim deste procedimento.

procedure repeticoes(var v:vetor; tamv, num:integer; var cont, y:integer); // "repeticoes" le vetor e valor acusando nºs de repetições , zerando suas ocorrencias em "v" e guardando este mesmo valor em "y".

begin // Inicio deste procedimento.
cont:=0; // Começa com zero.
y:=num; // Salva "num".
while tamv<>0 do // O loop acaba após a busca por todo o vetor "v".
	begin // Inicio deste loop.
	if v[tamv]=num then
		begin // Inicio deste if-then.
		cont:=cont+1; // Houve ocorrencia de "num".
		v[tamv]:=0; // Zera-se este valor em "v".
		end; // Fim deste if-then.
	tamv:=tamv-1; // Prox. indice do vetor.
	end; // Fim deste loop.
end; // Fim deste procedimento.

begin
tamv:=1; // Indice inicial de "v".
i:=0; // Começa com 0.
write('Escreva uma sequencia de nºs inteiros: '); // Pedido de "v".
ler_vetor(v,tamv); // Chama-se "ler_vetor".
writeln;
while i<>tamv do
	begin // Inicio deste loop.
	i:=i+1; // Indice atual de "v".
	if v[i]<>0 then // Zeros não fazem parte da verificação.
		begin // Inicio deste if-then.
		repeticoes(v, tamv, v[i], x, y); // Chama-se "repeticoes".
		write(y,': ',x,' ocorrencia'); // Parte da msg em singular.
		if x>1 then
			writeln('s') // Parte da msg em plural.
		else
			writeln; // Pula linha.
		end; // Fim deste if-then.
	end; // Fim deste loop. 
end.
