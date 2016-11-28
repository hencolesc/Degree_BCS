program AlgLista5Ex4; // Exercicio 4 da lista 5 de algoritmos. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..9,1..9]of real; // Criação do tipo de variavel vetor bidimensional.

var v:vetor; // Variaveis globais: v=> guardará numeros reais formando uma matriz quadrada. 
n:integer; // n=> tamanho da matriz quadrada que pode ser 1,2 ou 3.

procedure ler_vetor(var v:vetor; var n:integer); // "ler_vetor" recebe vetor bidimensional quadrático, le seu tamanho e a entrada retornando vetor com a entrada.

var i, j:integer; aux:real; // Variáveis locais: aux=> receberá a sequencia; i=> linha e j=> coluna.

begin // Inicio deste procedimento.
j:=0; // Começa com zero.	
while j<>n do // Loop das colunas.
	begin // Inicio deste loop.
	j:=j+1; // Coluna atual.
	i:=0; // Começa com zero.
	while i<>n do // Loop das linhas.
		begin // Inicio deste loop.
		i:=i+1; // Linha atual.
		read(aux); // Le nº da sequencia.
		v[i,j]:=aux; // Insere valor na cedula do vetor.
		end; // Fim deste loop.
	end; // Fim deste loop.
end; // Fim deste procedimento.

function determinante(v:vetor; n:integer):real; // "determinante" recebe vetor bidimensional quadrático, le sua ordem e conteúdo retornando seu determinante.

begin // Inicio desta função.
if n=3 then
	determinante:=(v[1,1]*v[2,2]*v[3,3])+(v[1,2]*v[2,3]*v[3,1])+(v[2,1]*v[3,2]*v[1,3])
	-(v[1,3]*v[2,2]*v[3,1])-(v[1,2]*v[2,1]*v[3,3])-(v[2,3]*v[3,2]*v[1,1]) // Conforme a regra.	
else	if n=2 then
		determinante:=(v[1,1]*v[2,2])-(v[1,2]*v[2,1]) // Conforme a regra.
	else
	determinante:=v[1,1]; // Conforme a regra.
end; // Fim desta função.

begin // Começo do processo.
write('Digite a ordem da matriz quadrada: '); // Pedido de "n".
readln(n); // Leitura de "n".
write('Digite uma sequência de nºs reais: '); // Pedido da seq. de nºs da matriz.
ler_vetor(v, n); // Chama-se "ler_vetor".
writeln; // Pula linha na tela.
writeln('O determinante da matriz inserida é de valor: ',determinante(v, n):5:2); // Chama-se "determinante"
end. // Fim do processo.
