program lista1ex2; // Exercício 1 da Lista 2 de Algorítmos. Autor: Henrique Colodetti Escanferla.

var a, b: longint; // Variáveis inteiras para a execução do processo. a=> numero a ser fatorado, b=> variavel que assumirá todos os primos do processo. Longint para fatorar numeros grandes.

begin // Começo do processo.

writeln('Este algoritmo fornecerá a fatoração em primos de um numero inteiro positivo qualquer. Veja que 1 não é primo e é o menor inteiro positivo. Ele não possui, então, uma fatoração em primos.'); // Apresentação do algoritmo e sua função.
write('Digite um numero inteiro a ser fatorado diferente de 1: '); // Aqui é pedido o numero inteiro "a".
readln(a); // Leitura da variável "a".
b:= 2; // Menor numero primo é o 2, a sequência de divisões começa por ele então.
while a<>1 do // Início do loop das divisões de "a" por numeros primos até restar 1 na fatoração.
	if (a)mod(b)=0 then // Se "a"/"b" tem resto 0 então "b" é um dos primos da fatoração.
		begin // Começo dos comandos deste "if then".
		a:=(a)div(b); // Restante a ser fatorado é inserido em "a".
		write(b,' '); // Apresentação dos primos espaçados entre sí como foi pedido.
		end // Fim dos comandos deste "if then".
	else // Caso "a"/"b" não dê resto 0, "b" é incrementado até que isso ocorra.
	b:=b+1; // Incrementação de "b" em busca dos primos que dividem "a". Fim deste "if then else".

end. // Fim do processo.
