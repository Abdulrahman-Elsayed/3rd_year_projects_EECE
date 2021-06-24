using namespace std;

#include <iostream>
#include "BST.h"


template <class btElementType>
BST <btElementType>::BST() {
    nullTree = true;
    leftTree = NULL;
    rightTree = NULL;
}

template <class btElementType>
BST <btElementType>::~BST() {
    delete leftTree;
    delete rightTree;
}

template <class btElementType>
void BST <btElementType>::make_empty() {
    nullTree = true;
    leftTree = NULL;
    rightTree = NULL;
}

template <class btElementType>
bool BST <btElementType>::isEmpty() const {
    return nullTree;
}

template <class btElementType>
btElementType BST <btElementType>::getData() const {
    //assert(!isEmpty());
    return treeData;
}

template <class btElementType>
void BST <btElementType>::insert(const btElementType & d) {
    if(nullTree) {
        nullTree = false;
        leftTree = new BST;
        rightTree = new BST;
        treeData = d;
    }
    else if (d.day < treeData.day)
        leftTree->insert(d);
    else if (d.day > treeData.day)
        rightTree->insert(d);    
    else {
        if (d.hour < treeData.hour)
            leftTree->insert(d);
        else if (d.hour > treeData.hour)
            rightTree->insert(d);  
    }    
}

template <class btElementType>
BST <btElementType> * BST <btElementType>::left() {
    //assert(!isEmpty());
    return leftTree;
}

template <class btElementType>
BST <btElementType> * BST <btElementType>::right() {
    //assert(!isEmpty());
    return rightTree;
}

template <class btElementType>
BST <btElementType> * BST <btElementType>::retrieve(const btElementType & d) {
    if ((nullTree) || ((d.day == treeData.day) && (d.hour == treeData.hour))) 
        return this;
    else if (d.day < treeData.day)    
        return leftTree->retrieve(d);
    else  if (d.day > treeData.day)  
        return rightTree->retrieve(d);  
    else {
        if (d.hour < treeData.hour)    
            return leftTree->retrieve(d);
        else 
            return rightTree->retrieve(d); 
    }    
}
