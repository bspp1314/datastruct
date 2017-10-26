#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"queue.h"

int is_empty(Queue Q)
{
  return Q->Next == NULL;
}

Queue create_queue( void )
{
  Queue Q = malloc(sizeof(struct Node));
  if(Q == NULL)
  {
    printf("out of space.\n");
    return NULL;
  }
  Q->Next == NULL;
  return Q;
}
void make_empty(Queue Q)
{
  if(Q == NULL)
  {
    printf("Must use create queue first");
    return;
  }
  while(is_empty(Q))
    dequeue(Q);
}

void enqueue(void *data,Queue Q)
{
  PtrToNode TmpCell;
  TmpCell = malloc(sizeof(struct Node));
  if(TmpCell == NULL)
  {
    printf("out of space.\n");
    return ;
  }

  PtrToNode q = Q;
  while(1)
  {
    if(q->Next == NULL)
    {
      TmpCell->data = data;
      q->Next = TmpCell;
      break;
    }else
    {
      q = q->Next;
    }
  }
}
void dequeue(Queue Q)
{
  PtrToNode FirstCell;
  if(is_empty(Q))
  {
    printf("Empty queue.\n");
    return;
  }

  FirstCell = Q->Next;
  Q->Next  = Q->Next->Next;
  free(FirstCell);
  FirstCell = NULL;
}
void free_queue(Queue Q)
{
  make_empty(Q);
  free(Q);
}
void test()
{
  double data_array[10];
  int i = 0;
  Queue q = create_queue();

  for(;i<10;i++)
  {
    data_array[i] = i * 2;
    enqueue(&data_array[i],q);
  }

  PtrToNode p = q->Next;
  while(p != NULL)
  {
    double *x = (double *)p->data;
    printf("%f\n",*x);
    p = p->Next;
  }
  free_queue(q);
}

int main()
{
  test();
  return 0;
}
