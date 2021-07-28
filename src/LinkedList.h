//
// Created by orelpc on 11/27/20.
//

#ifndef JERRYBOREE_LINKEDLIST_H
#define JERRYBOREE_LINKEDLIST_H

#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node *node;

typedef struct _list *list;
/*Description:
Receiving data element create Node and returning
 Node - if success or Null if not.
*/
node nodeCreate(Element);
/*Description:
Receiving list and data element, delete Node and returning  the correct status:
success( if o/k  ) or failure ( if not).
*/
status deleteNode(list, Element);

/*Description:
Receiving 4 generic function: free, print, equal, and copy.
Create an empty list- if success  returning  the empty list.
If not(failure) - returning null.
*/
list createLinkedList(FreeFunction, PrintFunction, EqualFunction, CopyFunction);

/*Description:
Receiving list,destroying the list and returning  the correct status:
success( if o/k  ) or failure ( if not).
*/
status destroyList(list);
/*Description:
Receiving list and data element (node), adding it to the end of the list.
 returning  the correct status:
success( if o/k  ) or failure ( if not).
*/
status appendNode(list, Element);
/*Description:
Receiving list and data element (node), if the search find the Node by Key -
 returning the same element.
If not returning failure.
*/
Element searchByKeyInList(list, Element);
/*Description:
Receiving list and print it.
*/
void displayList(list);
/*Description:
Receiving list and data element (node) and print the element.
*/
void displayNode(list, Element);
/*Description:
Receiving list and returning the size of this list - (int).
*/
int getLengthList(list ls);
/*Description:
Receiving list and the index of one member in it.
 returning the data of that  specific index .
If it fail returning null.
*/
Element getDataByIndex(list ls, int index);

#endif //JERRYBOREE_LINKEDLIST_H
