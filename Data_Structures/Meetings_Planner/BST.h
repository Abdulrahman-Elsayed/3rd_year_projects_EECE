#ifndef BST_H
#define BST_H

using namespace std;

template <class btElementType>
class BST {

public:
    BST();
    ~BST();
    void make_empty();
    bool isEmpty() const;
    btElementType getData() const;
    void insert(const btElementType & d);
    BST * retrieve(const btElementType & d);
    BST * left();
    BST * right();
    
private:
    bool nullTree;
    btElementType treeData;
    BST * leftTree;   
    BST * rightTree;  
};

#endif
