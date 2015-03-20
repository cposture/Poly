// һԪϡ�����ʽ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "poly.h"

void output(Term a);

int _tmain(int argc, _TCHAR* argv[])
{
	Poly p,q,r;
	Term e[] = { { 1.2, 1 }, { 2.5, 2 } };
	Term f[] = { { 1.0, 1 }, { 2.0, 2 } };
	if (OK != createPoly(p, e, 2))
		printf("��ʼ��ʧ��");
	if (OK != createPoly(q, f, 2))
		printf("��ʼ��ʧ��");
	createPoly(r, NULL, 0);
	subPoly(p, q, r);
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
