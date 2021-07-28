
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "Defs.h"

typedef struct hashTable_s *hashTable;

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue,
                          FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey,
                          TransformIntoNumberFunction transformIntoNumber, int hashNumber);

status destroyHashTable(hashTable);

status addToHashTable(hashTable, Element key, Element value);

Element lookupInHashTable(hashTable, Element key);

status removeFromHashTable(hashTable, Element key);

status displayHashElements(hashTable);

#endif /* HASH_TABLE_H */
