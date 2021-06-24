using namespace std;

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "BST.h"
#include "BST.cpp"

struct Meeting {
    string title;
    int day;
    int hour;
};

typedef BST <Meeting> Tree;
typedef Tree * TreePtr;

vector<string> command_select(string &line) { 
    int i = 0;
    string temp;
    vector<string> tokens; // hello \0
    while(i < line.length() + 1) { // the +1 accounts for the \0 char
        if (line[i] == 13)
        ;
        else if ((line[i] == '\0') || (line[i] == ' ') || (line[i] == '\t')) {
            if (temp != "") {
                tokens.push_back(temp);
                temp = "";
            }
        }
        else if (line[i] == '\"') {
            if (temp != "") {
                tokens.push_back(temp);
                temp = "";
            }
            i++;
            temp += "\"";
            while ((i < line.length() + 1) && (line[i] != '\"')) {
                temp += line[i];
                i++; 
            }
            temp += "\"";
        }
        else {  // ADD "Physics Lecture 1" 5 9
            temp += line[i];
        }
        i++;
    }
    return tokens;
}

void inOrderTraverse_to_print(TreePtr treePtr) {
    if (!treePtr->isEmpty()) {
        inOrderTraverse_to_print(treePtr->left());
        //cout << treePtr << ' ';
        //cout << treePtr->left() << ' ';
        //cout << treePtr->right() << ' ';
        cout << treePtr->getData().title << ' ';
        cout << treePtr->getData().day << ' ';
        cout << treePtr->getData().hour << endl;
        inOrderTraverse_to_print(treePtr->right());
    }
}

void inOrderTraverse_to_insert(TreePtr treePtr_to_insert_in, TreePtr treePtr_to_insert_from) {
    if (!treePtr_to_insert_from->isEmpty()) {
        inOrderTraverse_to_insert(treePtr_to_insert_in, treePtr_to_insert_from->left());
        treePtr_to_insert_in->insert(treePtr_to_insert_from->getData());
        inOrderTraverse_to_insert(treePtr_to_insert_in, treePtr_to_insert_from->right());
    }
}

void print(TreePtr t) {
    if(t->isEmpty()) 
        cout << "Empty Planner" << endl;
    else    
        inOrderTraverse_to_print(t);
}

void ADD(TreePtr t, Meeting m) {
    if(t->retrieve(m)->isEmpty())
        t->insert(m);
    else       
        cout << "Conflict " << m.day << " " << m.hour << endl;
}

void Find(TreePtr t, int d, int h) {
    Meeting meeting_to_search = {"any thing", d, h};
    if(t->retrieve(meeting_to_search)->isEmpty())
        cout << "Empty " << d << " " << h << endl;
    else {
        Meeting meeting_to_print = t->retrieve(meeting_to_search)->getData();
        cout << meeting_to_print.title << endl;
    } 
}

void DEL(TreePtr t, int d, int h) {
    Meeting meeting_to_search = {"any thing", d, h};
    TreePtr ptrTemp = t->retrieve(meeting_to_search);
    if(ptrTemp->isEmpty())
        cout << "Empty " << d << " " << h << endl;
    else {
        //TreePtr ptrTemp = t->retrieve(meeting_to_search);
        //cout << ptrTemp << endl;
        TreePtr ptrTemp_left = ptrTemp->left();
        TreePtr ptrTemp_right = ptrTemp->right();

        ptrTemp->make_empty();

        if (!ptrTemp_left->isEmpty()) {
            inOrderTraverse_to_insert(t, ptrTemp_left);
        }  
        if (!ptrTemp_right->isEmpty()) {
            inOrderTraverse_to_insert(t, ptrTemp_right);
        } 
        delete ptrTemp_left;
        delete ptrTemp_right;
    }
}

void MOD(TreePtr t, string title, int d, int h) {
    Meeting meeting_to_search = {"any thing", d, h};
    if(t->retrieve(meeting_to_search)->isEmpty())
        cout << "Empty " << d << " " << h << endl;
    else {
        DEL(t, d, h);
        Meeting meeting_to_insert = {title, d, h};
        t->insert(meeting_to_insert);
    }
}

int main(int argc, char *argv[]) {

    TreePtr meetings_tree = new Tree;
    //cout << meetings_tree << endl;
    string line; // to store the read line
    vector<string> arguments;
    ifstream comamnds_file (argv[1]);
    int if_continue1 = 1;
    int if_continue2 = 1;
    string command;
    string title;
    string day_str;
    string hour_str;
    int day;
    int hour;


	if (comamnds_file.is_open()) {
	    while (getline(comamnds_file, line)) {
            if (line != "") {
                arguments = command_select(line);
                //for (int i = 0; i < arguments.size(); i++) {
                //    cout << arguments[i] << endl;
                //}
                if_continue1 = 1; // to cheack if all argumenets are ok and it's safe to do the calculations
                if_continue2 = 1;
                if (arguments.size() > 0)
                    command = arguments[0];

                if (command == "ADD") {
                    if (arguments.size() != 4) {
                        cout << "Invalid arguments" << endl;
                    }
                    else {
                        title = arguments[1];
                        day_str = arguments[2]; 
                        hour_str = arguments[3]; 

                        if (title[0] != '\"') {
                            cout << "Invalid title" << endl;
                            if_continue2 = 0;
                        }

                        for (int i = 0; i < day_str.length(); i++) {
                            if (!isdigit(day_str[i])) {
                                cout << "Invalid day" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }    

                        for (int i = 0; i < hour_str.length(); i++) {
                            if (!isdigit(hour_str[i])) {
                                cout << "Invalid hour" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }

                        if(if_continue1) {
                            day = stoi(day_str);
                            hour = stoi(hour_str);

                            
                            if ((day < 1) || (day > 365)) {
                                cout << "Invalid day" << endl;
                                if_continue2 = 0;
                            }
                            if ((hour < 0) || (hour > 23)) {
                                cout << "Invalid hour" << endl;
                                if_continue2 = 0;
                            }
                                

                            // call ADD insert function 
                            if(if_continue2) {
                            Meeting meeting_to_insert = {title, day, hour};
                            ADD(meetings_tree, meeting_to_insert);
                            }
                        }
                    }
                }

                else if (command == "Find") {
                    if (arguments.size() != 3) {
                        cout << "Invalid arguments" << endl;
                    }
                    else {
                        day_str = arguments[1]; 
                        hour_str = arguments[2]; 

                        for (int i = 0; i < day_str.length(); i++) {
                            if (!isdigit(day_str[i])) {
                                cout << "Invalid day" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }    
            
                        for (int i = 0; i < hour_str.length(); i++) {
                            if (!isdigit(hour_str[i])) {
                                cout << "Invalid hour" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }

                        if(if_continue1) {
                            day = stoi(day_str);
                            hour = stoi(hour_str);
                
                            if ((day < 1) || (day > 365)) {
                                cout << "Invalid day" << endl;
                                if_continue2 = 0;
                            }
                            if ((hour < 0) || (hour > 23)) {
                                cout << "Invalid hour" << endl;
                                if_continue2 = 0;
                            }

                            // call Find function
                            if(if_continue2) {
                            Find(meetings_tree, day, hour);
                            }
                        }
                    }
                }

                else if (command == "MOD") {
                    if (arguments.size() != 4) {
                        cout << "Invalid arguments" << endl;
                    }
                    else {
                        title = arguments[1];
                        day_str = arguments[2]; 
                        hour_str = arguments[3]; 
                        
                        if (title[0] != '\"') {
                            cout << "Invalid title" << endl;
                            if_continue2 = 0; 
                        }

                        for (int i = 0; i < day_str.length(); i++) {
                            if (!isdigit(day_str[i])) {
                                cout << "Invalid day" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }    
            
                        for (int i = 0; i < hour_str.length(); i++) {
                            if (!isdigit(hour_str[i])) {
                                cout << "Invalid hour" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }

                        if(if_continue1) {
                            day = stoi(day_str);
                            hour = stoi(hour_str);

                            if ((day < 1) || (day > 365)) {
                                cout << "Invalid day" << endl;
                                if_continue2 = 0;
                            }
                            if ((hour < 0) || (hour > 23)) {
                                cout << "Invalid hour" << endl;
                                if_continue2 = 0;
                            }
                            if(if_continue2) {
                            // call MOD function
                            MOD(meetings_tree, title, day, hour);
                            }
                        }
                    }
                }

                else if (command == "DEL") {
                    if (arguments.size() != 3) {
                        cout << "Invalid arguments" << endl;
                    }
                    else {
                        day_str = arguments[1]; 
                        hour_str = arguments[2]; 

                        for (int i = 0; i < day_str.length(); i++) {
                            if (!isdigit(day_str[i])) {
                                cout << "Invalid day" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }    
            
                        for (int i = 0; i < hour_str.length(); i++) {
                            if (!isdigit(hour_str[i])) {
                                cout << "Invalid hour" << endl; 
                                if_continue1 = 0;
                                break;
                            }
                        }

                        if(if_continue1) {
                            day = stoi(day_str);
                            hour = stoi(hour_str);
                
                            if ((day < 1) || (day > 365)) {
                                cout << "Invalid day" << endl;
                                if_continue2 = 0;
                            }
                            if ((hour < 0) || (hour > 23)) {
                                cout << "Invalid hour" << endl;
                                if_continue2 = 0;
                            }

                            if(if_continue2) {
                            // call DEL function
                            DEL(meetings_tree, day, hour);
                            }
                        }
                    }
                }

                else if (command == "Print") {
                    if (arguments.size() != 1) {
                        cout << "Invalid arguments" << endl;
                    }
                    else {
                        // call inOrderTraverse function to print the mettings in ascending order
                        print(meetings_tree);

                    }
                }
                
                else {
                    cout << "Invalid command" << endl;
                }    
            }
            
        }
	    comamnds_file.close();
	}
    else {
        cout << "File not Found";
    }
    delete meetings_tree;
}
