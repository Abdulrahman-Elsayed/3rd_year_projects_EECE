using namespace std;

#include <iostream>
#include <string>

struct unit {
    string word;
    int lineNumber;
};

//typedef char* ListElemType;
//typedef string ListElemType;
typedef unit ListElemType;
class inord_list {
    public:
    inord_list();
    ~inord_list();
    bool is_empty();
    bool insert(const ListElemType &e);
    inord_list list_copy();
    void remove(const string &s);
    void remove_all();
    bool first(ListElemType &e);
    bool next(ListElemType &e);

    private:
    /*
    struct Node {
        ListElemType item;
        Node *next;
    }
    */
    struct Node;
    typedef Node* link;
    struct Node {
        ListElemType item;
        link next;
    };
    link head;
    link tail;
    link current;
};
