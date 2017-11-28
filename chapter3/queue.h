#ifndef _QUEUE_H
#define _QUEUE_H
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Queue;
int is_empty(Queue Q);
Queue create_queue(void);
void make_empty(Queue Q);
void enqueue(void *data,Queue Q);/*入队操作*/
void dequeue(Queue Q);/*出队操作*/
#endif
struct Node
{
  void *data;
  PtrToNode Next;
  
};
