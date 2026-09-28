#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_io.h"
#include "solve.h"

int main(int argc, char *argv[])
{
	double *a;
	double *x;
	int *permutation;
	int task = 13, n, p, k, res;
	double t, r1 = 0.0, r2 = 0.0;
	char *name = 0;
	io_status ret;
	if (!((argc == 4 || argc == 5) && sscanf(argv[1], "%d", &n) == 1 && sscanf(argv[2], "%d", &p) == 1 && sscanf(argv[3], "%d", &k) == 1 && (((k > 0 && k <= 4) && argc == 4) ||(k == 0 && argc == 5))))
	{
		printf("Usage: %s n p k [name] \n", argv[0]);
		return 0;
	}
	if (n < 0)
	{
		printf("Error lenght! \n");
		return 1;
	}
	if (argc == 5)
		name = argv[4];
	a = (double *)malloc(n * n * sizeof(double));
	if (!a)
	{
		printf("Not enought memory!\n");
		return 2;
	}
	if (name)
	{
		ret = read_matrix(a, n, name);
		do
		{
			switch (ret)
			{
				case SUCCESS:
					continue;
				case ERROR_OPEN:
					printf ("Cannot open %s\n", name);
					break;
				case ERROR_READ:
					printf ("Cannot read %s\n", name);
					break;
			}
			free(a);
			return 3;
		}while(0);
	}
	else
	{
		init_matrix(a, n, k);
	}
	x = (double *)malloc(n * n * sizeof(double));
	if (!x)
	{
		printf("Not enought memory!\n");
		free(a);
		return 2;
	}
	permutation = (int *)malloc(n * sizeof(int));
        if (!permutation)
        {
                printf("Not enought memory!\n");
                free(a);
		free(x);
                return 2;
        }
	printf("Initial matrix a: \n");
	print_matrix(a, n, p);
	t = clock();
	res = solve(a, x, permutation, n);
	t = (clock() - t) / CLOCKS_PER_SEC;
	if (res != 1)
	{
		printf("Error!\n");
		free(a);
		free(x);
		free(permutation);
		return 3;
	}

	printf("Result matrix: \n");
	print_matrix(x, n, p);
	if (name)
        {
                ret = read_matrix(a, n, name);
        }
        else
        {
                init_matrix(a, n, k);
        }
	if (n <= 4000)
	{
		r1 = r(a, x, n);
		r2 = r(x, a, n);
	}
	printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);
	free(a);
        free(x);
        free(permutation);
	return 0;
}
