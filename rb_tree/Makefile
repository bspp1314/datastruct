objects = rb_tree.c rb_tree_test.c

rbtree:$(objects)
	gcc -std=c99  -DRB_TREE_DEBUG $(objects) -o rbtree
.PHONY:clean
clean :
	rm -rf *.o
	rm -rf rbtree
