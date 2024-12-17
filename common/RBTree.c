/*
** RBTree.c
** Chris Fletcher
**
** This is free and unencumbered software released into the public domain.
**
** Anyone is free to copy, modify, publish, use, compile, sell, or
** distribute this software, either in source code form or as a compiled
** binary, for any purpose, commercial or non-commercial, and by any
** means.
**
** In jurisdictions that recognize copyright laws, the author or authors
** of this software dedicate any and all copyright interest in the
** software to the public domain. We make this dedication for the benefit
** of the public at large and to the detriment of our heirs and
** successors. We intend this dedication to be an overt act of
** relinquishment in perpetuity of all present and future rights to this
** software under copyright law.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
** OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
** ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
** OTHER DEALINGS IN THE SOFTWARE.
**
** For more information, please refer to <https://unlicense.org>
*/

#include "RBTree.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static RBTNode NilNodeObject = { NULL, BLACK, NULL, { NULL, NULL } };
static RBTNode* const NilNode = &NilNodeObject;
static RBTNode* const SentinelLeaf = &NilNodeObject;

#define left children[LEFT]
#define right children[RIGHT]
#define OppositeDirection(dir) (RIGHT - dir + LEFT)

/*****************************************************************************/
/* Internal helper functions                                                 */
/*****************************************************************************/

/*
** Returns true if the given node is the sentinel.
*/
static bool IsSentinel(const RBTNode* node)
{
    assert(node != NULL);
    return (node == SentinelLeaf);
}

/*
** Returns the child direction (if node is a left or right child)
*/
static RBTDirection GetChildDirection(const RBTNode* node)
{
    assert((node != NULL) && (!IsSentinel(node->parent)));

    if (node->parent->left == node) {
        return LEFT;
    }
    else {
        return RIGHT;
    }
}

/*
** Return a node's sibling.
*/
static RBTNode* GetSibling(const RBTNode* node)
{
    const RBTDirection nodeDir = GetChildDirection(node);
    const RBTDirection sibDir = OppositeDirection(nodeDir);

    return node->parent->children[sibDir];
}

/*
** Return a node's uncle.
*/
static RBTNode* GetUncle(const RBTNode* node)
{
    assert(node != NULL);
    return GetSibling(node->parent);
}

/*
** Rotate left or right about the given node.
**
** Comments assume left rotation.
*/
static void Rotate(RBTree* tree, RBTNode* node, const RBTDirection dir)
{
    const RBTDirection oppDir = OppositeDirection(dir);
    RBTNode* oldRoot = node;
    RBTNode* newRoot = NULL;

    assert((oldRoot != NULL) && (!IsSentinel(oldRoot)));

    /* oldRoot's right child becomes the new subtree root */
    newRoot = oldRoot->children[oppDir];

    /* Sentinel can't become the new subtree root */
    assert(!IsSentinel(newRoot));

    /* oldRoot's parent becomes newRoot's parent */
    newRoot->parent = oldRoot->parent;

    if (tree->root == oldRoot) {
        /* if oldRoot was the tree root, make newRoot the tree root */
        tree->root = newRoot;
    }
    else {
        /* else replace oldRoot as its parent's child */
        const RBTDirection rootDir = GetChildDirection(oldRoot);
        newRoot->parent->children[rootDir] = newRoot;
    }

    /* newRoot's left child (oldRoot's successor branch) becomes oldRoot's right child */
    oldRoot->children[oppDir] = newRoot->children[dir];
    if (!IsSentinel(oldRoot->children[oppDir])) oldRoot->children[oppDir]->parent = oldRoot;

    /* and oldRoot is now newRoot's left child */
    newRoot->children[dir] = oldRoot;

    /* oldRoot's new parent is newRoot */
    oldRoot->parent = newRoot;
}

/*****************************************************************************/
/* Constructors and Destructors                                              */
/*****************************************************************************/

/*
** Create a new node.
*/
static bool CreateNode(RBTNode** node, const RBTree* tree, const void* key, RBTNodeColor color, RBTNode* parent)
{
    RBTNode* newNode = (RBTNode*)malloc(sizeof(RBTNode));

    assert(node != NULL);

    if (newNode == NULL) return false;

    newNode->key = tree->keyFuncs.Copy(key);
    newNode->color = color;
    newNode->parent = parent;
    newNode->left = SentinelLeaf;
    newNode->right = SentinelLeaf;

    *node = newNode;
    return true;
}

/*
** Destroy a node and it's key
*/
static void DestroyNode(RBTree* tree, RBTNode** node)
{
    assert(tree != NULL);
    assert((node != NULL) && (*node != NULL) && (!IsSentinel(*node)));

    tree->keyFuncs.Destroy((*node)->key);

    free(*node);
    *node = NULL;
}

/*
** Destroy a subtree
*/
static void DestroySubtree(RBTree* tree, RBTNode* node)
{
    assert((tree != NULL) && (node != NULL));

    if (IsSentinel(node)) return;

    DestroySubtree(tree, node->left);
    DestroySubtree(tree, node->right);
    DestroyNode(tree, &node);
}

bool RBTCreate(RBTree** tree, RBTKeyFunctions keyFuncs)
{
    RBTree* newTree = (RBTree*)malloc(sizeof(RBTree));

    assert(tree != NULL);

    if (newTree == NULL) return false;
    newTree->root = SentinelLeaf;
    newTree->keyFuncs = keyFuncs;

    *tree = newTree;
    return true;
}

void RBTDestroy(RBTree** tree)
{
    if ((tree != NULL) && (*tree != NULL)) {

        DestroySubtree(*tree, (*tree)->root);   

        free(*tree);
        *tree = NULL;
    }
}

/*****************************************************************************/
/* Search and iterate functions                                              */
/*****************************************************************************/

/*
** Returns node containing the minimum key in the subtree rooted at node.
*/
static RBTNode* FindMinimum(RBTNode* node)
{
    assert((node != NULL) && (!IsSentinel(node)));

    while (!IsSentinel(node->left)) {
        node = node->left;
    }

    return node;
}

/*
** Returns node containing the maximum key in the subtree rooted at node.
*/
static RBTNode* FindMaximum(RBTNode* node)
{
    assert((node != NULL) && (!IsSentinel(node)));

    while (!IsSentinel(node->right)) {
        node = node->right;
    }

    return node;
}

RBTNode* RBTMin(RBTree* tree)
{
    assert(tree != NULL);
    return FindMinimum(tree->root);
}

RBTNode* RBTMax(RBTree* tree)
{
    assert(tree != NULL);
    return FindMaximum(tree->root);
}

RBTNode* RBTSuccessor(RBTNode* node)
{
    assert((node != NULL) && (!IsSentinel(node)));

    if (!IsSentinel(node->right)) {
        /* If node has a right subtree, successor is the minimum value in that subtree */
        return FindMinimum(node->right);
    }
    else {
        /* Else move up the tree until we find a parent where node is a left child (i.e., parent key > child key) */
        RBTNode* parent = node->parent;

        while ((!IsSentinel(parent)) && (node == parent->right)) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }
}

RBTNode* RBTPredecessor(RBTNode* node)
{
    assert((node != NULL) && (!IsSentinel(node)));

    if (!IsSentinel(node->left)) {
        /* If node has a left subtree, predecessor is the maximum value in that subtree */
        return FindMaximum(node->left);
    }
    else {
        /* Else move up the tree until we find a parent where node is a right child (i.e., parent key < child key) */
        RBTNode* parent = node->parent;

        while ((!IsSentinel(parent)) && (node == parent->left)) {
            node = parent;
            parent = node->parent;
        }

        return parent;
    }
}

RBTNode* RBTSearch(RBTree* tree, const void* key)
{
    RBTNode* node = NilNode;

    assert(tree != NULL);
    node = tree->root;

    while ((!IsSentinel(node)) && (!tree->keyFuncs.Equal(key, node->key))) {
        if (tree->keyFuncs.Compare(key, node->key)) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return node;
}

bool RBTIsNil(const RBTNode* node)
{
    assert(node != NULL);
    return (node == NilNode);
}

/*****************************************************************************/
/* Node insertion functions                                                  */
/*****************************************************************************/

/*
** Rebalance tree after inserting node.
*/
static void InsertRebalance(RBTree* tree, RBTNode* node)
{
    assert((tree != NULL) && (node != NULL));

    while (node->parent->color == RED) {
        RBTNode* uncle = GetUncle(node);
        const RBTDirection parentDir = GetChildDirection(node->parent);

        if (uncle->color == RED) {
            /* Parent and uncle are both red */
            uncle->color = BLACK;
            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            node = node->parent->parent;
        }
        else {
            /* Else parent is red and uncle is black */
            const RBTDirection nodeDir = GetChildDirection(node);

            if (parentDir != nodeDir) {
                node = node->parent;
                Rotate(tree, node, parentDir);
            }

            node->parent->color = BLACK;
            node->parent->parent->color = RED;
            Rotate(tree, node->parent->parent, OppositeDirection(parentDir));
        }
    }

    tree->root->color = BLACK;
}

RBTNode* RBTInsert(RBTree* tree, const void* key, bool noDuplicates)
{
    RBTNode* currentNode = NULL;
    RBTNode* prevNode = SentinelLeaf;
    RBTNode* newNode = NULL;

    assert(tree != NULL);

    /* Find where the new node will go */
    currentNode = tree->root;
    while (!IsSentinel(currentNode)) {

        /* Return the equal node if no duplicates allowed */
        if (noDuplicates && tree->keyFuncs.Equal(key, currentNode->key)) return currentNode;

        prevNode = currentNode;

        if (tree->keyFuncs.Compare(key, currentNode->key)) {
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }

    /* Create the new node */
    if (!CreateNode(&newNode, tree, key, RED, prevNode)) return SentinelLeaf;

    if (IsSentinel(prevNode)) {
        /* New node is the root node */
        tree->root = newNode;
    }
    else {
        /* Else add new node to left or right of parent node */
        if (tree->keyFuncs.Compare(key, prevNode->key)) {
            prevNode->left = newNode;
        }
        else {
            prevNode->right = newNode;
        }
    }

    InsertRebalance(tree, newNode);
    return newNode;
}

/*****************************************************************************/
/* Node deletion functions                                                   */
/*****************************************************************************/

/* Replaces subtree rooted at node a with subtree rooted at node b */
static void TransplantNode(RBTree* tree, RBTNode* a, RBTNode* b)
{
    assert((tree != NULL) && (a != NULL) && (b != NULL));

    if (a == tree->root) {
        tree->root = b;
    }
    else {
        const RBTDirection aDir = GetChildDirection(a);
        a->parent->children[aDir] = b;
    }

    b->parent = a->parent;
}

/*
** Rebalance tree after deleting a node.
*/
static void DeleteRebalance(RBTree* tree, RBTNode* node)
{
    assert((tree != NULL) && (node != NULL));

    while ((node != tree->root) && (node->color == BLACK)) {
        const RBTDirection nodeDir = GetChildDirection(node);
        RBTNode* sibling = GetSibling(node);

        if (sibling->color == RED) {
            /* node is black and sibling is red */
            sibling->color = BLACK;
            node->parent->color = RED;

            Rotate(tree, node->parent, nodeDir);
            sibling = GetSibling(node);
        }

        if ((sibling->left->color == BLACK) && (sibling->right->color == BLACK)) {
            sibling->color = RED;
            node = node->parent;
        }
        else {
            const RBTDirection oppDir = OppositeDirection(nodeDir);

            if (sibling->children[oppDir]->color == BLACK) {
                sibling->children[nodeDir]->color = BLACK;
                sibling->color = RED;

                Rotate(tree, sibling, oppDir);
                sibling = GetSibling(node);
            }

            sibling->color = node->parent->color;
            node->parent->color = BLACK;
            sibling->right->color = BLACK;

            Rotate(tree, node->parent, nodeDir);
            node = tree->root;
        }
    }

    node->color = BLACK;
}

void RBTDeleteNode(RBTree* tree, RBTNode* node)
{
    RBTNode* rebalanceNode = NULL; /* Node where rebalancing begins */
    RBTNodeColor delColor = BLACK;

    assert((tree != NULL) && (node != NULL));
    assert(!IsSentinel(node));

    delColor = node->color;

    if (IsSentinel(node->left)) {
        rebalanceNode = node->right;
        TransplantNode(tree, node, rebalanceNode);
    }
    else if (IsSentinel(node->right)) {
        rebalanceNode = node->left;
        TransplantNode(tree, node, rebalanceNode);
    }
    else {
        RBTNode* successor = FindMinimum(node->right);

        delColor = successor->color;
        rebalanceNode = successor->right;

        if (successor != node->right) {
            /* If successor isn't the right child of node */
            TransplantNode(tree, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        else {
            /* If successor is the right child of node */
            rebalanceNode->parent = successor;
        }

        TransplantNode(tree, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
        successor->color = node->color;
    }

    if (delColor == BLACK) DeleteRebalance(tree, rebalanceNode);

    DestroyNode(tree, &node);
}
