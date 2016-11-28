program AlgLista4Ex3; //Exercicio 3 da Lista 4 de algoritmos. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..100]of integer; // Criação do tipo de variavel vetor.

var v:vetor; // Variaveis globais: v=> guardará nºs do triangulo de pascal.
n,i,x,aux,aux2,aux3:integer; // n=> receberá a ordem pedida do triangulo de pascal; i=> varia de 2 a "n"; x=> varia de 2 a "i"+1; aux=> guarda nº da linha anterior para calcular nº da prox; aux2=> guardará outro nº da linha anterior p/ calcular nº da prox; aux3=> guardará a soma do padrão do triangulo de Pascal temporariamente possibilitando guardar os nºs certos em "aux" e aux2".

procedure writelnvet(v:vetor; tamv:integer); // "writelnvet" app nºs do vetor parcial até o indice.

begin // Inicio deste procedimento.
while tamv<>0 do
	begin // Inicio deste loop.
	write(v[tamv],' '); // App d um nº do vetor "v".
	tamv:=tamv-1; // Prox. indice de "v".
	end; // Fim deste loop.
	writeln; // Pula linha na tela.
end; // Fim deste procedimento.

begin // Inicio do processo.
write('Digite a ordem do triângulo de Pascal: '); // Pedido de "n".
readln(n); // Leitura de "n".
i:=0; // Começa com 0.
x:=0; // Começa com 0.
v[1]:=1; // 1º nº sempre é um.
v[2]:=1; // Inicialmente é um, mas será modificado a cada linha do triangulo de Pascal.		
while i<>n do
	begin // Inicio deste loop.
	v[i+1]:=1; // Ultimo nº sempre é um.
	aux:=i-1; // O 1º "v[x]" de cada linha sempre é "i"-1.
	aux2:=1; // O 1º "v[x-1]" de cada linha sempre é um.
	while x<>i+1 do
		begin; // Inicio deste loop.
		aux3:=aux+aux2; // Padrão do triangulo de Pascal.
		aux:=v[x]; // Guarda "v[x]" antes de sua alteração.
		aux2:=v[x+1]; // Guarda "v[x+1]" p/ prox "aux3".
		v[x]:=aux3; // Salva valor previamente calculado no seu devido lugar.
		x:=x+1; // Prox indice de "v".
		end; // Fim deste loop.
	x:=2; // Retorna p/ 2 pois a partir do 2º numero o padrão é aplicado de novo.
	writelnvet(v,i+1); // Chama-se "writelnvet".
	i:=i+1; // Tamanho da prox linha do triangulo de Pascal.
	end; // Fim deste loop.
end. // Fim do processo.
