program lista1ex2; (* Exercício 2 da Lista 1 de ALgorítmos. Autor: Henrique Colodetti Escanferla *)

var C, F: real; (* Para que o algoritmo aceite qualquer valor específico com varias casas decimais foi utilizado variáveis reais. C => Temperatura em Celsius, F => Temperatura em Farenheit. *)

begin (* Começo do processo de conversão Celsius-Farenheit. *)

writeln('Este algoritmo fornecerá uma temperatura em Farenheit a partir de um valor em Celsius.'); (* Apresentação do algoritmo e sua função. *)
write('Digite o valor da temperatura em Celsius: '); (* Aqui é fornecido a temperatura em Celsius. *)
readln(C); (* Leitura da variável Celsius. *)
F := 9*C/5+ 32; (* Fórmula inversa da fornecida que convertia Farenheit para Celsius. Foi isolado o F e obtida a fórmula usada aqui. *)
writeln('O valor correspondente à temperatura em Celsius fornecida é de: ',F:4:2,' F°'); (* Fornecimento do resultado para o usuário *)

end. (* Fim do algoritmo *)
