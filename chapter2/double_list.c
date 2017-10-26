#include<stdio.h>
#include<malloc.h>
#include"double_list.h"
DOUBLE_LIST MakeEmptyList()
{
  DOUBLE_LIST L = (DOUBLE_LIST)malloc(sizeof(struct Node));
  if(L == NULL)
  {
    printf("out of space\n");
    return NULL;
  }
  L->Next = NULL;
  return L;
}
int IsEmpty(DOUBLE_LIST L)
{
  return L->Next == NULL;
}
int IsLast(Position P)
{
  return P->Next == NULL;
}
Position Find(ElementType X,DOUBLE_LIST L)
{
  Position P;
  P = L->Next;
  while(P != NULL && P->Element != X)
    P = P->Next;
  return P;
}
void Delete(ElementType X,DOUBLE_LIST L)
{ 
  Position P;
  P = Find(X,L);
  if (P == NULL)
    return ;
  if(P->Next == NULL)
  {
    P->Ptr  = NULL;
    free(P);
  }else
  {
    P->Ptr->Next = P->Next;
    P->Next->Ptr = P->Ptr;
    free(P);
  }   
}
//Insert Element After of P
int Insert(ElementType X,DOUBLE_LIST L,Position P)
{
  Position TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if(TmpCell == NULL)
  {
    printf("Out of space.\n");
    return -1;
  }
  TmpCell->Element = X;
  //P后继的前驱变成TmpCell;
  P->Next->Ptr = TmpCell;
  TmpCell->Next = P->Next;

  P->Next = TmpCell;
  TmpCell->Ptr = P;
}
void DeleteList(DOUBLE_LIST L)
{
  Position P,TmpCell;
  P = L->Next;
  while( P != NULL )
  {
    TmpCell = P->Next;
    free(P);
    P = TmpCell;
  }
}
int main()
{

}
