//
// Created by orelpc on 11/27/20.
//

#include "KeyValuePair.h"


struct keyValuePair_t {
    Element value;
    Element key;

    //key func
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    //val func
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;

    //pair
    EqualFunction equalKey;

};


Pair createKeyValuePair(Element key, Element value, CopyFunction copyKey, FreeFunction freeKey,
                        PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                        PrintFunction printValue, EqualFunction equalKey) {
    Pair newPair = (Pair) malloc(sizeof(struct keyValuePair_t));
    if (newPair == NULL) {
        printf("Unable to allocate memory.");
        return NULL;
    }

    newPair->key = key;
    newPair->value = value;

    newPair->copyKey = copyKey;
    newPair->freeKey = freeKey;
    newPair->printKey = printKey;

    newPair->copyValue = copyValue;
    newPair->freeValue = freeValue;
    newPair->printValue = printValue;

    newPair->equalKey = equalKey;

    return newPair;
}


status destroyKeyValuePair(Pair pair) {
    if (pair == NULL) {
        return failure;
    }

    if (pair->key != NULL) {
        pair->freeKey(pair->key);
    }
    if (pair->value) {
        pair->freeValue(pair->value);
    }
    free(pair);
    return success;
}


void displayValue(Pair pair) {
    if (pair == NULL || (pair->value) == NULL)
        return;
    pair->printValue(pair->value);
}


void displayKey(Pair pair) {
    if (pair == NULL || pair->key == NULL)
        return;
    pair->printKey(pair->key);
}

Element getValue(Pair pair) {
    if (pair == NULL || pair->value == NULL)
        return NULL;

    return pair->value;
}

Element getKey(Pair pair) {
    if (pair == NULL || (pair->key) == NULL)
        return NULL;

    return pair->key;
}


bool isEqualKey(Pair p1, char *p2) {
    if (p1 == NULL || p2 == NULL)
        return false;

    return p1->equalKey(p1->key, p2);
}


CopyFunction copyPair(Element elem) {
    if (elem == NULL)
        return NULL;

    Pair p = (Pair) elem;
    Pair p2 = createKeyValuePair(p->key, p->value, p->copyKey, p->freeKey,
                                 p->printKey, p->copyValue, p->freeValue, p->printValue, p->equalKey);
    return (Element) p2;
}

status destroyKeyValuePairOnlyPair(Pair pair) {
    if (pair == NULL) {
        return failure;
    }

    if (pair->key != NULL) {
        free(pair->key);
    }
    if (pair->value) {
        free(pair->value);
    }
    free(pair);
    return success;
}