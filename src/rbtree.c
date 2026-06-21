#include <stdio.h>
#include <stdlib.h>

#include "../include/rbtree.h"

RBTree *rbtree_create(void)
{
    RBTree *tree = (RBTree *)malloc(sizeof(RBTree));

    if (tree == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    tree->nil = (RBNode *)malloc(sizeof(RBNode));

    if (tree->nil == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    tree->nil->color = BLACK;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->parent = tree->nil;

    tree->node_count = 0;
    tree->root = tree->nil;

    return tree;
}


RBNode *rbtree_create_node(RBTree *tree, int key)
{
    RBNode *node = (RBNode *)malloc(sizeof(RBNode));

    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->color = RED;

    node->left = tree->nil;
    node->right = tree->nil;
    node->parent = tree->nil;

    return node;
}


void rbtree_left_rotate(RBTree *tree, RBNode *x)
{
    RBNode *y = x->right;

    x->right = y->left;

    if (y->left != tree->nil)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == tree->nil)
    {
        tree->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rbtree_right_rotate(RBTree *tree, RBNode *y)
{
    RBNode *x = y->left;

    y->left = x->right;

    if (x->right != tree->nil)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == tree->nil)
    {
        tree->root = x;
    }
    else if (y == y->parent->right)
    {
        y->parent->right = x;
    }
    else
    {
        y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}


RBNode *rbtree_search(RBTree *tree, int key)
{
    RBNode *current = tree->root;

    while (current != tree->nil)
    {
        if (key == current->key)
        {
            return current;
        }

        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return tree->nil;
}


RBNode *rbtree_minimum(RBTree *tree, RBNode *node)
{
    while (node->left != tree->nil)
    {
        node = node->left;
    }

    return node;
}

void rbtree_transplant(
    RBTree *tree,
    RBNode *u,
    RBNode *v)
{
    if (u->parent == tree->nil)
    {
        tree->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    v->parent = u->parent;
}


void rbtree_insert(RBTree *tree, int key)
{
    RBNode *y = tree->nil;
    RBNode *x = tree->root;

    while (x != tree->nil)
    {
        y = x;

        /* Ignora duplicatas */
        if (key == x->key)
        {
            return;
        }

        if (key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    /* Só aloca memória se realmente precisar inserir */
    RBNode *z = rbtree_create_node(
        tree,
        key);

    z->parent = y;

    if (y == tree->nil)
    {
        tree->root = z;
    }
    else if (key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;

    tree->node_count++;

    rbtree_insert_fixup(
        tree,
        z);
}

void rbtree_insert_fixup(RBTree *tree, RBNode *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode *y = z->parent->parent->right;

            /* Caso 1:
               Tio vermelho */
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else
            {
                /* Caso 2:
                   Triângulo */
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rbtree_left_rotate(tree, z);
                }

                /* Caso 3:
                   Linha */
                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                rbtree_right_rotate(
                    tree,
                    z->parent->parent);
            }
        }
        else
        {
            RBNode *y = z->parent->parent->left;

            /* Caso espelhado 1 */
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else
            {
                /* Caso espelhado 2 */
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rbtree_right_rotate(tree, z);
                }

                /* Caso espelhado 3 */
                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                rbtree_left_rotate(
                    tree,
                    z->parent->parent);
            }
        }
    }

    tree->root->color = BLACK;
}

void rbtree_delete(RBTree *tree, int key)
{
    RBNode *node = rbtree_search(tree, key);

    if (node == tree->nil)
    {
        return;
    }

    rbtree_delete_node(tree, node);
}

void rbtree_delete_node(RBTree *tree, RBNode *z)
{
    RBNode *y = z;
    RBNode *x;

    Color original_color = y->color;

    if (z->left == tree->nil)
    {
        x = z->right;

        rbtree_transplant(
            tree,
            z,
            z->right);
    }
    else if (z->right == tree->nil)
    {
        x = z->left;

        rbtree_transplant(
            tree,
            z,
            z->left);
    }
    else
    {
        y = rbtree_minimum(
            tree,
            z->right);

        original_color = y->color;

        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbtree_transplant(
                tree,
                y,
                y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        rbtree_transplant(
            tree,
            z,
            y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    tree->node_count--;

    free(z);

    if (original_color == BLACK)
    {
        rbtree_delete_fixup(tree, x);
    }
}


void rbtree_delete_fixup(RBTree *tree, RBNode *x)
{
    while (x != tree->root &&
           x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            RBNode *w = x->parent->right;

            /* Caso 1 */
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(
                    tree,
                    x->parent);

                w = x->parent->right;
            }

            /* Caso 2 */
            if (w->left->color == BLACK &&
                w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                /* Caso 3 */
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;

                    rbtree_right_rotate(
                        tree,
                        w);

                    w = x->parent->right;
                }

                /* Caso 4 */
                w->color = x->parent->color;

                x->parent->color = BLACK;
                w->right->color = BLACK;

                rbtree_left_rotate(
                    tree,
                    x->parent);

                x = tree->root;
            }
        }
        else
        {
            RBNode *w = x->parent->left;

            /* Caso espelhado 1 */
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_right_rotate(
                    tree,
                    x->parent);

                w = x->parent->left;
            }

            /* Caso espelhado 2 */
            if (w->right->color == BLACK &&
                w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                /* Caso espelhado 3 */
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;

                    rbtree_left_rotate(
                        tree,
                        w);

                    w = x->parent->left;
                }

                /* Caso espelhado 4 */
                w->color = x->parent->color;

                x->parent->color = BLACK;
                w->left->color = BLACK;

                rbtree_right_rotate(
                    tree,
                    x->parent);

                x = tree->root;
            }
        }
    }

    x->color = BLACK;
}


void rbtree_inorder(
    RBTree *tree,
    RBNode *node)
{
    if (node == tree->nil)
    {
        return;
    }

    rbtree_inorder(tree, node->left);

    printf("%d(%s) ",
           node->key,
           node->color == RED ? "R" : "B");

    rbtree_inorder(tree, node->right);
}

void rbtree_print(RBTree *tree)
{
    rbtree_inorder(
        tree,
        tree->root);

    printf("\n");
}

void rbtree_destroy_node(
    RBTree *tree,
    RBNode *node)
{
    if (node == tree->nil)
    {
        return;
    }

    rbtree_destroy_node(
        tree,
        node->left);

    rbtree_destroy_node(
        tree,
        node->right);

    free(node);
}

void rbtree_destroy(RBTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    rbtree_destroy_node(
        tree,
        tree->root);

    free(tree->nil);
    free(tree);
}