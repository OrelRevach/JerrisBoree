//
// Created by orelpc on 11/27/20.
//

#include "LinkedList.h"


struct _node {
    Element data;
    node next;
};


struct _list {
    int length;
    node head;
    node tail;


    FreeFunction freef;
    PrintFunction printf;
    EqualFunction compareTo;
    CopyFunction copyf;
};


node nodeCreate(Element data) {
    node nd = (node) malloc(sizeof(struct _node));
    if (nd == NULL) {
        printf("Unable to allocate memory.");
        return NULL;
    }
    nd->data = data;
    nd->next = NULL;
    return nd;
}


list
createLinkedList(FreeFunction free_func, PrintFunction print_func, EqualFunction comp_func, CopyFunction copy_func) {
    list ls = (list) malloc(sizeof(struct _list));
    if (ls == NULL) {
        printf("Unable to allocate memory.");
        return NULL;
    }
    ls->length = 0;

    // Create/set head and tail nodes
    ls->head = NULL;
    ls->tail = NULL;

    // Pointer to a functions
    ls->freef = free_func;
    ls->printf = print_func;
    ls->compareTo = comp_func;
    ls->copyf = copy_func;

    return ls;
}




status appendNode(list ls, Element data) {
    if (ls == NULL || data == NULL) return failure;
    node nd = nodeCreate(data);
    node temp = ls->head;
    // If first item in list, set head
    if (!ls->head) {
        ls->head = nd;
        ls->tail = nd;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nd;
        ls->tail = nd;
    }
    ls->length++;
    return success;
}


status deleteNode(list ls, Element data) {
    if (ls == NULL || data == NULL || ls->length == 0) return 1;
    node tmp = NULL;
    node rem = NULL;

    if (ls->head == NULL) {
        return 1;
    }
    ls->length--;
    if (ls->head->data == data) {
        free(ls->head);
        ls->head = ls->head->next;
        ls->freef(data);
    } else {
        tmp = ls->head;
        while (!(tmp->next->data == data) && tmp->next != NULL) {
            tmp = tmp->next;
        }
        if (tmp == NULL) {
            return 1;
        } else {
            rem = tmp->next;
            tmp->next = tmp->next->next;
            ls->freef(rem->data);
            free(rem);
            return 0;
        }
    }
    return 1;
}


Element searchByKeyInList(list ls, Element data) {
    if (ls == NULL || data == NULL || ls->length == 0) return NULL;
    node current = ls->head;  // Initialize current
    while (current != NULL) {
        if (ls->compareTo(current->data, data) == true)
            return current->data;
        current = current->next;
    }
    return NULL;
}


void displayNode(list ls, Element data) {
    if (ls == NULL || data == NULL) return;
    ls->printf(data);
}


void displayList(list ls) {
    if (ls == NULL) return;
    node nd = ls->head;
    while (nd != NULL) {
        displayNode(ls, nd->data);
        nd = nd->next;
    }
}


status destroyList(list ls) {
    if (ls == NULL) return failure;
    node curr = ls->head;
    while (curr != NULL) {
        deleteNode(ls, curr->data);
        curr = curr->next;
    }
    free(ls);
    return success;
}

int getLengthList(list ls) {
    if (ls == NULL) {
        return 0;
    }
    return ls->length;
}

Element getDataByIndex(list ls, int index) {
    if (ls == NULL || ls->head == NULL || index < 0 || index > ls->length) {
        return NULL;
    }

    node temp;
    temp = ls->head;
    while (temp->next != NULL || index < 0) {
        if (index == 0) {
            return temp->data;
        }
        index--;
        temp = temp->next;
    }

    return temp->data;
}
