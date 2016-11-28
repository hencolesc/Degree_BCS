program ALgLista3Ex3; // Exercicio 3 da lista 3. Autor: Henrique Colodetti Escanferla.

var num1, num2, aux: integer; // num1=> 1 numero 1; num2=> numero 2; aux=> auxiliar para a troca de valores entre "num1" e "num2".

begin // Inicio do processo.

writeln('Este programa informará o mdc entre dois inteiros.'); // App do programa e sua função.
write('Insira um numero inteiro: '); // Pedido de "num1".
readln(num1); // Leitura de "num1".
write('Insira outro numero inteiro: '); // Pedido de "num2".
readln(num2); // Leitura de "num2".
if num2>num1 then // No caso de igual, não faz diferença no processo.
	begin //  Inicio deste if-then.
	aux:=num2; // "aux" salva "num1" para a troca de valores.
	num2:=num1; // "num1" fica com o maior valor.
	num1:=aux; // "num2" fica com o menos valor.
	end; // Fim deste if-then.
while num1 mod num2<>0 do
	begin // Inicio deste loop.
	aux:=num1; // "aux" salva "num1" para a troca de valores.
	num1:=num2; // "num1" recebe "num2"
	num2:= aux mod num2; // "num2" recebe o resto do "num1" anterior com "num2".
	end; // Fim deste loop.
writeln('Valor do MDC: ',num2); // App do resultado.
end. // Fim do processo.
