﻿#define _USE_MATH_DEFINES
#define N 25

#include <stdio.h>
#include <math.h>
#include <locale.h>
int choice_regime()
{
	int n;
	printf("Выберете режим\n");
	printf("1 - Одинократный расчет функции в точке\n");
	printf("2 - Серийный эксперимент\n");
	scanf_s("%d", &n);
	return n;
}

int choice_function()
{
	int n;
	printf("Выберете функцию\n");
	printf("1 - sin(x)\n");
	printf("2 - cos(x)\n");
	printf("3 - exp(x)\n");
	printf("4 - ch(x)\n");
	scanf_s("%d", &n);
	return n;
}

void my_sin(double x, float E, int k)
{
	int i;
	double sin_c = sin(x), func = x, delta = fabs(sin_c - func), term = x;
	for (i = 2; (i <= k) && (delta >= E); i++)
	{
		term = (-1) * term * x * x / ((2 * i - 1) * (2 * i - 2));
		func = func + term;
		delta = fabs(sin_c - func);	
	}
	printf("%-2.d   %.7lf   %.6lf\n", i - 1, func, delta);
}

void my_cos(double x, float E, int k)
{
	int i;
	double cos_c = cos(x), func = 1, delta = fabs(cos_c - func), term = 1;
	for (i = 2; (i <= k) && (delta >= E); i++)
	{
		term = (-1) * term * x * x / ((2 * i - 2) * (2 * i - 3));
		func = func + term;
		delta = fabs(cos_c - func);
	}
	printf("%-2.d   %.7lf   %.6lf\n", i - 1, func, delta);
}

void my_exp(double x, float E, int k)
{
	int i;
	double exp_c = exp(x), func = 1, delta = fabs(exp_c - func), term = 1;
	for (i = 2; (i <= k) && (delta >= E); i++)
	{
		term = term * x / (i - 1);
		func = func + term;
		delta = fabs(exp_c - func);
	}
	printf("%-2.d   %.7lf   %.6lf\n", i - 1, func, delta);
}

void my_ch(double x, float E, int k)
{
	int i;
	double ch_c = cosh(x), func = 1, delta = fabs(ch_c - func), term = 1;
	for (i = 2; (i <= k) && (delta >= E); i++)
	{
		term = term * x * x / ((2 * i - 2) * (2 * i - 3));
		func = func + term;
		delta = fabs(ch_c - func);
	}
	printf("%-2.d   %.7lf   %.6lf\n", i - 1, func, delta);
}

void output_one(void(*f)(double, float, int), double x, double func)
{
	float E;
	int k;
	printf("Введите точность вычисления (>= 0,000001)\n");
	scanf_s("%f", &E);
	printf("Введите количество слагаемых от 1 до 1000\n");
	scanf_s("%d", &k);
	printf("%lf\n", func);
	f(x, E, k);
}

void output_two(void(*f)(double, float, int), double x, double func)
{
	float E[N];
	int k[N], experience, i;
	printf("Введите количество экспериментов от 1 до 25?\n");
	scanf_s("%d", &experience);
	for (i = 0; i < experience; i++)
	{
		printf("Введите точность вычисления (>= 0,000001) для %d-ого эксперимента\n", i + 1);
		scanf_s("%f", &E[i]);
		printf("Введите количество слагаемых от 1 до 1000 для %d-ого эксперимента\n", i + 1);
		scanf_s("%d", &k[i]);
	}
	printf("%lf\n", func);
	for (i = 0; i < k[i]; i++)
		f(x, E[i], k[i]);
}

void main()
{
	setlocale(LC_ALL, "Rus");
	int n, regime;
	void(*f)(double, float, int) = NULL;
	double x, func;
	regime = choice_regime();
	n = choice_function();
	printf("Введите x\n");
	scanf_s("%lf", &x);
	switch (n)
	{
		case 1:
			f = my_sin;
			x = x / 180 * M_PI;
			func = sin(x);
			break;
		case 2:
			f = my_cos;
			x = x / 180 * M_PI;
			func = cos(x);
			break;
		case 3:
			f = my_exp;
			func = exp(x);
			break;
		case 4:
			f = my_ch;
			func = cosh(x);
			break;
	}
	if (regime == 1)
		output_one(f, x, func);
	else
		output_two(f, x, func);
	system("pause");
}