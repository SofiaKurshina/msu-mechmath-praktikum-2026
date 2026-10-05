#include <stdio.h>
#include <stdlib.h>
#include "solve.h"
#include "array_io.h"
#include <math.h>

//double Fabs(double x)
//{
//        if (x < 0.0)
//                return -x;
//        return x;
//}

//double Fmax(double a, double b)
//{
//	if (a > b)
//		return a;
//	return b;
//}

int is_equal(double a, double b, double c) 
{
    return fabs(a - b) <= c;
}

double nrm(double *a, int n) // Вычисление нормы матрицы
{
	int i, j;
	double sm = 0, mx = 0;
	for (j = 0; j < n; j++)
	{
		sm = 0;
		for (i = 0; i < n; i++)
		{
			sm += fabs(a[i * n + j]);
		}
		if (sm > mx)
			mx = sm;
	}
	return mx;
}

int solve(double *a, double *x, int *permutation, int n)
{
	int i, j, k, tmp, step1, step2;
      	int mx_j;
      	double mx, c, norm, el, e;
      	e = 1e-16;
      	norm = nrm(a, n);
      	c = e * norm;   // если главный элемент меньше этого значения, матрица считается вырожденной      	
        for (i = 0; i < n; i++) 
      	{
		    for (j = 0; j < n; j++) 
          	{
                	x[i * n + j] = (i == j);
          	}
          	permutation[i] = i; 
      	}
        // Прямой ход Гаусса (привожу матрицу к верхнетреугольному виду)
      	for (i = 0; i < n; i++) 
      	{
	    	mx = a[i * n + i];
          	mx_j = i;
          	for (j = i + 1; j < n; j++) 
          	{
                	el = a[i * n + j];
                	if (fabs(el) > fabs(mx)) 
                	{
                    		mx = el;
                    		mx_j = j; 
                	}	
          	}	
          	if (fabs(mx) <= c) 
          	{
                	return 0; 
          	}
          	if (mx_j != i) 
          	{
                	for (k = 0; k < n; k++) 
                	{
                		step1 = k * n;
                    		el = a[step1 + i];
                    		a[step1 + i] = a[step1 + mx_j];
                    		a[step1 + mx_j] = el;
                	}
                	tmp = permutation[i];
                	permutation[i] = permutation[mx_j];
                	permutation[mx_j] = tmp;
          	}
    		step1 = i * n;
    		for (j = 0; j < i; j++)
    		{
    			x[step1 + j] /= mx;
    		}
          	for (j = i; j < n; j++) 
          	{
                	a[step1 + j] /= mx;
                	x[step1 + j] /= mx;
          	}
          	for (k = i + 1; k < n; k++) 
          	{
          		step1 = k * n;
          		step2 = i * n;
                	el = a[step1 + i];
                	for (j = 0; j < i; j++)
                	{
                		x[step1 + j] -= el * x[step2 + j];
                	}
                	for (j = i; j < n; j++) 
                	{
                    		a[step1 + j] -= el * a[step2 + j];
                    		x[step1 + j] -= el * x[step2 + j];
                	}
          	}
	}
    // Обратный ход метода Гаусса (обнуляю элементы над диагональю)
    for (k = n - 1; k >= 0; k--) 
	{
		step2 = k * n;
		for (i = k - 1; i >= 0; i--) 
          	{
          		step1 = i * n;
                	el = a[step1 + k];
                	for (j = 0; j < n; j++) 
                	{
                   		x[step1 + j] -= el * x[step2 + j];
                	}
          	}
      	}
        // Восствновливаю правильного порядка строк обратной матрицы
     	k = -1;
      	for (i = 0; i < n; i++)
        {
        	while (i != k)
                {
              		k = permutation[i];
              		step1 = k * n;
              		step2 = i * n;
              		for (j = 0; j < n; j++)
                  	{
                  		el = x[step1 + j];
                  		x[step1 + j] = x[step2 + j];
                  		x[step2 + j] = el;
                  	}
              		permutation[i] = permutation[k];
              		permutation[k] = k;
              	}
        }
      	return 1; // Ура! Нашли обратную матрицу
}


