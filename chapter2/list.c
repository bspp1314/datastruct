#include<stdio.h>
#include<malloc.h>
#include"list.h"
struct Node
{
    int Element;
    Position Next;
};
List MakeEmpty(List L)
{
  L = (List)malloc(sizeof(struct Node));
  if(L == NULL){
    printf("out of space\n.");
    return NULL;
  }
  L->Next = NULL;
  return  L;
}
int IsEmpty(List L)
{
  return L->Next == NULL;
}
int IsLast(Position P,List L)
{
  return P->Next == NULL;
}
Position Find(ElementType X,List L)
{
  Position P;
  P = L->Next;
  while(P != NULL && P->Element != X)
    P = P->Next;
  return P;
}
//查找元素的前驱
Position FindPrevious(ElementType X,List L)
{
  Position P;
  P = L;
  while(P->Next != NULL && P->Next->Element != X)
    P = P->Next;
  return P;
}
void Delete( ElementType X,List L )
{
  Position P ,TmpCell;
  P = FindPrevious(X,L);
  if(!IsLast(P,L))
  {
    TmpCell = P->Next;
    P->Next = TmpCell->Next;
    free(TmpCell);
  }
}
int Add(ElementType X , List L)
{
  Position P,TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if(TmpCell == NULL)
  {
    printf("out of space \n.");
    return -1;
  }
  TmpCell->Element = X;

  if( L == NULL )
  {
    printf("List is null.\n");
    return -1;
  }
  
  P = L;
  while(1)
  {
    if(P->Next == NULL)
    {
      P->Next = TmpCell;
      break;
    }
  }

  return 0;
}
void Insert(ElementType X,List L,Position P)
{
  Position TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if(TmpCell == NULL)
  {
    printf("Out of space \n.");
    return;
  }
  TmpCell->Element = X;
  TmpCell->Next = P->Next;
  P->Next = TmpCell;
}
void DeleteList(List L)
{
  Position P,Tmp;
  P = L->Next;
  L->Next = NULL;
  while(P != NULL)
  {
    Tmp = P->Next;
    free(P);
    P = Tmp;
  }
}
Position Header( List L ){
  return L;
}
Position First(List L)
{
  return L->Next;
}
Position Advance(Position P)
{
  return P->Next;
}
ElementType Retrieve(Position P)
{
  return P->Element;
}
int main()
{ 
  List list = MakeEmpty(list);
  Add(23,list);
  printf("%d\n",list->Next->Element);
  MakeEmpty(list);
  free(list);
  return 1;
}


