	.data
espaço:	.asciiz		" "			# String espaço em branco
p_linha:.asciiz		"\n"			# String para pular linha
	.globl	main
	.text

main:	la	$s0, espaço		# Guarda endereço de string
	la	$s1, p_linha		# Guarda endereço de string
	li	$t0, 5			# n=5;
	li	$t1, 1			# i=1;
	li	$t2, 1			# f=1;
	mult	$t1, $t2		# f*i
loop:	mflo	$t2			# f = 16 bits menos significativos de f*i;
	addi	$t1, $t1, 1		# i++;
	bleu	$t1, $t0, loop		# Condição para continuar o loop
	mult	$t1, $t2		# f*i => instrução util após o delayed branch
	jal	imprime			# Chama a função imprime
	move	$t1, $t0		# i=n => instrução util após delayed jump
	mult	$t2, $t1		# f*i
loop2:	bgtz	$t1, fim		# Condição para o loop2
	nop				# Instrução nula para o branch delayed
	mflo	$t2			# f = 16 bits menos significativos de f*i
	addi	$t1, $t1, -1		#i--;
	j	loop2			# Reinicia o loop2
	mult	$t2, $t1		# f*i => instrução util para delayed jump
fim:	jal	imprime			# Chama a função imprime
	nop				# Instrução nula para o delayed jump
	li	$v0, 10			# Codigo para terminar a execução
	syscall				# FIM DO PROGRAMA!
	
######################################### SUBROTINA DE IMPRESSÃO #################################

imprime:li	$v0, 1			# Codigo para imprimir inteiro
	move	$a0, $t0		# Passa valor inteiro para imprimir
	syscall
	li	$v0, 4			# Codigo para imprimir string
	move	$a0, $s0		# Passa endereço de espaço para imprimir
	syscall		
	li	$v0, 1			# Codigo para imprimir inteiro
	move	$a0, $t2		# Passa valor inteiro para imprimir
	syscall	
	li	$v0, 4			# Codigo para imprimir string
	move	$a0, $s1		# Passa endereço de p_linha para imprimir
	syscall
	jr	$ra			# Retorna logo abaixo da chamada desta função
	li	$t2, 1			# f=1 => instrução util após delayed jump