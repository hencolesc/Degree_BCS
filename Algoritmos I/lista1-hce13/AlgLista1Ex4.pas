program AlgLista1Ex4; (* Exercícios 4 da lista 1 de Algoritmos. Autor: Henrique Colodetti Escanferla. *)

var g, m, s: longint; (* Já que o processo só envolve inteiros, todas as variaveis são declaradas como inteiros. *)

begin (* Começo do processo. *)

writeln('Este algoritmo irá converter um dado valor inteiro em segundos para um valor inteiro correspondente em graus, minutos e segundos.'); (* Apresentação do algoritmo e sua função. *)
writeln('Digite o valor inteiro em segundos: '); (* Requerimento da entrada para o usuário. *)
read(s); (* Leitura da variável fornecida pelo usuário. *)

g:=(s)div(3600); (* Um grau contém 3600 segundos, assim justifica-se esta expressão. *)
s:=(s)mod(3600); (* Retirada do valor de "s" ja convertido deixando o restante ainda não convertido *)
m:=(s)div(60); (* O resto da divisão anterior dá a quantidade de segundos a ser incluida em minutos. Um minuto contém 60 segundos. *)
s:=(s)mod(60); (* Retirada do valor de "s" ja convertido em minutos deixando o restante agora em segundos. *)
g:=(g)mod(360); (* Retirada de voltas inteiras para fornecer o valor mínimo equivalente *)
writeln('O valor correspondente mínimo, desconsiderando as voltas inteiras, é de: ',g,' Graus, ',m,' Minutos e ',s,' Segundos.'); (* Apresentação da saída do processo conforme foi pedido. *)

end. (* Fim do Processo. *)
