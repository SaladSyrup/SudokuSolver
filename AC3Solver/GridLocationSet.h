/*
** GridLocationSet.h
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

#ifndef GRIDLOCATIONSET_H
#define GRIDLOCATIONSET_H

#include "../common/Set.h"

#include "../Region.h"

/*
** GridLocation wrapper for Set. See Set.h for a thorough description of each
** function.
*/

typedef Set GridLocationSet;

/*****************************************************************************/
/* Prototypes                                                                */
/*****************************************************************************/

/*
** Creates a new, empty set of GridLocation values.
*/
bool GLSCreate(GridLocationSet** set);

/*
** Destroys the set.
*/
void GLSDestroy(GridLocationSet** set);

/*
** Add a new GridLocation to the set.
*/
bool GLSInsert(GridLocationSet* set, GridLocation gridLoc);

/*
** Delete a GridLocation from the set.
*/
bool GLSDelete(GridLocationSet* set, GridLocation gridLoc);

/*
** Get the next GridLocation in the set. GridLocations are unordered.
** GLSIterate and GLSPop functions may return GridLocations in different
** orders.
*/
bool GLSIterate(GridLocationSet* set, GridLocation* gridLoc);
void GLSResetIterator(GridLocationSet* set);

/*
** Get a GridLocation and delete it from the set. GridLocations are unordered.
** GLSIterate and GLSPop functions may return GridLocations in different
** orders.
*/
bool GLSPop(GridLocationSet* set, GridLocation* gridLoc);

/*
** Returns true if set contains the GridLocation.
*/
bool GLSContains(GridLocationSet* set, GridLocation gridLoc);

/*
** Clears the set of all GridLocations. Returns true if successful.
*/
bool GLSClear(GridLocationSet* set);

/*
** Returns the number of GridLocations in the set.
*/
unsigned int GLSNumElements(GridLocationSet* set);

/*
** Returns true if set is empty.
*/
bool GLSIsEmpty(GridLocationSet* set);

#endif // !GRIDLOCATIONSET_H
