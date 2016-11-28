#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

double timestamp(void)
{
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

void init_matrix(double *a, int h, int w, double first)
{
	int i, j;
	for (i = 0; i < h; ++i)
		for (j = 0; j < w; ++j)
			a[i*w + j] = first + i*w + j;
}

void func(double *a, double *b, double *c, int h, int w)
{
	int i, j;

	for (i = 0; i < h; ++i)
		for (j = 0; j < w; ++j)
			 a[i*w + j] = b[i*w + j] * sin(i*M_PI/180.0) + c[i*w + j] * cos(j*M_PI/180.0);
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "usage: %s HEIGHT WIDTH\n", argv[0]);
		exit(1);
	}

	int height = atoi(argv[1]);
	int width = atoi(argv[2]);
	int iter = 10000;

	if (height <=0 || width <=0 || height > 16*1024 || width > 16*1024) {
		fprintf(stderr, "error: out of range\n");
		exit(2);
	}

	double *a = (double *)malloc(height*width*sizeof(double));
	double *b = (double *)malloc(height*width*sizeof(double));
	double *c = (double *)malloc(height*width*sizeof(double));

	init_matrix(b, height, width, 0);
	init_matrix(c, height, width, 100);

    double start = timestamp();

    int i;
    for(i = 0; i < iter; ++i)
        func(a, b, c, height, width);

    double end = timestamp();
    printf("wall-clock: %f\n", end - start);

	free(a);
	free(b);
	free(c);

	return 0;
}

