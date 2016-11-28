program AlgLista1Ex5; (* Exercício 5 da Lista 1 de Algoritmos. *)

var a, b, c, d: integer; (* Variáveis inteiras para indicar numeradores e denominadores de frações. *)

begin (* Começo do processo. *)

writeln('Este algoritmo irá fornecer a soma e o produto equivalente de duas frações fornecidas por você.'); (* Apresentação do algoritmo e sua função. *)
writeln('Digite o numerador da primeira fração desejada: '); (* Pedido de "a" ao usuário. *)
read(a); (* Leitura de "a". *)
writeln('Digite o denominador da primeira fração desejada: '); (* Pedido de "b" ao usuário. *)
read(b); (* Leitura de "b". *)
writeln('Digite o numerador da segunda fração desejada: '); (* Pedido de "c" ao usuário. *)
read(c); (* Leitura de "c". *)
writeln('Digite o denominador da segunda fração desejada: '); (* Pedido de "d" ao usuário. *)
read(d); (* Leitura de "d". *)
writeln('A fração correspondente a soma das 2 frações fornecidas é de: ',a*d+b*c,' sobre ',b*d); (* Apresentação da fração soma para o usuário utilizando o mmc e convertendo os numeradores adequadamente. *)
writeln('A fração correspondente ao produto das 2 frações fornecidas é de: ',a*c,' sobre ',b*d); (* Apresentação da fração produto para o usuário multiplicando os numeradores e os denominadores. *)

end. (* Fim do processo. *)
