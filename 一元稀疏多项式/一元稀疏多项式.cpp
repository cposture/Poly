// 一元稀疏多项式.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "poly.h"
#include "malloc.h"

void output(Term a);

int _tmain(int argc, _TCHAR* argv[])
{
	Poly p,q,r;
	int i;
	float result;
	Term e[] = { { 1.2, 1 }, { 2.5, 2 } };
	Term f[] = { { 1.0, 2 }, { 2.0, 3 } };
	if (OK != createPoly(p, e, 2))
		printf("初始化失败");
	if (OK != createPoly(q, f, 2))
		printf("初始化失败");
	evaluatePoly(p, 2.0, result);
	addPoly(p, q, r);
	if (r.length == 0)
		printf("0");
	else
		polyTraverse(r, output);

	return 0;
}

void output(Term a)
{
	char signal;
	if (a.coef > 0)
		signal = '+';
	else
		signal = '-';
	printf("%c%3.2fx^%d", signal, a.coef, a.expn);
}
