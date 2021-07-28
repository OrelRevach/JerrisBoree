//
// Created by orelpc on 11/27/20.
//

#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static status FreeFunc(Element pair);

static Element CopyFunc(Element toCopy);

static bool CompearFunc(Element key1, Element key2);

static status PrintFunc(Element elem);

int hashSlot(hashTable ht, Element key);

struct hashTable_s {
    TransformIntoNumberFunction TransformIntoNumberFunction;
    // key funcs
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    //val funcs
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    //pair
    EqualFunction equalKey;

    int hashNumber;
    int num_elements;

    list *list_arr;
};


int hashSlot(hashTable ht, Element key) {
    int keyTrans = ht->TransformIntoNumberFunction(key);
    int slot = keyTrans % ht->hashNumber;
    return slot;
}


hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                          CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                          EqualFunction equalKey,
                          TransformIntoNumberFunction TransformIntoNumberFunction, int hashNumber) {
    if (hashNumber <= 0 || copyValue == NULL || copyKey == NULL || printValue == NULL || printKey == NULL ||
        freeValue == NULL
        || freeKey == NULL || TransformIntoNumberFunction == NULL || equalKey == NULL)
        return NULL;
    //mallocs
    hashTable ht = (hashTable) malloc(sizeof(struct hashTable_s));
    ht->hashNumber = hashNumber;
    ht->list_arr = (list *) malloc(hashNumber * sizeof(list));
    if (!(ht->list_arr) || !ht)
        return NULL;


    int i;
    for (i = 0; i < hashNumber; i++)
        ht->list_arr[i] = createLinkedList(FreeFunc, PrintFunc, CompearFunc, CopyFunc);


    ht->copyKey = copyKey;
    ht->freeKey = freeKey;
    ht->printKey = printKey;

    ht->freeValue = freeValue;
    ht->copyValue = copyValue;
    ht->printValue = printValue;


    ht->equalKey = equalKey;


    ht->TransformIntoNumberFunction = TransformIntoNumberFunction;
    ht->num_elements = 0;

    return ht;
}


status destroyHashTable(hashTable ht) {
    if (ht == NULL)
        return failure;
    for (int i = 0; i < ht->hashNumber; i++) {
        /* free the list the arr[i]*/
        destroyList(ht->list_arr[i]);
    }
    /*freeing the the arr of the Hash then the all struct*/
    free(ht->list_arr);
    free(ht);
    return success;
}




status addToHashTable(hashTable ht, Element key, Element value) {
    if (ht == NULL || key == NULL || value == NULL) return failure;
    char *newKey = ht->copyKey(key);
    Pair pair = createKeyValuePair(newKey, value, ht->copyKey, ht->freeKey, ht->printKey, ht->copyValue, ht->freeValue,
                                   ht->printValue, ht->equalKey);
    if (pair == NULL)
        return failure;
    int slot = hashSlot(ht, newKey);
    Element elem = searchByKeyInList(ht->list_arr[slot], key);
    if (elem != NULL) {
        return failure;
    }
    list ls = ht->list_arr[slot];
    if (ls)
        if (appendNode(ls, pair) == success) {
            ++ht->num_elements;
            return success;
        }
    return failure;
}



Element lookupInHashTable(hashTable ht, Element key) {
    if (ht == NULL || key == NULL)
        return NULL;
    int slot = hashSlot(ht, key);
    Element elem = searchByKeyInList(ht->list_arr[slot], key);
    if (elem != NULL) {
        return getValue(elem);
    }
    return NULL;
}


status removeFromHashTable(hashTable ht, Element key) {
    if (ht == NULL || key == NULL) return failure;
    int slot = hashSlot(ht, key);
    Element data = searchByKeyInList(ht->list_arr[slot], key);
    if (data != NULL) {
        deleteNode(ht->list_arr[slot], data);
        return success;
    }
    return failure;
}


status displayHashElements(hashTable ht) {
    if (ht == NULL)
        return failure;
    int i = 0;
    while (i < ht->hashNumber) {
        displayList(ht->list_arr[i]);
        i++;
    }
    return success;
}

static status PrintFunc(Element elem) {
    if (elem == NULL)
        return failure;
    displayValue(elem);
    return success;
}


static bool CompearFunc(Element key1, Element key2) {
    if (key1 == NULL || key2 == NULL)
        return false;
    return isEqualKey(key1, key2);
}


static Element CopyFunc(Element toCopy) {
    if (toCopy == NULL)
        return NULL;
    Pair newOne = (Pair) copyPair(toCopy);
    return newOne;
}


static status FreeFunc(Element pair) {
    if (pair == NULL)
        return 1;
    destroyKeyValuePair(pair);
    return 0;
}