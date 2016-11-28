program AlgLista1Ex3; (* Algoritmo do exercício 3 da Lista 1. Autor: Henrique Colodetti Escanferla. *)

var vkm, vml: real; (* vkm => Velocidade em km/h, vml => Velocidade em ml/h. Foi optado variáveis reais para casos bem específicos. *)

begin (* Começo do processo de conversão *)

writeln('Este algoritmo irá converter um valor fornecido em km/h num valor em ml/h'); (* Apresentação do algoritmo e sua função. *)
write('Digite o valor da velocidade em km/h: '); (* Aqui é pedido o valor de vkm. *)
readln(vkm); (* Aqui é recebido o valor de vkm. *)
vml := vkm/1.609344; (* Relação entre km/h e ml/h *)
writeln('O valor da velocidade é de: ',vml:6:3,' ml/h'); (* O resultado é apresentado para o usuário *)

end. (* Fim do processo de conversão *)
