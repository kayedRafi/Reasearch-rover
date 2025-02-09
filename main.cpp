#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>  
#include <sstream>    

using namespace std;

struct Node {
    int key;
    string value;
    Node* next;
};

class Problems {
public:
    string differentProblems();
};

class Solutions : public Problems {
private:
    vector<vector<int>> filter_search; // Vector of vectors to store search results

public:
    Solutions() : filter_search(10) {} // Initialize the vector with 10 elements

    long Life_solution(const string& wordSearch, int pushKey);
    void subSearch(int subSearchArray, int noOfWords, const string& searchedString);

    Node* problemList = nullptr; // Linked list to store problem statements
    int problemCount = 0;

    void appendProblem(const string& problemStatement) {
        Node* newNode = new Node;
        newNode->key = ++problemCount;
        newNode->value = problemStatement;
        newNode->next = nullptr;

        if (!problemList) {
            problemList = newNode;
        } else {
            Node* current = problemList;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }
};

long Solutions::Life_solution(const string& wordSearch, int pushKey) {
    long sub_search_count = 0;
    string line;

    ifstream getFile("Generic_Problem.txt");

    if (getFile.is_open()) {
        while (getline(getFile, line)) {
            appendProblem(line);
        }

        Node* current = problemList;

        while (current) {
            if (current->value.find(wordSearch) != string::npos) {
                filter_search[pushKey].push_back(current->key);
            }
            current = current->next;
        }

        if (filter_search[pushKey].empty()) {
            cout << "NO matches found " << endl;
        } else {
            sub_search_count = filter_search[pushKey].size();
            cout << wordSearch << " count is " << sub_search_count << endl;
        }

        getFile.close(); // Close the file
    }
    return sub_search_count;
}

void Solutions::subSearch(int subSearchArray, int noOfWords, const string& searchedString) {
    int freq[100];

    if (subSearchArray <= noOfWords && noOfWords > 0) {
        for (int i = 0; i < 10; i++) {
            if (!filter_search[i].empty()) {
                for (int j = 1; j < 10; j++) {
                    filter_search[0].insert(filter_search[0].end(), filter_search[j].begin(), filter_search[j].end());
                    filter_search[j].erase(filter_search[j].begin(), filter_search[j].end());
                    freq[j - 1] = -1;
                }
            }
        }

        sort(filter_search[0].begin(), filter_search[0].end());
        for (int q = 0; q < filter_search[0].size(); q++) {
            int count = 1;
            for (int p = q + 1; p < filter_search[0].size(); p++) {
                if (filter_search[0][q] == filter_search[0][p]) {
                    count++;
                    freq[p] = 0;
                }
            }
            if (freq[q] != 0) {
                freq[q] = count;
            }
        }
        for (int w = 0; w < filter_search[0].size(); w++) {
            if (freq[w] != 0) {
                cout << filter_search[0][w] << " " << freq[w] << endl;
            }
        }
        int max_freq = filter_search[0].size();
        int max_elements = max_element(freq, freq + max_freq) - freq;
        Node* current = problemList;
        while (current) {
            if (current->key == filter_search[0][max_elements]) {
                cout << current->value << endl;
                break;
            }
            current = current->next;
        }
    } else {
        cout << "Unable to find the solution" << endl;
        cout << "But We will add your question to our priority list of questions" << endl;
        ofstream out("Generic_Problem.txt", ios::app);
        string str = searchedString;
        out << endl;
        out << problemCount + 2 << "." << str;
        out.close(); // Close the file
    }
}
string Problems::differentProblems() {
    string anythingSpecificProblem;
    cout << "Please Enter your Search: ";
    getline(cin, anythingSpecificProblem);
    return anythingSpecificProblem;
}

int main() {
    string questionSearched;
    Solutions solution;

    questionSearched = Problems().differentProblems();
    string arr[20];
    int i = 0;
    int q = 0;
    int wordPresent = 0;

    istringstream iss(questionSearched);
    while (iss >> arr[i] && i < 20) {
        ++i;
    }

    int noOfwords = i;

    for (int x = 0; x < 20; x++) {
        if (arr[x].empty()) {
            break;
        } else {
            q += 1;
            long wordFound = solution.Life_solution(arr[x], q - 1);
            if (wordFound > 0) {
                ++wordPresent;
            } else {
                cout << arr[x] << " word is not found" << endl;
            }
        }
    }

    solution.subSearch(wordPresent, noOfwords, questionSearched);
}
