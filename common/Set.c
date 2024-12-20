/*
** Set.c
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

#include "Set.h"

#include <assert.h>
#include <stdlib.h>

/*****************************************************************************/
/* Constructor and Destructor                                                */
/*****************************************************************************/

bool SetCreate(Set** set, SetElementFunctions keyFuncs)
{
    Set* newSet = (Set*)malloc(sizeof(Set));
    RBTree* tree = NULL;

    assert(set != NULL);

    RBTCreate(&tree, keyFuncs);

    if ((newSet == NULL) || (tree == NULL)) {
        SetDestroy(&newSet);
        RBTDestroy(&tree);
        return false;
    }

    newSet->numElements = 0;
    newSet->tree = tree;
    SetResetIterator(newSet);

    *set = newSet;
    return true;
}

void SetDestroy(Set** set)
{
    if ((set != NULL) && (*set != NULL)) {

        RBTDestroy(&(*set)->tree);

        free(*set);
        *set = NULL;
    }
}

/*****************************************************************************/
/* Insert and delete functions                                               */
/*****************************************************************************/

bool SetInsert(Set* set, void* element)
{
    RBTNode* result = NULL;

    assert((set != NULL) && (set->tree != NULL));

    result = RBTInsert(set->tree, element, true);
    if (RBTIsNil(result)) return false;

    ++set->numElements;
    return true;
}

bool SetDelete(Set* set, void* element)
{
    RBTNode* toDeleteNode = NULL;

    assert((set != NULL) && (set->tree != NULL));

    toDeleteNode = RBTSearch(set->tree, element);
    if (RBTIsNil(toDeleteNode)) return false;

    /* If we're deleting the node pointed to by the iterator... */
    if (set->iterator == toDeleteNode) {
        /* ...then move iterator to next value before deleting. */
        set->iterator = RBTSuccessor(set->iterator);
    }

    RBTDeleteNode(set->tree, toDeleteNode);
    --set->numElements;

    return true;
}

/*****************************************************************************/
/* Iterate, search, and pop functions                                        */
/*****************************************************************************/

/* set->iterator points to next value to be returned */
bool SetIterate(Set* set, void** element)
{
    assert((set != NULL) && (element != NULL));

    if (RBTIsNil(set->iterator)) return false;

    *element = set->tree->keyFuncs.Copy(set->iterator->key);
    set->iterator = RBTSuccessor(set->iterator);

    return true;
}

void SetResetIterator(Set* set)
{
    assert((set != NULL) && (set->tree != NULL));

    if (RBTIsNil(set->tree->root)) {
        set->iterator = RBTNilNode;
    }
    else {
        set->iterator = RBTMin(set->tree);
    }
}

/* Always pops the root node */
bool SetPop(Set* set, void** element)
{
    assert((set != NULL) && (set->tree != NULL));
    assert(element != NULL);

    if (RBTIsNil(set->tree->root)) return false;

    *element = set->tree->keyFuncs.Copy(set->tree->root->key);

    /* If we're deleting the node pointed to by the iterator... */
    if (set->iterator == set->tree->root) {
        /* ...then move iterator to next value before deleting. */
        set->iterator = RBTSuccessor(set->iterator);
    }

    RBTDeleteNode(set->tree, set->tree->root);
    --set->numElements;

    return true;
}

bool SetContains(Set* set, void* element)
{
    RBTNode* result;

    assert((set != NULL) && (set->tree != NULL));

    result = RBTSearch(set->tree, element);

    return (!RBTIsNil(result));
}

/*****************************************************************************/
/* Miscellaneous functions                                                   */
/*****************************************************************************/

bool SetClear(Set* set)
{
    RBTree* newTree = NULL;

    assert((set != NULL) && (set->tree != NULL));

    RBTCreate(&newTree, set->tree->keyFuncs);
    if (newTree == NULL) return false;

    RBTDestroy(&set->tree);
    set->tree = newTree;
    set->numElements = 0;
    SetResetIterator(set);

    return true;
}

unsigned int SetNumElements(Set* set)
{
    assert(set != NULL);
    return set->numElements;
}

bool SetIsEmpty(Set* set)
{
    assert(set != NULL);
    return (set->numElements == 0);
}