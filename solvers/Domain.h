/*
** Domain.h
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

#ifndef DOMAIN_H
#define DOMAIN_H

/*
** Maintains a set of integer values within a bitfield. Allowable element
** values are all integers between minValue and (minValue + numElements - 1).
*/

#include <stdbool.h>

/* The number of bits in BitField must be >= numElements */
typedef unsigned short BitField;
typedef unsigned int ElementValue;

typedef struct {
    BitField domain;
    ElementValue minValue;
    ElementValue numElements;
} Domain;

/*
** Adds or removes an element from the domain. Behavior is undefined if element
** is outside the range minValue to (minValue + numElements - 1).
**
** Returns true if domain was updated or false if domain was not updated. In
** other words:
** 
**   - AddElement returns false if element was already in the domain.
**   - RemoveElement returns false if element was not in the domain.
*/
bool AddElement(Domain* domain, const ElementValue element);
bool RemoveElement(Domain* domain, const ElementValue element);

/*
** Returns true if domain contains element. Behavior is undefined if element is
** outside the range minValue to (minValue + numElements - 1).
*/
bool ContainsElement(const Domain domain, const ElementValue element);

/*
** Functions for determining number of elements.
*/
unsigned int NumElements(const Domain domain);
bool IsEmptyDomain(const Domain domain);
bool IsFullDomain(const Domain domain);
bool IsSingletonDomain(const Domain domain);

/*
** Domain operations. Behavior is undefined if both domains do not have the
** same minValue and numElements.
*/
Domain Union(const Domain a, const Domain b);
Domain Intersection(const Domain a, const Domain b);

#endif // !DOMAIN_H
