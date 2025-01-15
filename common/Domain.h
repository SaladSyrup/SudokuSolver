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
typedef unsigned short DomBitField;
typedef unsigned int DomElementValue;

struct _DomainType {
    DomBitField domain;
    DomElementValue minValue;
    DomElementValue numElements;
};

typedef struct _DomainType Domain;

/*
** Creates a new domain with the given values. If fullDomain is true the
** created domain will be full; otherwise it will be empty.
*/
Domain DomCreate(const DomElementValue minValue, const DomElementValue numElements, const bool fullDomain);

/*
** Adds or removes an element from the domain. Behavior is undefined if element
** is outside the range minValue to (minValue + numElements - 1).
**
** Returns true if domain was updated or false if domain was not updated. In
** other words:
** 
**   - DomAddElement returns false if element was already in the domain.
**   - DomRemoveElement returns false if element was not in the domain.
*/
bool DomAddElement(Domain* domain, const DomElementValue element);
bool DomRemoveElement(Domain* domain, const DomElementValue element);

/*
** Returns the least or most significant value in the domain.
**
** Behavior is undefined if domain is empty.
*/
DomElementValue DomGetLSValue(const Domain domain);
DomElementValue DomGetMSValue(const Domain domain);

/*
** Sets the domain to be full or empty.
*/
void DomSetFull(Domain* domain);
void DomSetEmpty(Domain* domain);

/*
** Returns true if domain contains element. Behavior is undefined if element is
** outside the range minValue to (minValue + numElements - 1).
*/
bool DomContainsElement(const Domain domain, const DomElementValue element);

/*
** Functions for determining number of elements.
*/
unsigned int DomNumElements(const Domain domain);
bool DomIsEmptyDomain(const Domain domain);
bool DomIsFullDomain(const Domain domain);
bool DomIsSingletonDomain(const Domain domain);

/*
** Domain operations. Behavior is undefined if both domains do not have the
** same minValue and numElements.
*/
Domain DomUnion(const Domain a, const Domain b);
Domain DomIntersection(const Domain a, const Domain b);

#endif // !DOMAIN_H
