program AlgLista5Ex3; //Exercicio 3 da Lista 5 de algoritmos. Autor: Henrique Colodetti Escanferla.

const n=120; m=240; max=29399; // Constantes globáis definidas de acordo com o enunciado.

type vetor=array[1..n,1..m]of integer; // Criação do tipo de variavel vetor bidimensional n por m.

var v:vetor; // Variaveis globais: v=> guardará nºs aleatórios de 0 à "max".

procedure escreve_vetor(v:vetor; x, y:integer); // "escreve_vetor" app. cédulas do vetor "v".

var i, j:integer; // Variáveis locais: i=> linha de "v" e j=> coluna de "v".

begin // Inicio deste procedimento.
j:=0; // Começa com zero.
while j<>y do // Loop das colunas.
	begin // Inicio deste loop.
	j:=j+1; // Próxima coluna de "v".
	i:=0; // Começa com zero.
	while i<>x do // Loop das linhas.
		begin // Inicio deste loop.
		i:=i+1; // Próxima linha de "v".
		write(v[i,j],' '); // App d uma cédula do vetor "v".
		end; // Fim deste loop.
	writeln; // Pula linha na tela.
	end; // Fim deste loop.
end; // Fim deste procedimento.

procedure randomiza_vetor(var v:vetor; l, c:integer); // "randomiza_vetor" cria nºs randoms em td o "v".

var i, j: integer; // Variáveis locais: i=> linha de "v" e j=> coluna de "v".

begin // Inicio deste procedimento.
randomize; // Randomiza o ponto inicial do gerador de números aleatórios.
i:=0; // Começa com zero.
while i<>l do // Loop das linhas.
	begin // Inicio deste loop.
	i:=i+1; // Próxima coluna de "v".
	j:=0; // Começa com zero.
	while j<>c do // Loop das colunas. Preenchimento por coluna como foi pedido.
		begin // Inicio deste loop.
		j:=j+1; // Próxima linha de "v".
		v[i,j]:=random(max+1); // Insere nº random em uma cédula do vetor "v".
		end; // Fim deste loop.
	end; // Fim deste loop.
end; // Fim deste procedimento.


begin // Inicio do processo.
writeln('P2'); writeln(m); writeln(n); writeln(max); // Como pedido no enunciado.
randomiza_vetor(v, n, m);
escreve_vetor(v, n, m);
end. // Fim do processo.
