#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 6

static long int num_steps = NUM_THREADS * 100000000;
double step;

int main(){
	int i, nthreads;
	double soma_thread[NUM_THREADS], soma_total = 0.0, pi;
	
	step = 1.0/(double) num_steps;
	
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		long int i;
		double x, sum;
		int nthrds, id = omp_get_thread_num(); // ID da thread
		
		nthrds = omp_get_num_threads();
		
		if (id == 0) nthreads = nthrds;
		
		for (i = id, soma_thread[id] = 0, sum = 0; i < num_steps; i += nthrds){
			x = (i + 0.5) * step; // largura do retangulo
			sum = sum + 4.0 / (1.0 + x*x); // sum += area do retangulo
		}
		
		soma_thread[id] = sum; // salva soma parcial
		
	}
	
	for (i = 0; i < NUM_THREADS; i++){
		soma_total += soma_thread[i]; // soma as partes para compor a soma total
	}
	
	pi = step * soma_total;
	
	printf("aproximacao de pi = %.10f\n", pi); // mostra na tela a aproximacao de pi
	
	return 0;
	
}
