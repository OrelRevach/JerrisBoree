//
// Created by ise on 4.12.2020.
//

#ifndef JERRYBOREE_MULTIVALUEHASHTABLE_H
#define JERRYBOREE_MULTIVALUEHASHTABLE_H

#include "HashTable.h"
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct MultiValueHashTable_s *MultiValueHashTable;

MultiValueHashTable
createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                          FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                          TransformIntoNumberFunction transformIntoNumber, int hashNumber);

status destroyMultiValueHashTable(MultiValueHashTable);

status addToMultiValueHashTable(MultiValueHashTable, Element, Element);

Element lookupInMultiValueHashTable(MultiValueHashTable, Element key);

status removeFromMultiValueHashTable(MultiValueHashTable, Element key, Element value);

status displayMultiValueHashElementsByKey(MultiValueHashTable);


#endif //JERRYBOREE_MULTIVALUEHASHTABLE_H
