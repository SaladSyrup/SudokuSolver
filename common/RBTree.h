/*
** RBTree.h
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

#ifndef RBTREE_H
#define RBTREE_H

/*
** Implements a red-black tree.
*/

#include <stdbool.h>

/*****************************************************************************/
/* Key Functions                                                             */
/*****************************************************************************/

/*
** Structure RBTKeyFunctions contains pointers to user-defined functions
** specific to the type of keys used in the tree.
**
** Keys are stored internally as void pointers.
*/
typedef struct {
    /*
    ** Creates a copy of the key that's independent of the original such that
    ** changes to the original do not modify the key stored in the tree.
    ** Called when inserting a new node.
    */
    void* (*Copy)(const void* key);

    /*
    ** Destroys the key. Called when deleting a node or destroying the tree.
    */
    void (*Destroy)(void* key);

    /*
    ** Returns true if keys a and b are equal.
    */
    bool (*Equal)(const void* a, const void* b);

    /*
    ** Returns true if key a is before key b when ordered.
    */
    bool (*Compare)(const void* a, const void* b);

} RBTKeyFunctions;

/*****************************************************************************/
/* Tree Components                                                           */
/*****************************************************************************/

typedef enum {
    RED,
    BLACK,
} RBTNodeColor;

typedef enum {
    LEFT = 0,
    RIGHT,
    NUM_CHILDREN,
} RBTDirection;

typedef struct _RBTNode {
    void* key;
    RBTNodeColor color;
    struct _RBTNode* parent;
    struct _RBTNode* children[NUM_CHILDREN];
} RBTNode;

typedef struct {
    RBTNode* root;
    RBTKeyFunctions keyFuncs;
} _RBTreeType;

typedef _RBTreeType RBTree;

extern RBTNode* const RBTNilNode;

/*****************************************************************************/
/* Prototypes                                                                */
/*****************************************************************************/

/*
** Creates a new, empty red-black tree.
**
** If successful, the tree parameter is updated to point to the newly created
** tree and true is returned.
**
** If unsucessful, the tree paramenter is not modified and false is returned.
*/
bool RBTCreate(RBTree** tree, RBTKeyFunctions keyFuncs);

/*
** Destroys the red-black tree. Traverses the tree, calling
** RBTKeyFunctions.destroy on each key and then destroying the node.
*/
void RBTDestroy(RBTree** tree);

/*
** Insert key into tree. Returns a pointer to the new node if successful or
** the NIL node if not.
**
** If noDuplicates is true and an equal key already exists in the tree,
** then a pointer to the already existing node will be returned.
*/
RBTNode* RBTInsert(RBTree* tree, const void* key, bool noDuplicates);

/*
** Delete node from tree.
*/
void RBTDeleteNode(RBTree* tree, RBTNode* node);

/*
** Returns node containing the miminum or maximum key value in the tree.
*/
RBTNode* RBTMin(RBTree* tree);
RBTNode* RBTMax(RBTree* tree);

/*
** Return successor and predecessor nodes. Returns NIL node when end is
** reached.
*/
RBTNode* RBTSuccessor(RBTNode* node);
RBTNode* RBTPredecessor(RBTNode* node);

/*
** Searches tree for key.
**
** Returns the node if successful, or the NIL node if not.
*/
RBTNode* RBTSearch(RBTree* tree, const void* key);

/*
** Returns true if node is NIL
*/
bool RBTIsNil(const RBTNode* node);

/*
** Return number of nodes in the tree.
*/
unsigned int RBTNumNodes(RBTree* tree);

#endif // !RBTREE_H
