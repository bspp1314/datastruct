#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"stack.h"

int is_empty(Stack S)
{
  return S->Next == NULL;
}

Stack create_stack( void )
{
  Stack S;
  S = malloc(sizeof(struct Node));
  if(S == NULL)
  {
    printf("Out of space.\n");
    return NULL;
  }
  S->Next == NULL;
  return S;
}

void make_empty(Stack S)
{
  if(S == NULL)
  {
    printf("Must use create stack first");
    return;
  }
  while(is_empty(S))
    pop(S);
}

//入栈操作
void push(void *Element,Stack S)
{
  PtrToNode TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if(TmpCell == NULL)
  {
    printf("out of space.\n");
    return;
  }
  //向表头和第一元素之间插入一个元素
  TmpCell->Element = Element;
  TmpCell->Next = S->Next;
  S->Next = TmpCell;
}

//出栈操作
void pop(Stack S)
{
  PtrToNode FirstCell;
  if(is_empty(S))
  {
    printf("Empty stack.\n");
  }else
  {
    FirstCell = S->Next;
    S->Next = S->Next->Next;
    free(FirstCell);
    FirstCell = NULL;
  }
}
//获取栈顶元素
void top(void *Element,Stack S)
{
  PtrToNode FirstCell;
  if(is_empty(S))
  {
    printf("Empty stack.\n");
  }else
  {
    Element = S->Next->Element;
  }
}

void free_stack(Stack S)
{
 make_empty(S);
 free(S);
}

void  test()
{
  double data_array[10];
  int i = 0;

  Stack s = create_stack();
  for(;i<10;i++)
  {
    data_array[i] = i * 2;
    push(&data_array[i],s);
  }

  PtrToNode  p = s->Next;
  while(p != NULL)
  {
    double *x = (double *)p->Element;
    printf("%f\n",*x);
    p = p->Next;
  }

  free_stack(s);
}
int main()
{
  test();
  return -1;
}
