program AlgLIsta3Ex2; // Exercício 2 da lista 3. Autor: Henrique Colodetti Escanferla.

var num1, num2, produto, carry, aux, casadec1, casadec2: longint; // Variáveis inteiras para o processo. num1=> multiplicando; num2=> multiplicador; produto=> resultado da operação; carry=> vai-um do processo; aux=> guardará "num1" quando necessário; casadec1=> impõe a casa decimal dos numeros somados em "produto" com relação ao "num1"; casadec2=> idem ao "casadec1" mas em relação ao "num2".

begin // Inicio do processo.
write('Insira o multiplicador: '); // Pedido de "num1".
readln(num1); // Leitura de "num1".
write('Insira o multiplicando: '); // Pedido de "num2".
readln(num2); // Leitura de "num2".
produto:=0; // O resultado começa com "0" pois sofrerá incrementação de somas.
aux:=num1; // "aux" salva valor de "num1".
casadec1:=10; // Começa com "10^1".
casadec2:=1; // Começa com "10^0".
carry:=0; // O vai-um naturalmente começa com "0".
while num2<>0 do
	begin // Inicio deste loop.
	casadec2:=casadec2*10; // Aumenta-se a casa decimal atual em relação ao "num2".
	casadec1:=10; // Retorno ao valor inicial para o novo ciclo de "num1".
	num1:=aux; // Retorno ao valor inicial para o novo ciclo de "num1".
	carry:=0; // Vai-um é zerado pois ele ja foi incluido no "produto".
	while num1<>0 do
		begin // Inicio deste loop.
		produto:=produto+(carry+(num1 mod 10)*(num2 mod 10)mod 10)*(casadec1*casadec2 div 100); //1º algarismo do multiplicador vezes 1º algarismo do multiplicando somado com "carry" são multiplicados pela casa decimal atual formando um novo valor a ser inserido em "produto".
		carry:=(carry+(num1 mod 10)*(num2 mod 10))div 10; // Novo carry é calculado.
		num1:=num1 div 10; // Retira-se o 1º algarismo de "num1".
		casadec1:=casadec1*10; // Aumenta-se a casa decimal atual em relação ao "num1".
		end; // Fim deste loop.
	produto:=produto+carry*casadec1*casadec2 div 100; // Caso tenha o ultimo vai-um, ele é inserido em "produto" a esquerda.
	num2:=num2 div 10; // Retira-se o 1º algarismo de "num1".
	end; // Fim deste loop.
writeln('O valor do produto é: ',produto); // Apresentação do resultado.
end. // Fim do processo.
