//============================================================================
// Name        : a2.cpp
// Author      : Abdulrahan Elsayed
// Version     : 03
// Copyright   : Your copyright notice
// Description : 
//============================================================================
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include "inord_list.h"

int char_num = 0;

bool s1_contain_s2_num (string s1, string s2) {
    s1 = " " + s1 + " ";
    s2 = " " + s2 + " ";
    return ((s1.find(s2) >= 0) && (s1.find(s2) < s1.length())); // if s1 contains s2
}

bool s1_contain_s2_str (string s1, string s2) {
    //s1 = "" + s1 + "";
    //s2 = "" + s2 + "";
    return ((s1.find(s2) >= 0) && (s1.find(s2) < s1.length())); // if s1 contains s2
}

void command_select(string &line, string args[]) { 
    // selecting the first argument if any
    int i = 0;
    //string arg1 = "";          
    while ((i < line.length()) && ((line[i] == ' ') || (line[i] == '\t'))) // escaping the left white spaces
        i++;
    while ((i < line.length()) && (line[i] != ' ') && (line[i] != '\t')) { // selecting the charachters
        args[0] += line[i];
        i++;
    }    

    line = line.substr(i, line.length()); 

    // selecting the second argument if any
    i = 0;
    //string arg2 = "";
    while ((i < line.length()) && ((line[i] == ' ') || (line[i] == '\t'))) // escaping the left white spaces
        i++; // white   asasas    
    while ((i < line.length()) && (line[i] != ' ') && (line[i] != '\t')) { // selecting the charachters
        args[1] += tolower(line[i]);
        i++;
    }  
    // if there a third argument, make a flag to report an error
    line = line.substr(i, line.length());
    i = 0;
    while (i < line.length()) {
        if (line[i] != ' ') {
            args[2] = "flag: third argument";
            break;
        }
        i++;
    }
}

void wordCount(inord_list &l) {
    unit result;
	bool flag;
    int count = 0;
	flag = l.first(result);

	while (flag) {
        count++;
		flag = l.next(result); 
	}
    cout << count << " words" << endl;
}

void distWords(inord_list &l) {
    unit result;
	bool flag;
    int count = 0;
    string word1 = "";
    string word2 = "";

	flag = l.first(result);
    word2 = result.word;

	while (flag) {
        if (word1 != word2) 
            count++;
        word1 = word2;
		flag = l.next(result); 
        word2 = result.word;
	}
    cout << count << " distinct words" << endl;
}

void charCount(inord_list &l) {
    if (char_num == 0) // empty file
        cout << 1 << " characters" << endl;
    else    
        cout << char_num << " characters" << endl;
}

void frequentWord(inord_list &l) {
    inord_list frequent;
    string word1, word2;
    int word_freq = 1;
    unit instance1;
    unit instance2;
	bool flag;
    int max = 0;
    inord_list l2 = l.list_copy();
    l2.remove("a");
    l2.remove("an");
    l2.remove("the");
    l2.remove("in");
    l2.remove("on");
    l2.remove("of");
    l2.remove("and");
    l2.remove("is");
    l2.remove("are");
	flag = l2.first(instance1);
	while (flag) {
        word1 = word2;
        word2 = instance1.word;
        //cout << word1 << " " << word2 << endl;
        if (word1 == word2) {
            word_freq++;
        } 
        else {
            if (word_freq == max) {
                instance2.word = word1;
                frequent.insert(instance2);
            }
            else if (word_freq > max) {
                frequent.remove_all();
                instance2.word = word1;
                frequent.insert(instance2);
                max = word_freq;
            }
            word_freq = 1;
        }
		flag = l2.next(instance1); 
    }
    if ((max == 1) || (word_freq == max)) {
        instance2.word = word2;
        frequent.insert(instance2);
    }
    if (word_freq > max) {
        frequent.remove_all();
        instance2.word = word2;
        frequent.insert(instance2);
    }
    if (l.is_empty()) 
        cout << "Word not found" << endl;
    else { //print the frequent 
        cout << "Most frequent word is:";
        flag = frequent.first(instance1);
        while (flag) { 
            cout << " " << instance1.word;
            flag = frequent.next(instance1); 
        }
        cout << endl;
    }    
}

void countWord(inord_list &l, string &s) {
    unit instance1;
	bool flag;
    int count = 0;
	flag = l.first(instance1);

	while (flag) {
        if (instance1.word == s)
            count++;
		flag = l.next(instance1); 
	}
    if (count == 0) 
        cout << "Word not found" << endl;
    else    
        cout << s << " is repeated " << count << " times" << endl;
}

void starting(inord_list &l, string &s) {
    int len = s.length();
    int count = 0;
    int i = 0;
    string tempWord1;
    unit instance1;
	bool flag;
    bool condition;
	flag = l.first(instance1);

	while (flag) {
        condition = instance1.word.substr(0, len) == s;
        if ((condition) && (instance1.word != tempWord1)) {
            if (i) {
                cout << count << "\t";
                count = 0;
            }
            i++;
            cout << instance1.word << ": ";
            count++;
            tempWord1 = instance1.word;
        }
        else if ((condition) && (instance1.word == tempWord1)) {
            count++;
            i++;
        }
		flag = l.next(instance1); 

    }    
    if (count == 0)
        cout << "Word not found" << endl;
    else    
        cout << count << endl;
}

void containing(inord_list &l, string &s) {
    int count = 0;
    int i = 0;
    string tempWord1;
    unit instance1;
	bool flag;
    bool condition;
	flag = l.first(instance1);

	while (flag) {
        condition = (instance1.word.find(s) >= 0) && (instance1.word.find(s) < instance1.word.length()); // if instance1.word contains s
        if ((condition) && (instance1.word != tempWord1)) { // and if instance1.word is first encountered
            if (i) { // ignore for first time
                cout << count << "\t";
                count = 0;
            }
            i++;
            cout << instance1.word << ": ";
            count++;
            tempWord1 = instance1.word;
        }
        else if ((condition) && (instance1.word == tempWord1)) { // and if instance1.word is previously encountered 
            count++;
            i++;
        }
		flag = l.next(instance1); 
            
	}
    if (count == 0)
        cout << "Word not found" << endl;
    else    
        cout << count << endl;
}

void search(inord_list &l, string &s) {
    int len = s.length();
    int i = 0;
    string word_prev, line_numbers, line_number, word;
    unit instance1;
	bool flag;
    bool condition;
	flag = l.first(instance1);

	while (flag) {
        line_number = to_string(instance1.lineNumber);
        word = instance1.word;
        if ((s1_contain_s2_str(word, s)) && (word != word_prev)) { // instance1.word contains s and if instance1.word is first encountered
            if (line_numbers != "") { // print the previous word
                for (int k = 0; k < line_numbers.length(); k++) {
                    cout << line_numbers[k]; 
                }
                cout << endl;
                i++;
            }
            line_numbers = ""; // new word and line numbers
            cout << word << ":\tlines ";
            if (!(s1_contain_s2_num(line_numbers, line_number))) {
                line_numbers = line_number.append(" ").append(line_numbers);                  
            }
            word_prev = word;
        }
        else if ((s1_contain_s2_str(word, s)) && (word == word_prev)) { // and if instance1.word is previously encountered 
            if (!(s1_contain_s2_num(line_numbers, line_number))) {
                line_numbers = line_number.append(" ").append(line_numbers);
            }
        }
		flag = l.next(instance1); 
	}
    if (line_numbers != "") { // print the previous word
        for (int k = 0; k < line_numbers.length(); k++) {
            cout << line_numbers[k]; 
        }
        cout << endl;
        i++;
    }      
    if (i == 0) 
        cout << "Word not found" << endl;
    
}

int main(int argc, char *argv[]) {
    
    if (argc != 3)
        cout << "Incorrect number of arguments" << endl;
    else {
        inord_list words_list;
	    string line; // to store the read line

        unit item; 

        ifstream words_file (argv[1]);
        int lineNumber = 0;
        int k;
        string word;
	    if (words_file.is_open()) {
	        while (getline(words_file,line)) {
                char_num++;
                lineNumber++;
                word = "";
                for (k = 0; k < line.length(); k++) { 
                    //if ((isalpha(line[k])) || (isdigit(line[k])) || (line[k] == '\'') || 
                    //((k - 1 >= 0) && (isalpha(line[k - 1])) && (line[k] == '-') && 
                    //(k + 1 < line.length()) && (isalpha(line[k + 1])))) {
                     
                    if ((line[k] != ',') && (line[k] != ';') && (line[k] != ':') &&
                    (line[k] != '\'') && (line[k] != '&') && (line[k] != '"') &&
                    (line[k] != '.') && (line[k] != '[') && (line[k] != ']') &&
                    (line[k] != '{') && (line[k] != '}') && (line[k] != '(') &&
                    (line[k] != ')') && (line[k] != '?') && (line[k] != '!') &&
                    (line[k] != ' ') && (line[k] != '\t')) { 
                        word += tolower(line[k]);
                    } 
                    
                    else if (word != "") {
                        item.word = word;
                        item.lineNumber = lineNumber;
                        words_list.insert(item);
                        word = "";        
                    }
                    if ((word != "") && (k == line.length() - 1)) {
                        item.word = word;
                        item.lineNumber = lineNumber;
                        words_list.insert(item);
                        word = "";  
                    }
                }
                char_num += k;
            }
	        words_file.close();
	    }
        else {
            cout << "File not found" << endl; 
            return 0;
        }   
        
        ifstream comamnds_file (argv[2]);
	    if (comamnds_file.is_open()) {
	        while (getline(comamnds_file,line)) {
                // selecting the comamnd
                string args[3];
                //cout << line << 0 << endl;
                command_select(line, args);
                string arg1 = args[0];
                string arg2 = args[1];
                string arg3 = args[2];
                //cout << line << 1 << endl;
                //cout << arg1 << 2 << endl;
                //cout << arg2 << 3 << endl;
                //cout << arg3 << 4 << endl;
                //if (arg3 != "") 
                //    cout << "Incorrect number of arguments" << endl; // or should be undefined command?

                if (arg1 == "wordCount") {
                    if (arg2 == "")
                        wordCount(words_list);
                    else
                        cout << "Incorrect number of arguments" << endl;
                    }
  
                else if (arg1 == "distWords") {
                    if (arg2 == "")
                        distWords(words_list);
                    else
                        cout << "Incorrect number of arguments" << endl;
                    }

                else if (arg1 == "charCount") {
                    if (arg2 == "")
                        charCount(words_list);
                    else
                        cout << "Incorrect number of arguments" << endl;                    
                }

                else if (arg1 == "frequentWord") {
                    if (arg2 == "")
                        frequentWord(words_list);
                    else
                        cout << "Incorrect number of arguments" << endl;                    
                }

                else if (arg1 == "countWord") {
                    if ((arg2 != "") && (arg3 == ""))
                        countWord(words_list, arg2);
                    else
                        cout << "Incorrect number of arguments" << endl;                    
                }
                    
                else if (arg1 == "starting") {
                    if ((arg2 != "") && (arg3 == ""))
                        starting(words_list, arg2);
                    else
                        cout << "Incorrect number of arguments" << endl;                    
                }

                else if (arg1 == "containing") {
                    if ((arg2 != "") && (arg3 == ""))
                        containing(words_list, arg2);
                    else
                        cout << "Incorrect number of arguments" << endl;                     
                }

                else if (arg1 == "search") {
                    if ((arg2 != "") && (arg3 == ""))
                        search(words_list, arg2);    
                    else
                        cout << "Incorrect number of arguments" << endl;                    
                }       

                else {
                    cout << "Undefined command" << endl;                           
                }     
                              
            }
	        comamnds_file.close();
	    }
        else {
            cout << "File not found";
            return 0;
        }
        /*
        unit result;
	    bool flag;
	    flag = words_list.first(result);
	    while (flag) {
            cout << result.word << "  " << result.lineNumber << endl;
	    	flag = words_list.next(result);
        }
        */
    }
} 
