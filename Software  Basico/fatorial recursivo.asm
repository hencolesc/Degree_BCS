		.data
app:		.asciiz	"Digite um inteiro n para calcular n!: "
		.globl	main
		.text

main:		la,	$a0, app		# Le endereço de app
		li,	$v0, 4			# Codigo para imprimir string
		syscall
		li,	$v0, 5			# Codigo para ler inteiro
		syscall
		move	$a0, $v0		# Prepara inteiro lido como 1º argumento
		jal	fat			# Passa o controle para a sub rotina fat
		move	$a0, $v0		# Salva retorno de fat para imprimir
		li,	$v0, 1			# Codigo para imprimir inteiro
		syscall
		li,	$v0, 10			# Codigo para terminar execução
		syscall				# FIM DO PROGRAMA!
	
##################### SUB ROTINA FAT: Fatorial Recursivo #######################################

fat:		ble	$a0, 1, fim_base	# Base da recursão
		sub	$sp, $sp, 8		# Aloca 8 bytes na pilha
		sw	$a0, 0($sp)		# Empilha 1º argumento
		sw	$ra, 4($sp)		# Empilha endereço de retorno
		sub	$a0, $a0, 1		# (n-1)!
		jal	fat			# Chamada recursiva
		lw	$a0, 0($sp)		# Desempilha 1º argumento
		lw	$ra, 4($sp)		# Desempilha endereço de retorno
		add	$sp, $sp, 8		# Desaloca 8 bytes da pilha
		mult	$a0, $v0		# n * (n-1)!
		mflo	$v0			# n! = n * (n-1)! - 32 bits menos significativos
		jr	$ra			# Retorna controle para quem chamou
fim_base:	li	$v0, 1			# 1!=1
		jr	$ra			# Retorna controle para quem chamou
