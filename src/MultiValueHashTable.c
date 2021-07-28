//
// Created by ise on 4.12.2020.
//
#include "MultiValueHashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"

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

struct MultiValueHashTable_s {
    TransformIntoNumberFunction TransformIntoNumberFunctionValue;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    //val funcs
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    //pair
    EqualFunction equalKey;
    hashTable ht;
};

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                              CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                              EqualFunction equalKey,
                                              TransformIntoNumberFunction TransformIntoNumberFunction, int hashNumber) {
    if (hashNumber <= 0 || copyValue == NULL || copyKey == NULL || printValue == NULL || printKey == NULL ||
        freeValue == NULL
        || freeKey == NULL || TransformIntoNumberFunction == NULL || equalKey == NULL)
        return NULL;
    //mallocs
    MultiValueHashTable multHt = (MultiValueHashTable) malloc(sizeof(struct MultiValueHashTable_s));
    hashTable ht = createHashTable(copyKey, freeKey, printKey,
                                   copyValue, copyValue, printValue, equalKey,
                                   TransformIntoNumberFunction, hashNumber);
    multHt->ht = ht;
    if (!(multHt->ht) || !multHt) {
        return NULL;
    }
    // key functions
    multHt->copyKey = copyKey;
    multHt->freeKey = freeKey;
    multHt->printKey = printKey;
    // value functions

    multHt->freeValue = freeValue;

    multHt->copyValue = copyValue;
    multHt->printValue = printValue;
    // pair functions
    multHt->equalKey = equalKey;

    return multHt;
}



status destroyMultiValueHashTable(MultiValueHashTable ht) {
    if (ht == NULL)
        return failure;
    for (int i = 0; i < ht->ht->hashNumber; i++) {

        destroyList(ht->ht->list_arr[i]);
    }
    free(ht->ht->list_arr);
    free(ht->ht);
    free(ht);
    return success;
}

status addToMultiValueHashTable(MultiValueHashTable mvht, Element key, Element value) {
    if (mvht == NULL || key == NULL || value == NULL) return failure;
//    return addToHashTable(mvht->ht, key, value);
    list *temp;
    list *newList;
    temp = lookupInMultiValueHashTable(mvht, key);
    if (temp != NULL) {
        appendNode(temp, (Element) value);
    } else {
        //char *keyHash=mvht->copyKey(key);
        newList = createLinkedList(mvht->freeValue, mvht->printValue, mvht->equalKey, mvht->copyValue);
        appendNode(newList, value);
        addToHashTable(mvht->ht, key, newList);
    }
}


Element lookupInMultiValueHashTable(MultiValueHashTable ht, Element key) {
    if (ht == NULL || key == NULL)
        return NULL;
    int slot = hashSlot(ht->ht, key);
    Element elem = searchByKeyInList(ht->ht->list_arr[slot], key);

    if (elem != NULL) {
        return getValue(elem);
    }

    return NULL;
}



status removeFromMultiValueHashTable(MultiValueHashTable ht, Element key, Element value) {
    list TempTairlist = lookupInMultiValueHashTable(ht, key);
    deleteNode(TempTairlist, value);
}

//
//
status displayMultiValueHashElementsByKey(MultiValueHashTable ht) {
    list *temp1;
    temp1 = lookupInMultiValueHashTable(ht, "jerryJoy");
    if (temp1 == NULL || getLengthList(temp1) == 0) {
        return failure;
    } else {
        displayList(temp1);
    }
    return success;
}



static status FreeFunc(Element pair) {
    if (pair == NULL)
        return 1;
    destroyKeyValuePair(pair);
    return 0;
}

