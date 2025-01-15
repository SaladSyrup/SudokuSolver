/*
** Set.h
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

#ifndef SET_H
#define SET_H

/*
** Implements a set backed by a red-black tree.
*/

#include "RBTree.h"

#include <stdbool.h>

/*
** Pointers to user-defined functions copy, destroy, equal, and compare. These
** functions are specific to the type of data stored in the set; see RBTree.h.
*/
typedef RBTKeyFunctions SetElementFunctions;
typedef RBTNode SetIterator;

typedef struct {
    RBTree* tree;
    SetIterator* iterator;
} _SetType;

typedef _SetType Set;

/*****************************************************************************/
/* Prototypes                                                                */
/*****************************************************************************/

/*
** Creates a new, empty set.
**
** If successful, the set parameter is updated to point to the newly created
** set and true is returned.
**
** If unsucessful, the set parameter is not modified and false is returned.
*/
bool SetCreate(Set** set, SetElementFunctions keyFuncs);

/*
** Destroys the set.
*/
void SetDestroy(Set** set);

/*
** Adds a new element to the set. Returns true if successful (the element was
** added or already exists in the set).
*/
bool SetInsert(Set* set, void* element);

/*
** Deletes an element from the set. Returns true if successful, and false if
** not (e.g., the element doesn't exist in the set.)
*/
bool SetDelete(Set* set, void* element);

/*
** Gets the next element in the set. Elements are unordered. SetIterate and
** SetPop functions may return elements in different orders.
**
** If successful, a copy of the element is placed in *element and true is
** returned.
**
** False is returned if no elements are remaining. Use SetResetIterator to
** begin again.
**
** The iterator is not reset by insertions and deletions that occur between
** calls to SetIterate. Therefore, if insertions occur after resetting the
** iterator, the iterator may reach the end of the set without returning all
** values. Always call SetResetIterator before iterating to ensure all set
** values are returned.
*/
bool SetIterate(Set* set, void** element);
void SetResetIterator(Set* set);

/*
** Gets an element and deletes it from the set. Elements are unordered.
** SetIterate and SetPop functions may return elements in different orders.
**
** If successful, a copy of the popped element is placed in *element and true
** is returned.
**
** If unsuccessful (e.g., the set is empty), false is returned and *element is
** not altered.
*/
bool SetPop(Set* set, void** element);

/*
** Returns true if set contains the element.
*/
bool SetContains(Set* set, void* element);

/*
** Clears the set of all elements. Returns true if successful.
*/
bool SetClear(Set* set);

/*
** Returns the number of elements in the set.
*/
unsigned int SetNumElements(Set* set);

/*
** Returns true if set is empty.
*/
bool SetIsEmpty(Set* set);

#endif // !SET_H
