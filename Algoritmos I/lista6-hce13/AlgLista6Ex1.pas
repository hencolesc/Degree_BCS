program AlgLista6Ex1; //Exercicio 1 da Lista 6 de algoritmos. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..1000,1..1000]of integer; // Criação do tipo de variavel vetor bidimensional.

var v, vaux:vetor; // Variaveis globais: vaux=> guardará imagem codificada em PGM e v=> receberá os nºs com os deslocamentos inseridos.
l, c, max: integer; // l, c e max são as linhas, colunas e intensidade maxima da escala cinza, respectivamente, lida da imagem codificada.
ch: char; // Le P2 e joga-o fora.

procedure escreve_vetor(v:vetor; x, y:integer); // "escreve_vetor" app. cédulas do vetor "v".

var i, j:integer; // Variáveis locais: i=> linha de "v" e j=> coluna de "v".

begin // Inicio deste procedimento.
i:=0; // Começa com zero.
while i<>x do // Loop das linhas.
	begin // Inicio deste loop.
	i:=i+1; // Próxima linha de "v".
	j:=0; // Começa com zero.
	while j<>y do // Loop das colunas.
		begin // Inicio deste loop.
		j:=j+1; // Próxima coluna de "v".
		write(v[i,j],' '); // App d uma cédula do vetor "v".
		end; // Fim deste loop.
	writeln; // Pula linha na tela.
	end; // Fim deste loop.
end; // Fim deste procedimento.

procedure ler_vetor(var v:vetor; l, c:integer); // "ler_vetor" recebe vetor bidimensional, nº de linhas e nº de colunas retornando um vetor prenchido.

var i, j, aux:integer; // Variáveis locais: aux=> receberá a sequencia; i=> linha e j=> coluna.

begin // Inicio deste procedimento.
i:=0; // Começa com zero.
while i<>l do // Loop das linhas.
	begin // Inicio deste loop.
	i:=i+1; // Linha atual.
	j:=0; // Começa com zero.
	while j<>c do // Loop das colunas. Preenchimento por linha como foi pedido.
		begin // Inicio deste loop.
		j:=j+1; // Coluna atual.
		read(aux); // Le nº da sequencia.
		v[i,j]:=aux; // Insere valor na cedula de "v".
		end; // Fim deste loop.
	end; // Fim deste loop.
end; // Fim deste procedimento.

procedure desloca_vetor(v: vetor; l, c: integer; var vaux: vetor); // "desloca_vetor" desloca o vetor de entrada.

var i, j, x, y, deslocv, desloch: integer; // Variaveis locais: i, j, x, y, deslocv e desloch são linhas e colunas de "v", linhas e colunas de "vaux", deslocamento vertical e horizontal da img, respectivamente.

begin // Inicio deste procedimento.
read(desloch, deslocv); // Leitura dos deslocamentos.
deslocv:=-1*deslocv; // Positivo é pra cima e negativo pra baixo, o inverso ocorre nos vetores.
if (desloch>c)or(desloch<-c) then // Inicio do tratamento dos deslocamentos p/ otimização de codigo.
	desloch:=desloch mod c; // Ficará no intervalo ("-c","c").
if (deslocv>l)or(deslocv<-l) then
	deslocv:=deslocv mod l; // Ficará no intervalo ("-l","l").
if desloch<0 then
	desloch:=c+desloch; // Ficará no intervalo [0,"c").
if deslocv<0 then
	deslocv:=l+deslocv; // Ficará no intervalo [0,"c").
i:=0; // Começa com zero.
x:=deslocv; // A linha da origem deslocada de "vaux".
while i<>l do // Loop das colunas.
	begin // Inicio deste loop.
	i:=i+1; // Próxima linha de "v".
	if x>=l then
		begin
		x:=0; // Volta para o começo de "vaux".
		end;
	x:=x+1; // Próxima linha de "vaux".
	j:=0; // Começa com zero.
	y:=desloch; // A coluna da origem deslocada de "vaux".
	while j<>c do // Loop das colunas.
		begin // Inicio deste loop.
		j:=j+1; // Próxima coluna de "v".
		if y>=c then
			begin
			y:=0; // Volta para o começo de "vaux".
			end;
		y:=y+1; // Próxima coluna de "vaux".
		vaux[x,y]:=v[i,j]; // Insere nº de "v" em uma cédula específica de "vaux".
		end; // Fim deste loop.
	end; // Fim deste loop.
end; // Fim deste procedimento.

begin // Inicio do processo.
read(ch, ch, c, l, max); // Joga fora P e 2, le colunas, le linhas e o nivel maximo de cinza, respectivamente.
ler_vetor(v, l, c); // Chama-se "ler_vetor".
writeln('P2'); writeln(c,' ',l); writeln(max); // Como pedido no enunciado.
desloca_vetor(v, l, c, vaux); // Chama-se "desloca_vetor".
escreve_vetor(vaux, l, c); // Chama-se "escreve_vetor".
end. // Fim do processo.
