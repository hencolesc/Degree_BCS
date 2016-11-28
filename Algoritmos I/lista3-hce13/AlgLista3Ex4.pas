program AlgLIsta3Ex4; // Exercicio 4 da lista 3. Autor: Henrique Colodetti Escanferla.

var a1,a2,a3,a4,a5,a6,a7,a8,a9: integer; // Inteiros do quadrado mágico. Da esquerda para a direita, de cima para baixo.
achou: boolean; // Indicará quando deve parar o loop pois uma solução foi encontrada.

begin // Inicio do processo.

writeln('Este programa buscará uma solução para o quadrado magico em que a soma de qualquer linha, coluna e diagonal de seus inteiros é igual a 15.'); // App do programa e sua função.
a9:=0; // Isto é necessario para que o 1º while funcione que, após isto, definirá todos os outros "a"s.
achou:=true; // Será falso quando encontrar uma solução.
while (a9<>10)and(achou) do
	begin // Inicio deste loop.
	a8:=0; // Volta a ser zero para a nova combinação de valores.
  a9:=a9+1; // Incrementação de "a9" quando todos os "a8"s foram testados.
  a9:=a9 mod 10; // Se a9=10 => a9=0. Se -1 < a9 < 10 => a9=a9.
	while (a8<>10)and(achou) do
		begin // Inicio deste loop.
		a7:=0; // Volta a ser zero para a nova combinação de valores.
    a8:=a8+1; // Incrementação de "a8" quando todos os "a7"s foram testados.
		while (a7<>10)and(achou) do
			begin // Inicio deste loop.
			a6:=0; // Volta a ser zero para a nova combinação de valores.
      a7:=a7+1; // Incrementação de "a7" quando todos os "a6"s foram testados.
			while (a6<>10)and(achou) do
				begin // Inicio deste loop.
				a5:=0; // Volta a ser zero para a nova combinação de valores.
        a6:=a6+1; // Incrementação de "a6" quando todos os "a5"s foram testados.
				while (a5<>10)and(achou) do
					begin // Inicio deste loop.
					a4:=0; // Volta a ser zero para a nova combinação de valores.
         	a5:=a5+1; // Incrementação de "a5" quando todos os "a4"s foram testados.
					while (a4<>10)and(achou) do
						begin // Inicio deste loop.
						a3:=0; // Volta a ser zero para a nova combinação de valores.
            a4:=a4+1; // Incrementação de "a4" quando todos os "a3"s foram testados.
						while (a3<>10)and(achou) do
							begin // Inicio deste loop.
							a2:=0; // Volta a ser zero para a nova combinação de valores.
              a3:=a3+1; // Incrementação de "a3" quando todos os "a2"s foram testados.
							while (a2<>10)and(achou) do
								begin // Inicio deste loop.
								a1:=0; // Volta a ser zero para a nova combinação de valores.
                a2:=a2+1; // Incrementação de "a2" quando todos os "a1"s foram testados.
								while (a1<>10)and(achou) do
									begin // Inicio deste loop.
									if (a1+a2+a3=a4+a5+a6)and(a7+a8+a9=a1+a2+a3)and(a1+a4+a7=a2+a5+a8)and
									(a3+a6+a9=a1+a4+a7)and(a1+a2+a3=a1+a4+a7)and(a1+a5+a9=a3+a5+a7)and(a1+a2+a3=a1+a5+a9)
									and(a1+a2+a3=15)and(a1<>a2)and(a1<>a3)and(a1<>a4)and(a1<>a5)and(a1<>a6)and(a1<>a7)and(a1<>a8)and(a1<>a9)and(a2<>a3)and(a2<>a4)and(a2<>a5)and(a2<>a6)and(a2<>a7)and(a2<>a8)and(a2<>a9)and(a3<>a4)and(a3<>a5)and(a3<>a6)and(a3<>a7)and(a3<>a8)and(a3<>a9)and(a4<>a5)and(a4<>a6)and(a4<>a7)and(a4<>a8)and(a4<>a9)and(a5<>a6)and(a5<>a7)and(a5<>a8)and(a5<>a9)and(a6<>a7)and(a6<>a8)and(a6<>a9)and(a7<>a8)and(a7<>a9)and(a8<>a9) then // Isto abrange as condições e restrições do exercicio.
										achou:=false // Indica que encontrou solução e os loops devem parar.
									else
										a1:=a1+1; // Incrementação de "a1" se não achou solução.
									end; // Fim deste loop.
								end; // Fim deste loop.
							end; // Fim deste loop.
						end; // Fim deste loop.
					end; // Fim deste loop.
				end; // Fim deste loop.
			end; // Fim deste loop.
		end; // Fim deste loop.
	end; // Fim deste loop.
writeln('O 1º resultado encontrado é mostrado abaixo:');
writeln(a1,'	',a2,'	',a3);
writeln;
writeln(a4,'	',a5,'	',a6);
writeln;
writeln(a7,'	',a8,'	',a9); // App da 1ª solução encontrada.
end. // Fim do processo.
