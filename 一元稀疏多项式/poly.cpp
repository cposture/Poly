#include "poly.h"
#include <malloc.h>
#include <stddef.h>

static double pow(double x, long n);
static Status insertTerm(Poly &a, Term b);
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

Status mulPoly(Poly a, Poly b, Poly &c)
{
	int i, j;
	Term tmp;
	if (a.elem == NULL || b.elem == NULL)
		return ERROR;

	c.elem = (Term*)malloc((a.length*b.length)*sizeof(Term));
	
	if (c.elem == NULL)
		return OVERFLOW;
	c.length = 0;

	for (i = 0; i < b.length; i++)
	{
		for (j = 0; j < a.length; j++)
		{
			tmp.coef = a.elem[j].coef * b.elem[i].coef;
			tmp.expn = a.elem[j].expn + b.elem[i].expn;
			insertTerm(c, tmp);
		}
	}
	/*
		realloc();
		ָ����=����������*��realloc��Ҫ�ı��ڴ��С��ָ�������µĴ�С����
		�µĴ�С�ɴ��С������Ҫע�⣬����µĴ�СС��ԭ�ڴ��С�����ܻᵼ�����ݶ�ʧ�����ã���*/
	if (c.length != a.length + b.length)
	{
		c.elem = (Term*)realloc(c.elem, c.length*sizeof(Term));
		if (c.elem == NULL)
			return OVERFLOW;
	}
	return OK;
}



static Status insertTerm(Poly &a, Term b)
{
	int i,j;
	if (a.elem == NULL)
		return ERROR;
	if (b.coef == 0)
		return OK;
	if (a.length == 0)
	{
		a.elem[a.length++] = b;
		return OK;
	}
		
	for (i = 0; i < a.length; i++)
	{
		if (a.elem[i].expn < b.expn )
		{
			if (i != a.length - 1 && a.elem[i + 1].expn>b.expn)
			{
				for (j = a.length-1; j >i ; j--)
				{
					a.elem[j + 1] = a.elem[j];
				}
				a.elem[i + 1] = b;
				a.length++;
				return OK;
			}
			if (i == a.length - 1)
			{
				a.elem[i + 1] = b;
				a.length++;
				return OK;
			}		
			
		}
		if (a.elem[i].expn == b.expn)
		{
			a.elem[i].coef += b.coef;
			if (a.elem[i].coef == 0)
			{
				for (j = i; j < a.length-1; j++)
				{
					a.elem[j] = a.elem[j + 1];
				}
				a.length--;
			}
			return OK;
		}
		if (a.elem[i].expn > b.expn)
		{
			for (j = a.length - 1; j >=i; j--)
			{
				a.elem[j + 1] = a.elem[j];
			}
			a.elem[i] = b;
			a.length++;
			return OK;
		}	
	}
	return OK;
}

Status evaluatePoly(Poly a, float x,float &r)
{
	int i;
	if (a.elem == NULL)
		return ERROR;
	for (i = 0,r =0.0; i < a.length; i++)
	{
		r += a.elem[i].coef*pow(x,a.elem[i].expn);
	}
	return OK;
}

static double pow(double x, long n)
{
	double result = 1;
	if (x == 0)
		return 0;
	if (n == 0)
		return 1;
	if (n > 0)
	{
		while (n--)
		{
			result *= x;
		}
	}
	else
	{
		n = -n;
		while (n--)
		{
			result /= x;
		}
	}
	return result;
}