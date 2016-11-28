program AlgLista2Ex2; // Algoritmo do exercício 2 da Lista 2. Autor: Henrique Colodetti Escanferla.

var 
s, a, b: real;
i, f, g: integer; // s => soma dos termos; a=> um termo da sequência dada; b=> o termo, após ou antes de "a", da sequência dada; i => variavel utilizada para calculo de fatorial; g=> outra variavel usada para calcular fatorial; f=> variavel usada para guardar o valor de certo calculo fatorial.

begin // Começo do processo.

writeln('Este algoritmo irá mostrar o valor da soma dos termos da sequência 1-1/2!+1/4!-1/6!... até que a diferença de dois termos consecutivos seja menor que 0,000001'); // Apresentação do algoritmo e sua função.
s:=1; // Pra não definir que 0!=1, a soma ja começa com o 1º termo.
i:=4; // O primeiro numero operado com fatorial no 2º loop é 4.
a:=1; // 1º termo da sequência.
f:=-1; // Elemento neutro da multiplicação para que "f" não anule e nem modifique seu processo de geração. Com "-" pois o primeiro termo gerado aqui é positivo mas existe "-"*f no meio do processo.
b:=-0.5; // Pra não usar que 2!=2, "b" ja começa com o 2º termo e é inserido em "s".
g:=4; // Começa com 4 para seguir a sequência 4, 6, 8, 10, 12...
	while (abs(a)-abs(b))>=0.000001 do // Este 1º loop ocorre até que dois termos seguidos da sequência tenham a diferença menor que 0,000001. Pelo enunciado, entende-se que é a diferença de seus módulos.
	begin // Início dos comandos deste 1º loop.
	s:=s+b; // A soma dos termos é realizada aqui. Logo após ser TRUE no 1º loop com o novo "b".
	a:=b; // Isto salva o termo gerado anteriormente para a comparação do 1º loop.
		while i<>2 do // 2º loop criado para calcular fatoriais de "g" e guardar em "f".
		begin // Início dos comandos deste 2º loop.
		f:=i*(i-1)*f; // Isto garante o cálculo de fatoriais até que "i"=2.
		i:=i-2; // O fatorial consiste no produto de n por seus antecessores até que chegue a 1.
		end; // Fim dos comandos deste 2º loop.
	f:=-2*f; // O 2º loop não processa "i"=2, então, aqui ele é inserido no cálculo de "f"."-" garante a alternância de sinais nos termos da sequência. Veja que "f" começa com -1 para que "f" seja positivo na 1ª execução do 1º loop.
	g:=g+2; // O padrão do fatorial é este, de dois em dois.
	i:=g; // Preparação de "i" para o 2º loop.
	b:=1/f; // Geração do termo seguinte da sequência.
	f:=1; // Eliminação do resquício do cálculo anterior inserindo o elemento nulo da multiplicação.
	end; // Fim dos comandos deste 1º loop.
writeln('O valor da soma é, aproximadamente, de: ',s); // O resultado é apresentado para o usuário.

end. // Fim do processo.
