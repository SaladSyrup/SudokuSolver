/*
** GridLocationSet.c
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

#include "GridLocationSet.h"

#include <assert.h>

typedef union {
    void* ptr;
    GridLocation gridLocation;
} GLSKey;

/*****************************************************************************/
/* Key Functions                                                             */
/*****************************************************************************/

static void* GLSKeyCopy(const void* key)
{
    return (void*)key;
}

static void GLSKeyDestroy(void* key)
{
    key;
}

static bool GLSKeyEqual(const void* a, const void* b)
{
    return (a == b);
}

static bool GLSKeyCompare(const void* a, const void* b)
{
    return (a < b);
}

/*****************************************************************************/
/* Constructor and destructor                                                */
/*****************************************************************************/

bool GLSCreate(GridLocationSet** set)
{
    SetElementFunctions GLSKeyFuncs = { NULL };

    /* Verify GridLocation can be stored directly in a void pointer */
    assert(sizeof(void*) >= sizeof(GridLocation));

    GLSKeyFuncs.Copy = GLSKeyCopy;
    GLSKeyFuncs.Destroy = GLSKeyDestroy;
    GLSKeyFuncs.Equal = GLSKeyEqual;
    GLSKeyFuncs.Compare = GLSKeyCompare;

    return SetCreate(set, GLSKeyFuncs);
}

void GLSDestroy(GridLocationSet** set)
{
    SetDestroy(set);
}

/*****************************************************************************/
/* Insert and delete functions                                               */
/*****************************************************************************/

bool GLSInsert(GridLocationSet* set, GridLocation gridLoc)
{
    GLSKey key = { NULL };
    key.gridLocation = gridLoc;

    return SetInsert(set, key.ptr);
}

bool GLSDelete(GridLocationSet* set, GridLocation gridLoc)
{
    GLSKey key = { NULL };
    key.gridLocation = gridLoc;

    return SetDelete(set, key.ptr);
}

/*****************************************************************************/
/* Iterate, search, and pop functions                                        */
/*****************************************************************************/

bool GLSIterate(GridLocationSet* set, GridLocation* gridLoc)
{
    GLSKey key = { NULL };

    assert(gridLoc != NULL);

    if (SetIterate(set, &key.ptr)) {
        *gridLoc = key.gridLocation;
        return true;
    }

    return false;
}

void GLSResetIterator(GridLocationSet* set)
{
    SetResetIterator(set);
}

bool GLSPop(GridLocationSet* set, GridLocation* gridLoc)
{
    GLSKey key = { NULL };

    assert(gridLoc != NULL);

    if (SetPop(set, &key.ptr)) {
        *gridLoc = key.gridLocation;
        return true;
    }

    return false;
}

/*****************************************************************************/
/* Miscellaneous functions                                                   */
/*****************************************************************************/

bool GLSContains(GridLocationSet* set, GridLocation gridLoc)
{
    GLSKey key = { NULL };
    key.gridLocation = gridLoc;

    return SetContains(set, key.ptr);
}

bool GLSClear(GridLocationSet* set)
{
    return SetClear(set);
}

unsigned int GLSNumElements(GridLocationSet* set)
{
    return SetNumElements(set);
}

bool GLSIsEmpty(GridLocationSet* set)
{
    return SetIsEmpty(set);
}