program AlgLista5Ex1; // Exercicio 1 da lista 5. Autor: Henrique Colodetti Escanferla.

type vetor=array[1..100] of real; // Criação do tipo de variável "vetor".

var u, v, w: vetor; // Variáveis globais: u=> 1ª seq. de nºs; v=> 2ª seq. de nºs e w=> Seq. do resultado.
tamu, tamv, tamw: integer; // tamu, tamv e tamw são os tamanhos de u, v, e w respectivamente.

procedure escreve_vetor(v:vetor; tamv:integer); // "escreve_vetor" app nºs do vetor até tal indice.

var i:integer; // Variáveis locais: i=> Varia de um à tamv.

begin // Inicio deste procedimento.
i:=0; // Começa com zero.
while tamv<>i do
	begin // Inicio deste loop.
	i:=i+1; // Prox. indice de "v".
	write(v[i]:3:1,' '); // App d um nº do vetor "v".
	end; // Fim deste loop.
end; // Fim deste procedimento.

procedure ler_vetor(var v:vetor; var i:integer); // "ler_vetor" recebe vetor, indice inicial e le entrada retornando vetor com a entrada e seu tamanho.

var aux:integer; // Variáveis locais: aux=> recebera a sequencia.

begin // Inicio deste procedimento.
read(aux); // Le 1º numero da sequencia.
while aux<>0 do
	begin // Inicio deste loop.
	v[i]:=aux; // Insere valor no indice do vetor.
	i:=i+1; // Incrementa o indice.
	read(aux); // Le prox. nº da sequencia.
	end; // Fim deste loop.
i:=i-1; // Retira-se o 0 na contagem.
end; // Fim deste procedimento.

procedure intercala(u, v: vetor; var w:vetor; tamu, tamv: integer; var tamw:integer); // "intercala" cria um vetor intercalando valores alternados de u e v como foi pedido.

var i, j, k: integer; // Variaveis locais: i=> indices de "w".; j=> indices de "u" e k=> indices de "v".

begin // Inicio deste procedimento.
i:=0; j:=0; k:=0; // Começam todos com zero.
tamw:=tamu+tamv; // Isto sempre ocorre pelo que foi pedido.
while i<tamw do
	begin // Inicio deste loop.
	if j<tamu then
		begin // Inicio deste if-then.
		i:=i+1; // Gera indice atual de "w".
		j:=j+1; // Gera indice atual de "u".
		w[i]:=u[j]; // "w" recebe valor de "u".
		end; // Fim deste if-then.
	if k<tamv then
		begin // Inicio deste if-then.
		i:=i+1; // Gera indice atual de "w".
		k:=k+1; // Gera indice atual de "v".
		w[i]:=v[k]; // "w" recebe valor de "v".
		end; // Fim deste if-then.
	end; // Fim deste loop.
end; // Fim deste procedimento.

begin // Inicio do processo.
tamu:=1; tamv:=1; tamw:=1; // Indices iniciais de u,v e w para "ler_vetor".
write('Digite uma sequência de nºs: '); // Pedido de "u".
ler_vetor(u, tamu); // Chama-se "ler_vetor".
write('Digite uma sequência de nºs: '); // Pedido de "v".
ler_vetor(v, tamv); // Chama-se "ler_vetor".
intercala(u, v, w, tamu, tamv, tamw); // Chama-se "intercala".
escreve_vetor(w, tamw); // Chama-se "escreve_vetor".
writeln; // Pula linha.
end. // Fim do processo.
