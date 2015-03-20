#ifndef POLY_H
#define POLY_H

typedef struct{
	float	coef;
	int		expn;
}Term;

typedef struct{
	Term	*elem;
	int		length;
}Poly;

typedef	enum{
	ERROR	= -1,
	OK		= 0,
	OVERFLOW = 1
}Status;

Status	createPoly(Poly &p,Term e[],int n);
Status	destroyPoly(Poly &p);
Status addPoly(Poly a, Poly b, Poly &c);
#endif