#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 6

static long long num_steps = NUM_THREADS * 1000000000LL;
double step;

int main(){
	double pi = 0.0;
	
	step = 1.0/(double) num_steps;
	
	#pragma omp parallel num_threads(NUM_THREADS)
	{
		long int i;
		double x, sum = 0.0;
		
		#pragma omp for schedule(static)
		for (i = 0; i < num_steps; i++){
			x = (i + 0.5) * step; // largura do retangulo
			sum = sum + 4.0 / (1.0 + x*x); // sum += area do retangulo
		}
		
		#pragma omp atomic
		pi += step * sum;
		
	}
	
	printf("aproximacao de pi = %.10f\n", pi); // mostra na tela a aproximacao de pi
	
	return 0;
	
}
