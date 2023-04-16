#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;
    Node(int num) {
        data = num;
        left = NULL;
        right = NULL;
    }
};

int main() {
    char input[80];
    int rawinputs[80];
    bool cont = true;
    int total = 0;
    Node* head = NULL;
    while (cont == true) {
        cout << "Add, read, or print (add/read/print)?: ";
        cin >> input;
        cin.ignore();
        if (strcmp(input, "add") == 0) {

        }
        else if (strcmp(input, "read") == 0) {
            char file[80];
            cout << "Enter file name (Do not include .txt): ";
            cin >> file;
            cin.ignore();
            strcat(file, ".txt");
            ifstream numFile;
            numFile.open(file);
            cout << "Numbers from file: ";
            while (numFile >> rawinputs[total]) {
                Node* newnode = new Node(rawinputs[total]);
                insert(newnode, head);
                cout << rawinputs[total] << " ";
                total+=1;
            }
        }
        else if (strcmp(input, "print") == 0) {
            int numTabs = 0;
            print(head, numTabs);
        }
        else {
            cout << "Invalid input." << endl;
        }
    }

}

void insert() {

}

void print(Node* n, int numTabs) {
  if (n == NULL) {
    return;
  }  
  ++numTabs;
  print(n->right, numTabs);
  for (int i = 0; i < numTabs; ++i) {
    cout << "\t";
  }
  cout << n->data << endl;
  print(n->left, numTabs);
}