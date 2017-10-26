#ifndef _LIST_H
#define _LIST_H
struct Node;
typedef struct Node *List;
typedef struct Node *Position;
typedef int ElementType;

List MakeEmpty( List L );
Position Find(ElementType X,List L);
Position FindPrevious(ElementType X,List L);
void Delete( ElementType X,List L  );
void Insert(ElementType X,List L,Position P);
void DeleteList(List L);
#endif
