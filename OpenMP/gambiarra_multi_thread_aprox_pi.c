#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 6
#define PAD 64

static long int num_steps = NUM_THREADS * 1000000000;
double step;

int main(){
	int i, nthreads;
	double soma_thread[NUM_THREADS][PAD], soma_total = 0.0, pi;
	
	step = 1.0/(double) num_steps;
	
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		long int i;
		double x, sum;
		int nthrds, id = omp_get_thread_num(); // ID da thread
		
		nthrds = omp_get_num_threads(); // num d threads que o S.O. liberou
		
		if (id == 0) nthreads = nthrds;
		
		for (i = id, soma_thread[id][0] = 0.0, sum = 0.0; i < num_steps; i += nthrds){
			x = (i + 0.5) * step; // largura do retangulo
			sum = sum + 4.0 / (1.0 + x*x); // sum += area do retangulo
		}
		
		soma_thread[id][0] = sum; // salva soma parcial
		
		// printf("%ld iteracoes na thread %d\n", i, id);
		
	}
	
	for (i = 0; i < nthreads; i++){
		soma_total += soma_thread[i][0]; // soma as partes para compor a soma total
	}
	
	pi = step * soma_total;
	
	printf("aproximacao de pi = %.10f\n", pi); // mostra na tela a aproximacao de pi
	
	return 0;	
}
