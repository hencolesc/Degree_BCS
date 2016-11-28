program AlgLista4Ex2; // Exercicio 2 da lista 4. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..100]of integer; // Criação do tipo de variável "vetor".

var v, u, i: vetor; // Variáveis globais: v=> guarda 1ª sequencia; u=> guarda 2ª sequencia; i=> guarda o resultado pedido.
tamv, tamu, tami:integer; // tamv=> tamanho util de "v"; tamu=> tamanho util de 'u"; tami=> tamanho util de "i".

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


begin
tamv:=0; // Começa, naturalmente, com zero.
tamu:=0; // Começa, naturalmente, com zero.
tami:=0; // Começa, naturalmente, com zero.
write('Escreva a 1ª sequência: '); // Pedido de "v".
lervetor(v,tamv); // Chama-se "lervetor".
write('Escreva a 2ª sequência: '); // Pedido de "u".
lervetor(u,tamu); // Chama-se "lervetor".
write('Conjunto união = '); // 1ª parte da msg.
while (tamv<>0)or(tamu<>0) do
	begin // Inicio deste loop.
	if (repeticoes(v,tamv,v[tamv])<>0)and(repeticoes(i,tami,v[tamv])=0) then // Coloca-se "v" em "i".
		begin // Inicio deste if-then.
		tami:=tami+1; // Indice atual de "i".
		i[tami]:=v[tamv]; // Guarda valor de "v" em "i".
		end; // Fim deste if-then.
	if tamv>0 then
		tamv:=tamv-1; // Prox. indice de "v" p/ gerar prox valor a ser verificado.
	if (repeticoes(u,tamu,u[tamu])<>0)and(repeticoes(i,tami,u[tamu])=0) then // Coloca-se "u" em "i".
		begin // Inicio deste if-then.
		tami:=tami+1; // Indice atual de "i".
		i[tami]:=u[tamu]; // Guarda valor de "u" em "i".
		end; // Fim deste if-then.
	if tamu>0 then
		tamu:=tamu-1; // Prox. indice de "u" p/ gerar prox valor a ser verificado.
	end; // Fim deste loop.
writelnvet(i,tami); // Chama-se "writelnvet".
end.
