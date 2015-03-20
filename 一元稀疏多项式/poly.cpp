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
	/*������p.elem == NULL�ж϶���ʽ�Ƿ�Ϊ��*/
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
		����������ʽ����С���ȷ�Χ����αȽ�ָ����С������С�ģ����Ƹ�c�ҽ�����ֵ˫����λ��ָ����һλ��
		������ȣ���ָ����ӽ����Ϊ0����ָ����ӽ�����Ƹ�c����Ϊ��ȣ�����a,b,c��Ӧλ�궼��1��ȡ��һ�
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
			if (x != 0)								/*����ĸ�������0�����е�����*/
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
		����δ�������a��b��ʣ�ಿ��������Ӹ�c
	*/
	while (i < a.length)
	{
		c.elem[k++] = a.elem[i++];
	}
	while (j < b.length)
	{
		c.elem[k++] = b.elem[j++];
	}
	/*ע��Ҫ��ʵ�ʳ���k��ֵ��c��length��Ա*/
	c.length = k;
	
	if (k == i + j)	
		return OK;
	/*ʵ�ʳ���С��ԭ��������ʽ����֮�ͣ������·���c��elem����Ŀռ�*/	
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
	����������ʽ����С���ȷ�Χ����αȽ�ָ����С������С�ģ����Ƹ�c�ҽ�����ֵ˫����λ��ָ����һλ��
	������ȣ���ָ����ӽ����Ϊ0����ָ����ӽ�����Ƹ�c����Ϊ��ȣ�����a,b,c��Ӧλ�궼��1��ȡ��һ�
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
			if (x != 0)								/*����ĸ�������0�����е�����*/
			{
				c.elem[k].expn = b.elem[j].expn;
				c.elem[k].coef = x;
				k++;								/*k++Ӧ�÷�����*/
			}
			i++;
			j++;
			
		}
	}
	/*
	����δ�������a��b��ʣ�ಿ��������Ӹ�c
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
	/*ע��Ҫ��ʵ�ʳ���k��ֵ��c��length��Ա*/
	c.length = k;

	if (k == i + j)
		return OK;
	/*ʵ�ʳ���С��ԭ��������ʽ����֮�ͣ������·���c��elem����Ŀռ�*/
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

