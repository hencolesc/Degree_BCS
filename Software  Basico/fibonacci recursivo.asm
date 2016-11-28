		.data
app:		.asciiz	"Digite n natural para calcular o n-esimo nº da sequencia de fibonacci: "
		.globl	main
		.text
	
main:		li 	$v0, 4		# Codigo para imprimir string
		la	$a0, app	# Carrega endereço de app
		syscall			# Imprime app
		li	$v0, 5		# Codigo para ler inteiro
		syscall			# Le um inteiro
		move	$a0, $v0	# Prepara 1º argumento
		jal	fib		# Transfere controle para sub rotina fib
		move	$a0, $v0	# Prepara inteiro para imprimir
		li	$v0, 1		# Codigo para imprimir inteiro
		syscall
		li	$v0, 10		# Codigo para terminar execução
		syscall			# FIM DO PROGRAMA!
		
######################################### Sub Rotina: fib - Fibonnaci recursivo ######################################################

fib:		ble	$a0, 2, base	# Base da recursão n<=2
		sub	$sp, $sp, 8	# Aloca 8 bytes na pilha
		sw	$ra, 4($sp)	# Empilha endereço de retorno
		sw	$a0, 0($sp)	# Empilha 1º argumento
		sub	$a0, $a0, 1	# Prepara 1º argumento
		jal	fib		# Recursão nº1
		lw	$a0, 0($sp)	# Desempilha 1º argumento
		sub	$a0, $a0, 2	# Prepara 1º argumento
		sw	$v0, 0($sp)	# Empilha fib(n-1)
		jal	fib		# Recursão nº2
		lw	$t0, 0($sp)	# Desempilha fib(n-1)
		lw	$ra, 4($sp)	# Desempilha endereço de retorno
		add	$sp, $sp, 8	# Desaloca 8 bytes da pilha
		add	$v0, $t0, $v0	# fib(n)=fib(n-1)+fib(n-2);
		jr	$ra		# Retorna controle para quem chamou
base:		sub	$v0, $a0, 1	# fib(1)=0 e fib(2)=1
		jr	$ra		# Retorna controle para quem chamou