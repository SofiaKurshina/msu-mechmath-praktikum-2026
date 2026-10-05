#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"
#include "array_io.h"

io_status read_matrix(double *a, int n, const char *name)
{
	int i, j;
	FILE *fp;
	if (!(fp = fopen(name, "r")))
		return ERROR_OPEN;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (fscanf(fp, "%lf", a + i * n + j) != 1)
			{
				fclose(fp);
				return ERROR_READ;
			}
		}
	}
	fclose(fp);
	return SUCCESS;
}

void print_matrix(const double *a, int n, int p)
{
	int np = (n > p ? p : n);
	int i, j;
	for (i = 0; i < np; i++)
	{
		for (j = 0; j < np; j++)
			printf(" %10.3e", a[i * n + j]);
		printf("\n");
	}
}

int max(int m, int n)
{
	if (n > m)
		return n;
	return m;
}

double f1(int n, int i, int j)
{
	i++;
	j++;
	return n - max(i, j) + 1;
}

double f2(int n, int i, int j)
{
        (void)n;
        i++;
        j++;
	if (i > j)
		return i;
	return j;
}

double f3(int n, int i, int j)
{
	(void)n;
        i++;
        j++;
	return abs(i - j);
}

double f4(int n, int i, int j)
{
	(void)n;
        i++;
        j++;
	return 1. / (i + j - 1);
}

void init_matrix(double *a, int n, int k)
{
	double (*f[])(int, int, int) = {f1, f2, f3, f4};
	double (*q)(int, int, int);
	int i, j;
	q = f[k-1];
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			a[i * n + j] = (*q)(n, i, j);
}

double r(double * a, double * x, int n) // Вычисление нормы невязки 
{
	int i, j, k;
    	double sm = 0, sm1 = 0, mx = 0;
    	for (j = 0; j < n; ++j) 
	{
        	sm1 = 0;
        	for (i = 0; i < n; ++i) 
		{
            		sm = 0;
            		for (k = 0; k < n; ++k) 
			{
                		sm += (a[i * n + k] * x[k * n + j]);
            		}
			if (i == j) 
			{
                		sm -= 1.0;
            		}
            		sm1 += fabs(sm);
        	}
        	if (sm1 > mx) 
		{
            		mx = sm1;
        	}
    	}	
    	return mx;
}
