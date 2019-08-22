#include<stdio.h>
#include<malloc.h>
#include"polyomial.h"
//数组的下标0对应多项式式最低项0
void zero_poly(POLY_S *poly)
{ 
  int i;
  for(i = 0;i <= MaxDegree;i++)
  {
    poly->CoffArray[i] == 0;
  }
  poly->HighPower = 0;
}
void add_poly(const POLY_S *poly1,const POLY_S *poly2,POLY_S *poly_sum)
{
  zero_poly(poly_sum);
  poly_sum->HighPower = poly1->HighPower > poly2->HighPower ? poly1->HighPower : poly2->HighPower;
  int i;
  for(i = poly_sum->HighPower;i >= 0;i--)
    poly_sum->CoffArray[i] = poly1->CoffArray[i] + poly2->CoffArray[i];
}
void mul_poly(const POLY_S *poly1,const POLY_S *poly2,POLY_S *poly_mul)
{
  zero_poly(poly_mul);
  if((poly_mul->HighPower = poly1->HighPower * poly2->HighPower) > MaxDegree)
  {
    printf("out of Maxdegree.\n");
    return;
  }
}
int add_value_poly(int coeff,int term,POLY_S *poly)
{
  if(term > MaxDegree)
  {
    printf("out of Maxdegree.\n");
    return -1;
  }
  poly->HighPower = term > poly->HighPower ? term : poly->HighPower;
  poly->CoffArray[term] = poly->CoffArray[term]+coeff;
  return 0;
}
void free_poly(POLY_S *poly)
{
  if(poly != NULL)
  {
    free(poly);
    poly = NULL;
  }
}
int main(){
  POLY_S poly1 = {};
  POLY_S poly2 = {};
  POLY_S poly_sum = {};


  zero_poly(&poly1);
  zero_poly(&poly2);

  //3x2+4x+1
  add_value_poly(3,2,&poly1);
  add_value_poly(4,1,&poly1);

  //5x5+3x2
  add_value_poly(5,5,&poly2);
  add_value_poly(3,2,&poly2);

  add_poly(&poly1,&poly2,&poly_sum);
  int i;
  for(i = poly_sum.HighPower;i >= 0;i--)
    printf("%d ",poly_sum.CoffArray[i]);
  printf("\n.");

  return 0;
}

