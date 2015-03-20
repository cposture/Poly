#include "poly.h"
#include <malloc.h>
#include <stddef.h>


Status	createPoly(Poly &p, Term e[], int n)
{
	int i;
	if (e == NULL || n == 0)
		return ERROR;
	//p.elem = e;
	p.elem = (Term *)malloc(n*sizeof(Term));
	if (p.elem == NULL)
		return OVERFLOW;
	for (i = 0; i < n; i++)
		p.elem[i] = e[i];
	p.length = n;
	return OK;
}

Status	destroyPoly(Poly &p)
{
	if (p.elem == NULL)
		return ERROR;
	free((void*)p.elem);
	p.elem = NULL;
	p.length = 0;
	return OK;
}

Status getPolyLength(Poly p,int &n)
{
	/*这里用p.elem == NULL判断多项式是否为空*/
	if (p.elem == NULL)	
		return ERROR;
	n = p.length;
	return OK;
}

Status addPoly(Poly a, Poly b, Poly &c)
{
	int i, j, k;
	float x;

	i = j = k = 0;
	
	if (a.elem == NULL || b.elem == NULL)
		return ERROR;

	c.elem = (Term*)malloc((a.length + b.length)*sizeof(Term));
	if (c.elem == NULL)
		return OVERFLOW;
	/*
		在两个多项式的最小长度范围里，依次比较指数大小，凡是小的，复制给c且将，赋值双方的位标指向下一位，
		若是相等，且指数相加结果不为0，则将指数相加结果复制给c。因为相等，所以a,b,c相应位标都加1，取下一项。
	*/
	while (i < a.length && j < b.length)
	{
		if (a.elem[i].expn < b.elem[j].expn)
			c.elem[k++] = a.elem[i++];
		else if (a.elem[i].expn > b.elem[j].expn)
			c.elem[k++] = b.elem[j++];
		else
		{
			x = a.elem[i].coef + b.elem[j].coef;
			if (x != 0)								/*这里的浮点数判0可能有点问题*/
			{
				c.elem[k].expn = b.elem[j].expn;
				c.elem[k].coef = x;
			}
			i++;
			j++;
			k++;
		}
	}
	/*
		将尚未处理完的a或b的剩余部分依次添加给c
	*/
	while (i < a.length)
	{
		c.elem[k++] = a.elem[i++];
	}
	while (j < b.length)
	{
		c.elem[k++] = b.elem[j++];
	}
	/*注意要将实际长度k赋值给c的length成员*/
	c.length = k;
	
	if (k == i + j)	
		return OK;
	/*实际长度小于原两个多项式长度之和，则重新分配c的elem数组的空间*/	
	if (NULL == (c.elem = (Term*)realloc(c.elem, k*sizeof(Term))))
		return OVERFLOW;
	return OK;
}

Status subPoly(Poly a, Poly b, Poly &c)
{
	int i, j, k;
	float x;

	i = j = k = 0;

	if (a.elem == NULL || b.elem == NULL)
		return ERROR;

	c.elem = (Term*)malloc((a.length + b.length)*sizeof(Term));
	if (c.elem == NULL)
		return OVERFLOW;
	/*
	在两个多项式的最小长度范围里，依次比较指数大小，凡是小的，复制给c且将，赋值双方的位标指向下一位，
	若是相等，且指数相加结果不为0，则将指数相加结果复制给c。因为相等，所以a,b,c相应位标都加1，取下一项。
	*/
	while (i < a.length && j < b.length)
	{
		if (a.elem[i].expn < b.elem[j].expn)
		{
			c.elem[k++] = a.elem[i++];
		}
		else if (a.elem[i].expn > b.elem[j].expn)
		{
			c.elem[k++].expn = b.elem[j++].expn;
			c.elem[k++].coef = -1 * b.elem[j++].coef;
		}	
		else
		{
			x = a.elem[i].coef - b.elem[j].coef;
			if (x != 0)								/*这里的浮点数判0可能有点问题*/
			{
				c.elem[k].expn = b.elem[j].expn;
				c.elem[k].coef = x;
				k++;								/*k++应该放在这*/
			}
			i++;
			j++;
			
		}
	}
	/*
	将尚未处理完的a或b的剩余部分依次添加给c
	*/
	while (i < a.length)
	{
		c.elem[k++] = a.elem[i++];
	}
	while (j < b.length)
	{
		c.elem[k++].expn = b.elem[j++].expn;
		c.elem[k++].coef = -1 * b.elem[j++].coef;
	}
	/*注意要将实际长度k赋值给c的length成员*/
	c.length = k;

	if (k == i + j)
		return OK;
	/*实际长度小于原两个多项式长度之和，则重新分配c的elem数组的空间*/
	if (NULL == (c.elem = (Term*)realloc(c.elem, k*sizeof(Term))))
		return OVERFLOW;
	return OK;
}

void polyTraverse(Poly a, void(*fun)(Term b))
{
	int i;
	for (i = 0; i < a.length; i++)
		fun(a.elem[i]);
}

