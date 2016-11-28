program AlgLista2Ex3; // Exercício 3 da Lista 2 de Algoritmos.

var 
num, numsv, pal: integer; // Variáveis inteiras para guardar "num" em "numsv" que será modificado para a comparação com "pal" se é palíndromo ou não.

begin // Começo do processo.

writeln('Este algoritmo analisará um numero inteiro para informar se ele é palíndromo ou não.'); // Apresentação do algoritmo e sua função.
write('Digite um valor inteiro: '); // Pedido de "num".
read(num); // Leitura de "num".
numsv:=num; // "num" é salvo em "numsv" pois ele será modificado no processo. (Ver linha 16)
pal:=0; // "pal" guardará "num' ao contrário. Inicialmente ele tem que ser 0. (Ver linha 15)
	while num div 10<>0 do // Divisões suscessivas de 10 informarão os digitos de "num".
		begin // Início dos comandos deste loop.
		pal:=10*pal+num mod 10; // Isto extrai os digitos de "num" e os coloca ao contrário. (Ver linha 12)
		num:=num div 10; // Preparação de "num" para a extração do próximo digito.
		end; // Fim dos comandos deste loop.
pal:=10*pal+num mod 10; // Isto foi necessário pois o loop termina antes que o ultimo digito seja inserido em "pal". Neste momento, ja que "num" carrega o digito faltante, a linha 15 foi duplicada aqui.
	if numsv=pal then // Análise de "num" ser palíndromo ou não. "pal" tem que ser igual a "numsv".
		writeln('Sim, eh palíndromo') // Apresentação do resultado como foi pedido em caso verdade.
		else
		writeln('Não, eh palíndromo'); // Aprsentação do resultado como foi pedido em caso falso.

end. // Fim do processo.
