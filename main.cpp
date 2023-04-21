#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
using namespace std;

class Node {
    public:
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int type;
    Node(int num) {
        data = num;
        parent = NULL;
        left = NULL;
        right = NULL;
        type = 1;//red is 1, black is 2
    }
};

void insert(Node* &newnode, Node* &head);
//void insert-fix(Node* &newnode, Node* &head)
void print(Node* head, int numTabs);

int main() {
    cout << 1/5;
    char input[80];
    int rawinputs[80];
    bool cont = true;
    int total = 0;
    int num = 0;
    Node* head = NULL;
    while (cont == true) {
        cout << "Add, read, or print (add/read/print)?: ";
        cin >> input;
        cin.ignore();
        if (strcmp(input, "add") == 0) {
            while(num != -1) {
                cout << "Enter number, enter -1 to quit adding: ";
                 cin >> num;
                if (num == -1) {
                    break;
                }
            Node* newnode = new Node(num);
            insert(newnode, head);
        }
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
                //insert(newnode, head);
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

void insert(Node* &newnode, Node* &head) {
    if (head == NULL) {//if there is nothing in the tree
        head = newnode;
        head->type = 2;
    }
    else {
        Node* n = head;
        while((n->left != NULL) || (n->right != NULL)) {
            if (newnode->data > n->data) {
                n = n->right;
            }
            else {
                n = n->left;
            }
            cout << n->data << endl;
        }
        cout << n->data << endl;
        newnode->parent = n;
        if (n->data > newnode->data) {
            n->left = newnode;
        }
        else {
            n->right = newnode;
        }
        newnode->type = 1;
        //insert_fix();
    }
    int numTabs = 0;
    print(head, numTabs);
}

void insert_fix() {

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