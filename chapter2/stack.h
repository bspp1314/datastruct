#ifndef _Stack_h
#define _Stack_h
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;
int is_empty(Stack S);
Stack create_stack(void);
void make_empty(Stack S);
void pop(Stack S);
void push(void *Element,Stack S);
void top(void *Element,Stack S);
#endif
struct Node
{
  void *Element;
  PtrToNode Next;
};
