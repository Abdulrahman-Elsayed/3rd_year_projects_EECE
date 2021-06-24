#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc > 1) {
        string command {string(argv[1])};

        if(command == "print") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            for(int i = 2; i < argc; i++) {
                cout << argv[i] << " ";
            }
        }
        else if(command == "reverse") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            for(int i = argc - 1; i > 1; i--) {
                cout << argv[i] << " ";
            }
        }
        else if(command == "upper") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            for(int i = 2; i < argc; i++) {
                string word = string(argv[i]);
                int word_length = word.length();
                for(int j = 0; j < word_length; j++) {
                    cout << (char) toupper(word[j]);
                }
                cout << " ";

            }
        }
        else if(command == "shuffle") {
            if (argc != 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            string word = string(argv[2]);
            int word_length = word.length();
            int iterations = word_length / 2;
            int i {0};
            for(; i < iterations; i++) {
                cout << word[i * 2 + 1] << word[i * 2];
            }
            if((word_length % 2) != 0) {
                cout << word[i * 2];
            }
        }
        else if(command == "shuffleStatement") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            int iterations = argc / 2;
            int i {1};
            for(; i < iterations; i++) {
                cout << argv[i * 2 + 1] << " " << argv[i * 2] << " ";
            }
            if((argc % 2) != 0) {
                cout << argv[i * 2];
            }
        }

        else if(command == "delete") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            int to_delete {atoi(argv[2])};
            if (to_delete <= 0) {
                cout << "Incorrect Data Type" << endl;
                return 0;
            }
            if ((argc - 2) < to_delete) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }

            for(int i = 3; i < argc; i++) {
                if ((i - 2) != to_delete) {
                    cout << argv[i] << " "; 
                }
            }
        }
        
        else if(command == "middle") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            int mid {((argc - 2) / 2)};
            if ((argc % 2) == 0) {
                cout << argv[mid - 1 + 2] << " " << argv[mid + 2] << endl;
            }
            else {
                mid += 1;
                cout << argv[mid - 1 + 2] << endl;
            }
        }
        else if(command == "add") {
            if (argc < 3) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            int sum {0};     
            for (int i {2}; i < argc; i++) {
                int num {atoi(argv[i])};
                string sum_str {to_string(num)};
                string argvi_str {argv[i]};
                if (argvi_str != sum_str) {
                    cout << "Incorrect Data Type" << endl;
                    return 0;
                }
                sum += num;
            }
            cout << sum << endl;
        }
        
        else if(command == "random") {
            if (argc != 6) {
                cout << "Incorrect Number of Arguments" << endl;
                return 0;
            }
            for (int i {2}; i < argc; i++) {
                int num {atoi(argv[i])};
                string sum_str {to_string(num)};
                string argvi_str {argv[i]};
                if (argvi_str != sum_str) {
                    cout << "Incorrect Data Type" << endl;
                    return 0;
                }
            }
            int sequence_length {atoi(argv[2])};
            int min_number {atoi(argv[3])};
            int max_number {atoi(argv[4])};
            int seed_value {atoi(argv[5])};
            if ((sequence_length <= 0) || (min_number > max_number)) {
                cout << "Incorrect Data Type" << endl;
                    return 0;
            }

            srand(seed_value);
            for(int i {0}; i < sequence_length; i++) {
                cout << rand() % (max_number - min_number + 1) + min_number << " ";
            }
        }
        else {
            cout << "Undefined Command";
        }
    } 
    else {
        cout << "Not enough arguments" << endl;
    }
}  