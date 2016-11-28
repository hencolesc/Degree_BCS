	.data
origem:	.asciiz	"abcd-efgh-ijkl-"      	# string origem com \0 no final
destino:.asciiz	"               "	# string destino "vazio" c/ \0 no final
p_linha:.asciiz "\n"			# string auxiliar para pular linha na tela
	.text
	.globl main

main:	la	$t0, origem	# Carrega endereço inicial da string origem
	la	$t1 destino	# Carrega endereço inicial da string destino
	li	$t3, 0		# i=0;
loop:	lb	$t2, 0($t0)	# Carrega char de origem
	sb	$t2, 0($t1)	# destino[$t1]=origem[$t0];
	addi	$t3, $t3, 1	# i++;
	beqz	$t2, fim	# Char '\0' indica fim da string e fim deste loop
	addi	$t0, $t0, 1	# $t0++;
	addi	$t1, $t1, 1	# $t1++;
	j	loop		# Reinicia o loop
################################# IMPRESSÃO ####################################
fim:	la  	$a0, origem	# load address of the print heading string
	li  	$v0, 4         	# specify Print String service
	syscall              	# print the heading string
      
	la  	$a0, p_linha	# load address of the print heading string
	li  	$v0, 4         	# specify Print String service
	syscall          	# print the heading string

	la  	$a0, destino	# load address of the print heading string
	li  	$v0, 4         	# specify Print String service
	syscall          	# print the heading string
	
	la  	$a0, p_linha	# load address of the print heading string
	li  	$v0, 4         	# specify Print String service
	syscall          	# print the heading string
	
	move	$a0, $t3	# load integer from register
	li  	$v0, 1         	# specify Print integer service
	syscall          	# print the integer
	
	li	$v0, 10		# Codigo para terminar a execução
	syscall			# Termina a execução