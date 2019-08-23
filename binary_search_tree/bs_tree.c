#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include"bs_tree.h"

static void remove_node(c_bs_tree_t *bs_tree,c_bs_node_t *node);
static c_bs_node_t* create_bs_node(void *key, void *value);
static c_bs_node_t *search(c_bs_tree_t *bs_tree,const void *key);
static void free_nodes(c_bs_node_t *node,int key_free ,int value_free);

c_bs_tree_t *c_bs_tree_create(int(*compare)(const void *,const void *),void (* print_key_func)(const void *))
{
    c_bs_tree_t *bs_tree = NULL;

    if (compare == NULL) {
        printf("compare function is null\n");
        NULL;    
    }

    bs_tree = (c_bs_tree_t*)malloc(sizeof(c_bs_tree_t));
    if (bs_tree == NULL) {
        printf("malloc bs_tree failed \n");
        return NULL;
    }

    bs_tree->root = NULL;
    bs_tree->size = 0;
    bs_tree->compare = compare;
    bs_tree->print_key_func = print_key_func;
}

// sucess return 0 
// fail   return  !0 
static c_bs_node_t* create_bs_node(void *key, void *value)
{
    c_bs_node_t *new = (c_bs_node_t *)malloc(sizeof(c_bs_node_t));
    if (new == NULL){
        printf("malloc c_bs_node_t failed \n");
        return NULL;
    }

    new->left = NULL;
    new->right = NULL;
    new->key = key;
    new->value = value;
    new->parent = NULL;
    return new; 
}

static c_bs_node_t *search(c_bs_tree_t *bs_tree,const void *key)
{
    assert(bs_tree != NULL);
    if (key == NULL) {
        return NULL;
    }

    int comp = 0;
    c_bs_node_t *node = bs_tree->root;
    while(node != NULL){
        comp = bs_tree->compare(node->key,key);
        if (comp == 0) {
            return node;
        }else if (comp == -1) {
            node = node->right;
        }else{
            node = node->left;
        }
    }
    return NULL;
}

static void free_nodes(c_bs_node_t *node,int key_free ,int value_free)
{
    if (node == NULL){
        return;
    }
    if(node->left != NULL){
        free_nodes(node->left,key_free,value_free);
    }

    if(node->right != NULL){
        free_nodes(node->right,key_free,value_free);
    }

    if (key_free){
        free(node->key);
        node->key = NULL;
    }
    
    if(value_free){
        free(node->value);
        node->value = NULL;
    }

    free(node);
    node = NULL;
}

void  c_bs_tree_get(c_bs_tree_t *bs_tree,const void *key,void **rvalue)
{
    assert(bs_tree != NULL);
    
    if (rvalue == NULL) {
        return;
    }

    c_bs_node_t *node = search(bs_tree,key);
    if(node == NULL){
        return;
    }

    *rvalue = node->value;
}

void  c_bs_tree_remove(c_bs_tree_t *bs_tree,const void *key,void **rkey,void **rvalue)
{
    assert(bs_tree != NULL);

    c_bs_node_t *node = NULL;
    if (rkey == NULL && rvalue == NULL){
        return;
    }

    node = search(bs_tree,key);
    if(node == NULL){
        return;
    }

    //调整
    remove_node(bs_tree,node);

    if(rkey != NULL){
        *rkey = node->key;
    }
    if(rvalue != NULL){
        *rvalue = node->value;
    }
    bs_tree->size--;
}

//节点最大值
c_bs_node_t *max_node(c_bs_node_t *node)
{
    if(node == NULL){
        return NULL;
    }
    while(node->right != NULL){
        node = node->right;
    }
    return node;
}

//节点node右子树的最小值
c_bs_node_t *min_node(c_bs_node_t *node)
{
    if(node == NULL){
        return NULL;
    }
    while(node->left != NULL){
        node = node->left;
    }
    return node;
}

static void remove_node(c_bs_tree_t *bs_tree,c_bs_node_t *node)
{
    assert(bs_tree != NULL);
    assert(node != NULL);

    c_bs_node_t *left = node->left;
    c_bs_node_t *right = node->right;
    c_bs_node_t *parent = node->parent;
    c_bs_node_t *replace = NULL;

    if (right == NULL){
        replace = node->left;
    }else if (left == NULL){
        replace = node->right;
    }else{
        //右子树的最小值
        c_bs_node_t *min = min_node(node->right);
        bs_tree->print_key_func(min->key);
        //重设right_min parent的左子树为right_min的右子树
        min->parent->left = min->right;

        min->parent = node->parent;
        min->left = node->left;
        min->right = node->right;
        replace = min;
    }

    if (parent == NULL){
        bs_tree->root = replace;
    }else if(parent->left == node){
        parent->left = replace;
    }else{
        parent->right = replace;
    }
}



int c_bs_tree_insert(c_bs_tree_t *bs_tree,void *key,void *value)
{
    assert(bs_tree != NULL);
    assert(bs_tree->compare != NULL);
    assert(key != NULL); 
    c_bs_node_t *new = NULL;
    c_bs_node_t *index = bs_tree->root;

    if (bs_tree->root == NULL){
        new = create_bs_node(key,value);
        if (new == NULL){
            return 1;
        }
        bs_tree->root = new;
    }else{
        while(1){
            int comp = bs_tree->compare(index->key,key);
            if (comp == 0 ){
                index->value = value;
                return 0;
            }else {
                if (comp < 0 ){//left < right 
                    if(index->right == NULL){
                        new = create_bs_node(key,value);
                        if (new == NULL){
                            return 1;
                        }
                        index->right = new;
                        new->parent = index;
                        break;
                    }else{
                        index = index->right;
                    }
                }else{
                    if(index->left == NULL){
                        new = create_bs_node(key,value);
                        if (new == NULL){
                            return 1;
                        }

                        index->left = new;
                        new->parent = index;
                        break;
                    }else{
                        index = index->left;
                    }
                }
            }
        }
    }
    bs_tree->size++;
    return 0;
}

//key_free 是否释放key
//value_free 是否释放value
void c_bs_tree_destroy(c_bs_tree_t *bs_tree,int key_free ,int value_free){
    if (bs_tree == NULL){
        return;
    }

    free_nodes(bs_tree->root,key_free,value_free);
    free(bs_tree);
    bs_tree = NULL;
}

static preorder(c_bs_node_t *node,void(*print_key_func)(const void *))
{
    if (node != NULL && print_key_func != NULL){
        print_key_func(node->key);
        preorder(node->left,print_key_func);
        preorder(node->right,print_key_func);
    }
}

//前序遍历
void c_bs_tree_preorder(c_bs_tree_t *tree)
{
    assert(tree != NULL);
    preorder(tree->root,tree->print_key_func);
    printf("\n");
}

static inorder(c_bs_node_t *node,void(*print_key_func)(const void *)){
    if (node != NULL && print_key_func != NULL){
        inorder(node->left,print_key_func);
        print_key_func(node->key);
        inorder(node->right,print_key_func);
    }
}

//中序遍历
void c_bs_tree_inorder(c_bs_tree_t *tree){
    assert(tree != NULL);
    inorder(tree->root,tree->print_key_func);
    printf("\n");
}

static postorder(c_bs_node_t *node,void(*print_key_func)(const void *)){
    if (node != NULL && print_key_func != NULL){
        postorder(node->left,print_key_func);
        postorder(node->right,print_key_func);
        print_key_func(node->key);
    }
}

void c_bs_tree_postorder(c_bs_tree_t *tree){
    assert(tree != NULL);
    postorder(tree->root,tree->print_key_func);
    printf("\n");
}








