#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#define MaxDegree 10
struct ploynomial
{
  int CoffArray[MaxDegree + 1];
  int HighPower;
};/*多项式ADT的数组实现的类型声明*/
typedef struct ploynomial POLY_S;
void zero_poly(POLY_S *poly);
void add_poly(const POLY_S *poly1,const POLY_S *poly2,POLY_S *poly_sum);
#endif
