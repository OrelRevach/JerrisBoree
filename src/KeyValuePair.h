//
// Created by orelpc on 11/27/20.
//

#ifndef JERRYBOREE_KEYVALUEPAIR_H
#define JERRYBOREE_KEYVALUEPAIR_H

#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct keyValuePair_t *Pair;
/*Description:
Receiving: 2 (generic) Elements: one for key and one for value.
In addition - 7 function by this critical order for use of the Pair:
3 function for the key: (Copy_Function, Free_Function, Print_Function).
 3 function for the value: (Copy_Function, Free_Function, Print_Function).
 The last(7) function  check equal_Key- Checking if the two keys are Equal.

Returning Pair*  or null if  it is not succeed.
*/
Pair createKeyValuePair(Element, Element, CopyFunction copyKey, FreeFunction freeKey,
                        PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue,
                        PrintFunction printValue, EqualFunction equalKey);

/*Description:
Receiving: Pair
Displaying the Pair .
 return success or failure
*/
status destroyKeyValuePair(Pair);
/*Description:
Receiving: Pair
Displaying the Value .
*/
void displayValue(Pair);
/*Description:
Receiving: Pair
Displaying the key .
*/
void displayKey(Pair);
/*Description:
Receiving: Pair
Geting the Value .
If it is not succeed return Null.
*/
Element getValue(Pair);
/*Description:
Receiving: Pair
Geting the key .
If it is not succeed return Null.
*/
Element getKey(Pair);
/*Description:
Receiving: pair and char* (key Element of the Pair).
Checking if the two elements are Equal .
Returning true - if they are the same, or
false if they are not.
*/
bool isEqualKey(Pair p1, char *p2);
status destroyKeyValuePairOnlyPair(Pair pair);
CopyFunction copyPair(Element);


#endif //JERRYBOREE_KEYVALUEPAIR_H


