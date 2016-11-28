program lista3ex1; // Exercício 1 da Lista 3 de Algorítmos. Autor: Henrique Colodetti Escanferla.

var num, contp, divisor: integer; // Variáveis inteiras para o processo. num=> numero natural variavel; contp=> contador de primos; divisor=> dividirá "num".
divide: boolean; // divide=> indicará se encontrou algum divisor ou não de "num".

begin // Início do processo.

num:=1; // Começa com o menor natural.
contp:=0; // Contador de primos começa com 0.
while contp<>23 do // Loop ocorre até que o vigésimo terceiro primo seja encontrado.
	begin // Início do loop.
	num:=num+1;
	divide:=true;
	divisor:=1; // Começa com o menor natural.
	while divide do // Loop ocorre até que o primo seja fatorado ou até que encontrem algum divisor de resto zero.
		begin // Início deste loop.
		divisor:=divisor+1; // Gera o divisor.
		if num mod divisor=0 then // Encontrou divisor de resto zero.
			divide:=false; // Acusa a existencia de divisor de resto zero.
		end; // Fim deste loop.
if num=divisor then // Encontrou um primo, ou seja, teve um único divisor de "num" igual a ele mesmo.
	contp:=contp+1; // Conta-se "1".
	end; // Fim deste loop.
writeln('O vigésimo terceiro primo é o número: ',num); // Apresentação do resultado.

end. // Fim do processo.
