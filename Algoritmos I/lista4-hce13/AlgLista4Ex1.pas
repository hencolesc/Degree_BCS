program AlgLista4Ex1; // Exercicio 1 da lista 4. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..100]of integer; // Criação do tipo de variável "vetor".

var seq, rep: vetor; // Variáveis globais. seq=> receberá sequência de inteiros; rep=> nºs repetidos.
tamseq, irep: integer; // tamseq=> tamanho util de "seq"; irep=> indice de "rep", será tamanho util dele.

procedure writelnvet(v:vetor; tamv:integer); // "writelnvet" app nºs do vetor parcialmente pelo indice.

begin // Inicio deste procedimento.
while tamv<>0 do
	begin // Inicio deste loop.
	write(v[tamv],' '); // App d um nº do vetor "v".
	tamv:=tamv-1; // Prox. indice de "v".
	end; // Fim deste loop.
writeln; // Pula linha na tela.
end; // Fim deste procedimento.

procedure lervetor(var v:vetor; var i:integer); // "lervetor" recebe vetor, indice inicial e le entrada retornando vetor com a entrada e seu tamanho.

var aux:integer; // Variáveis locais: aux=> recebera a sequencia.

begin // Inicio deste procedimento.
read(aux); // Le 1º numero da sequencia.
while aux<>0 do
	begin // Inicio deste loop.
	i:=i+1; // Incrementa o indice.
	v[i]:=aux; // Insere valor no indice do vetor.
	read(aux); // Le prox. nº da sequencia.
	end; // Fim deste loop.
writeln;
end; // Fim deste procedimento.

function repeticoes(v:vetor; tamv:integer; num:real):integer; // "repeticoes" le vetor e valor acusando nºs de repetições.

var cont:integer; // Variaveis locais: cont=> contará o nº de repetições.

begin // Inicio desta função.
cont:=0; // Começa com zero.
while tamv<>0 do // Se "num" repetir o loop acaba.
	begin // Inicio deste loop.
	if v[tamv]=num then
		cont:=cont+1; // Houve ocorrencia de "num".
	tamv:=tamv-1; // Prox. indice do vetor.
	end; // Fim deste loop.
repeticoes:=cont; // Coleta do resultado.
end; // Fim desta função.

begin // Inicio do processo.
tamseq:=0; // Começa, naturalmente, com zero.
irep:=0; // Começa, naturalmente, com zero.
write('Digite uma sequência de números inteiros: '); // Pedido de "aux".
lervetor(seq,tamseq); // Chama-se "lervetor".
while tamseq<>0 do
	begin // Inicio deste lopp.
	if (repeticoes(seq,tamseq,seq[tamseq])>1)and(repeticoes(rep,irep,seq[tamseq])=0) then // Chama-se "repeticoes" tanto para verificar repetições em "seq" quanto para verificar repetições em "rep".
		begin // Inicio deste if-then.
		irep:=irep+1; // Prox. indice.
		rep[irep]:=seq[tamseq]; // Guarda em "rep" valores repetidos em "seq".
		end; // Fim deste if-then.
	tamseq:=tamseq-1; // Prox. indice de "seq" a verificar.
	end; // Fim deste loop.
write('Os repetidos são: '); // Parte da app do resultado.
writelnvet(rep,irep); // Chama-se "writelnvet".
end. // Fim do processo.
