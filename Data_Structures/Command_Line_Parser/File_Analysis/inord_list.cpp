#include <iostream>
#include "inord_list.h"

inord_list::inord_list() {
    head = NULL;
    tail = NULL;
    current = NULL; 
}

inord_list::~inord_list() {
    remove_all();
}

bool inord_list::is_empty() {
    if ((head == NULL) && (tail == NULL)) 
        return true;
    else 
        return false;    
}

bool inord_list::insert(const ListElemType &e) {
    link addedNode;
    link pred;

    addedNode = new Node;
    if (addedNode == NULL)
        return false;
    else
        addedNode->item = e;

    if (head == NULL) { // first insert
        addedNode->next = head;
        head = addedNode;
        tail = addedNode;
        return true;
    }
    else if (e.word <= head->item.word) { // insert in the left
    	addedNode->next = head;
        head = addedNode;
        return true;
    }
    else if (e.word > tail->item.word) { // insert in the left
        tail->next = addedNode;
    	addedNode->next = NULL;
        tail = addedNode;
        return true;
    }
    else {
        pred = head;
        while ((pred->next != NULL) && (pred->next->item.word < e.word))
            pred = pred->next;
        addedNode->next = pred->next;
        pred->next = addedNode;
        return true;
    }
}

inord_list inord_list::list_copy() {
    link ptr;
    inord_list list_new;
    if (head == NULL) { // list is empty
        return list_new;
    }
    else {
        ptr = head;
        while (ptr != NULL) {
            list_new.insert(ptr->item);
            ptr = ptr->next;
        }     
    }
    return list_new;
}

void inord_list::remove(const string &s) {

    link ptr_temp;
    link ptr_pre;
    ptr_pre = head;
    if ((head == NULL) && (tail == NULL)) {} // if empty list, do nothing

    else if (head == tail) { // if one element
        if (head->item.word == s) {
            delete head;
            head = NULL;
            tail = NULL;
        }
    }
    else {
        while (ptr_pre->next != NULL) {
            if (head->item.word == s) { // if first element
                ptr_temp = head;
                head = head->next;
                ptr_pre = head;
                delete ptr_temp;
            }
            else if (ptr_pre->next->item.word == s) {
                ptr_temp = ptr_pre->next;
                ptr_pre->next = ptr_temp->next;
                delete ptr_temp;
            }
            else {
                ptr_pre = ptr_pre->next;
            }
        }
    }
}

void inord_list::remove_all() {
    link ptr_temp;
    while (head != NULL) {
        ptr_temp = head;
        head = head->next;
        delete ptr_temp;
    }
    tail = NULL; 
    current = NULL;
}

bool inord_list::first(ListElemType &e) {
    if (head == NULL)
        return false;
    else {
        current = head;
        e = current->item;
        return true;
    }
}

bool inord_list::next(ListElemType &e) {
	if ((current == NULL) || (current->next == NULL))
        return false;
    else {
        current = current->next;
        e = current->item;
        return true;
    }
}
