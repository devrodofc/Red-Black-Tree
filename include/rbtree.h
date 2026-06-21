#ifndef RBTREE_H
#define RBTREE_H

#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct RBNode
{
    int key;
    Color color;

    struct RBNode *parent;
    struct RBNode *left;
    struct RBNode *right;

} RBNode;

typedef struct
{
    RBNode *root;
    RBNode *nil;

    size_t node_count;

} RBTree;

RBTree *rbtree_create(void);
RBNode *rbtree_create_node(RBTree *tree, int key);

void rbtree_insert(RBTree *tree, int key);
void rbtree_insert_fixup(RBTree *tree, RBNode *node);

RBNode *rbtree_search(RBTree *tree, int key);

void rbtree_delete(RBTree *tree, int key);
void rbtree_delete_node(RBTree *tree, RBNode *node);
void rbtree_delete_fixup(RBTree *tree, RBNode *node);

void rbtree_left_rotate(RBTree *tree, RBNode *node);
void rbtree_right_rotate(RBTree *tree, RBNode *node);

RBNode *rbtree_minimum(RBTree *tree, RBNode *node);

void rbtree_transplant(
    RBTree *tree,
    RBNode *u,
    RBNode *v);

void rbtree_inorder(
    RBTree *tree,
    RBNode *node);

void rbtree_print(
    RBTree *tree);

void rbtree_destroy_node(
    RBTree *tree,
    RBNode *node);

void rbtree_destroy(
    RBTree *tree);

#endif