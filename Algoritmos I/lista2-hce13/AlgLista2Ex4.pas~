program ALgLista2Ex4; // Exercicio 4 da lista 2 de algoritmos. Autor: Henrique Colodetti Escanferla.

var
k, x, i: integer; // k=> taxa de alternancia; x=> sequencia de inteiros; i=> contador de pares/impares.
a, p: boolean; // a=> guarda o resultado final; p=> indica se o nº anterior é par/impar.

begin // Começo do processo.

writeln('Este programa informará a k-alternância ou não de uma sequência dada.'); // App do programa.
write('Digite o valor de k: '); // Pedido de k.
readln(k); // Leitura de k.
write('Digite uma sequência de inteiros espaçados entre sí: '); // Pedido de x.
read(x); // Ler 1º nº. Read para que o programa guarde a sequência no buffer e use-o periodicamente.
i:=0; // Contador de pares/impares começa obviamente com zero.
a:=true; // Por suposição, o resultado é verdadeiro. Caso encontre erro ele será falso.
if x mod 2=0 then // Isto é necessário para os if's do loop.
	p:=false // Falso para nº par.
else
	p:=true; // Verdadeiro para nº impar.
while (x<>0)and a do // 0 na sequência indica seu fim. Falso em a indica erro em x e interrompe o loop.
	begin // Inicio dos comandos deste loop.
	if ((x mod 2<>0)xor p)and(i=k) then // Caso ciclo alternou sem erro.
		begin // Inicio dos comandos caso alternou sem erro.
		p:=not p; // p é seu inverso pois o ciclo alternou.
		i:=1; // Contando este nº temos que i=1.
		end // Fim dos comandos caso alternou sem erro.
	else // Aqui existem duas possibilidades: ciclo continuou sem erro ou houve erro.
		if (not((x mod 2<>0)xor p))and(i<>k) then // Caso ciclo continuou sem erro.
			i:=i+1 // Conta-se este nº incrementando i.
		else // Todos os outros possíveis casos são erros.
			a:=false; // Sinal de que a hipótese é errada, que houve erro.
	read(x); // Leitura do próx. nº da sequencia.
	end; // Fim dos comandos deste loop.
if (a)and(i=k) then // i=k cobre o caso da sequência ter errado só no ultimo ciclo de pare(s)/impare(s).
	writeln('A sequência inserida é ',k,'-alternante. #FIM DO PROGRAMA#') // Resultado positivo.
else
	writeln('A sequência inserida não é ',k,'-alternante. #FIM DO PROGRAMA#'); // Resultado negativo.
end. // Fim do processo.
