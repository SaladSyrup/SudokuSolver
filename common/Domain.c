/*
** Domain.c
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

#include "Domain.h"

#include <assert.h>

Domain DomCreate(const DomElementValue minValue, const DomElementValue numElements, const bool fullDomain)
{
    Domain domain = { 0 };

    assert((sizeof(DomBitField) * 8) >= numElements);

    domain.minValue = minValue;
    domain.numElements = numElements;

    if (fullDomain) {
        DomSetFull(&domain);
    }
    else {
        DomSetEmpty(&domain);
    }

    return domain;
}

bool DomAddElement(Domain* domain, const DomElementValue element)
{
    DomBitField bitMask = 0;

    assert(domain != NULL);
    assert((sizeof(DomBitField) * 8) >= domain->numElements);
    assert((element >= domain->minValue) && (element < (domain->minValue + domain->numElements)));

    bitMask = 0x1 << (element - domain->minValue);

    if (domain->domain & bitMask) return false;    /* Element is already in the domain */

    domain->domain |= bitMask;
    return true;
}

bool DomRemoveElement(Domain* domain, const DomElementValue element)
{
    DomBitField bitMask = 0;

    assert(domain != NULL);
    assert((sizeof(DomBitField) * 8) >= domain->numElements);
    assert((element >= domain->minValue) && (element < (domain->minValue + domain->numElements)));

    bitMask = 0x1 << (element - domain->minValue);

    if (!(domain->domain & bitMask)) return false;     /* Element is not in the domain */

    domain->domain &= ~bitMask;
    return true;
}

void DomSetFull(Domain* domain)
{
    assert(domain != NULL);
    assert((sizeof(DomBitField) * 8) >= domain->numElements);

    domain->domain = ~((DomBitField)(~0x0) << domain->numElements);
}

void DomSetEmpty(Domain* domain)
{
    assert(domain != NULL);

    domain->domain = 0;
}

unsigned int DomNumElements(const Domain domain)
{
    DomBitField bitMask = 0x1 << (domain.numElements - 1);
    unsigned int numElements = 0;

    assert((sizeof(DomBitField) * 8) >= domain.numElements);

    do {
        if (domain.domain & bitMask) ++numElements;
    } while ((bitMask >>= 1) > 0);

    return numElements;
}

bool DomIsEmptyDomain(const Domain domain)
{
    const DomBitField emptyField = ((DomBitField)(~0x0) << domain.numElements);

    assert((sizeof(DomBitField) * 8) >= domain.numElements);

    return ((domain.domain | emptyField) ==  emptyField);
}

bool DomIsFullDomain(const Domain domain)
{
    const DomBitField fullField = ~((DomBitField)(~0x0) << domain.numElements);

    assert((sizeof(DomBitField) * 8) >= domain.numElements);

    return ((domain.domain & fullField) ==  fullField);
}

bool DomIsSingletonDomain(const Domain domain)
{
    return (DomNumElements(domain) == 1);
}

bool DomContainsElement(const Domain domain, const DomElementValue element)
{
    const DomBitField bitMask = 0x1 << (element - domain.minValue);

    assert((sizeof(DomBitField) * 8) >= domain.numElements);
    assert((element >= domain.minValue) && (element < (domain.minValue + domain.numElements)));

    return (domain.domain & bitMask);
}

Domain DomUnion(const Domain a, const Domain b)
{
    Domain newDomain = { 0 };

    assert(a.minValue == b.minValue);
    assert(a.numElements == b.numElements);

    newDomain.domain = a.domain | b.domain;
    newDomain.minValue = a.minValue;
    newDomain.numElements = a.numElements;

    return newDomain;
}

Domain DomIntersection(const Domain a, const Domain b)
{
    Domain newDomain = { 0 };

    assert(a.minValue == b.minValue);
    assert(a.numElements == b.numElements);

    newDomain.domain = a.domain & b.domain;
    newDomain.minValue = a.minValue;
    newDomain.numElements = a.numElements;

    return newDomain;
}