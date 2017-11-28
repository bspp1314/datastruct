#ifndef DOUBLE_LIST_H
#define DOUBLE_LIST_H
struct Node;
typedef struct Node *DOUBLE_LIST;
typedef struct Node *Position;
typedef int ElementType;
#endif
struct Node{
  ElementType Element;
  Position Next;//后继
  Position Ptr;//前驱
};
