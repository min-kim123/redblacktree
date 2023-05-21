#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
using namespace std;
/*
Author: Min Kim
Program Description: This is a red black tree. It is a self-balancing tree. Black nodes are denoted by parentheses around that number. 
Date: 5/9/23
*/

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
void print(Node* head, int numTabs);
void left_rotate(Node* &head, Node* &k);
void right_rotate(Node* &head, Node* &k);
void deleet(int num, Node* &head);
void search (Node* n, int searchnum);

int main() {
    cout << 1/5;
    char input[80];
    int rawinputs[80];
    bool cont = true;
    int total = 0;
    int num = 0;
    Node* head = NULL;
    while (cont == true) {
        cout << "Add, read, print, or quit (add/read/delete/search/print/quit)?: ";
        cin >> input;
        cin.ignore();
        if (strcmp(input, "add") == 0) {
            while(num != -1) {
                cout << "Enter number, enter -1 to quit adding: ";
                 cin >> num;
                if (num == -1) {
                    num = 0;
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
            while (numFile >> rawinputs[total]) {
                Node* newnode = new Node(rawinputs[total]);
                insert(newnode, head);
                total+=1;
            }
        }
        else if (strcmp(input, "print") == 0) {
            int numTabs = 0;
            print(head, numTabs);
        }
        else if (strcmp(input, "delete")==0) {
            int num = 0;
            cout << "Number to delete: ";
            cin >> num;
            deleet(num, head);
        }
        else if (strcmp(input, "search") == 0) {
            int searchnum = 0;
            cout << "Number: ";
            cin >> searchnum;
            search(head, searchnum);

        }
        else if (strcmp(input, "quit") == 0) {
            cont = false;
        }
        else {
            cout << "Invalid input." << endl;
        }
    }
}

void insert(Node* &k, Node* &head) {
    //inserting normally into the tree with no rotations
    if (head == NULL) {//if there is nothing in the tree
        head = k;
        head->type = 2;//set it black
    }
    else {
        Node* n = head;
        while((n != NULL) && ((n->left != NULL) || (n->right != NULL))) {//traverse until finding null node
            if (k->data > n->data) {
                if (n->right == NULL) {
                    break;
                }
                n = n->right;
            }
            else if (k->data <= n->data) {
                if (n->left == NULL) {
                    break;
                }
                n = n->left;
            }
            if (n == NULL) {
                cout << "n is null " << endl;
            }
        }
        k->parent = n;//newnode's parent is n
        if (n->data >= k->data) {
            n->left = k;//n's left is newnode
        }
        else {
            n->right = k;//n's right is newnode
        }
    }
    //restoring through rotations/recolors
    while ((k != head) && (k->parent->type == 1)) {//if parent of k is red; don't need to change anything if it's black
        if (k->parent == k->parent->parent->left) {//if k's parent is a left node
            Node* newnodeRightUncle =  k->parent->parent->right;
            if ((newnodeRightUncle != NULL) && (newnodeRightUncle->type == 1)) {//if right uncle is red
                k->parent->type = 2;
                newnodeRightUncle->type = 2;
                k->parent->parent->type = 1;
                k = k->parent->parent;//k becomes the grandparent that has just become red
            }
            else {//if right uncle is black or null
                if (k == k->parent->right) {//if k is right, double rotation
                    k = k->parent;
                    //LEFT ROTATE
                    left_rotate(head, k);
                }
                //else single rotation
                k->parent->type = 2;
                k->parent->parent->type = 1;
                k = k->parent->parent;
                //right rotate
                right_rotate(head, k);
            }
        }
        else {//if k's parent is a right node
            Node* newnodeLeftUncle =  k->parent->parent->left;
            if ((newnodeLeftUncle != NULL) && (newnodeLeftUncle->type == 1)) {
                k->parent->type = 2;
                newnodeLeftUncle->type = 2;
                k->parent->parent->type = 1;
                k = k->parent->parent;//k becomes the grandparent that has just become red
                
            }
            else {//if left uncle is black or null
                if (k == k->parent->left) {//if k is ;eft, double rotation
                    k = k->parent;
                    //RIGHT ROTATE
                    right_rotate(head, k);
                }
                //else single rotation
                k->parent->type = 2;
                k->parent->parent->type = 1;
                k = k->parent->parent;//k is now the grandparent
                //LEFT rotate
                left_rotate(head, k);
            }
        }
    }
    head->type = 2;//make head black
    print(head, 0);
    cout << "--------------------------" << endl;
}

void left_rotate(Node* &head, Node* &k) {
    Node* y = k->right;//y is the newly inserted node
    k->right = y->left;
    if (y->left != NULL) {
        y->left->parent = k;
    }
    y->parent = k->parent;
    if (k->parent == NULL) {
        head = y;
    }
    else {
        if (k == k->parent->left) {
            k->parent->left = y;
        }
        else {
            k->parent->right = y;
        }
    }
    y->left = k;
    k->parent = y;
}

void right_rotate(Node* &head, Node* &k) {
    Node* y = k->left;//y is the newly inserted node
    k->left = y->right;
    if (y->right != NULL) {
        y->right->parent = k;
    }
    y->parent = k->parent;
    if (k->parent == NULL) {
        head = y;
    }
    else {
        if (k == k->parent->right) {
            k->parent->right = y;
        }
        else {
            k->parent->left = y;
        }
    }
    y->right = k;
    k->parent = y;
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
  if (n->type == 1) {
    cout << n->data << endl;
  }
  else {
    cout << "(" << n->data << ")" << endl;
  }
  print(n->left, numTabs);
}

void deleet(int num, Node* &head) {//regular BST deletion
    Node* n = head;
    Node* node_delete = NULL;
    while (n != NULL) {
        if (n->data == num) {
            node_delete = n;
            break;
        }
        else if (n->data > num) {
            n = n->right;
        }
        else if (n->data < num) {
            n = n->right;
        }
    }
    if (node_delete == NULL) {
        cout << "Number does not exist" << endl;
        return;
    }
    Node* y = node_delete;
    Node* node_replacer;
    int color = node_delete->color;
    //TRANSPLANT
    if (node_delete->left == NULL) {//if node only has right branch
        node_replacer = node_delete->right;
        //for all of these cases replace whatever node with the deleted node's right child
        if (node_delete->parent == NULL) {//if node_delete is head
            head = node_replacer;
        }
        else if (node_delete== node_delete->parent->left) {//if node being deleted is a left node
            node_delete->parent->left = node_replacer;
        }
        else {
            node_delete->parent->right = node_replacer;
        }
        node_delete->right->parent = node_replacer;
    }
    else if (node_delete->right == NULL) {//if node only has left branch
        node_replacer = node_delete->left;
        if (node_delete->parent == NULL) {//if node_delete is head
            head = node_replacer;
        }
        else if (node_delete== node_delete->parent->left) {//if node being deleted is a left node
            node_delete->parent->left = node_replacer;
        }
        else {
            node_delete->parent->right = node_replacer;
        }
        node_delete->right->parent = node_replacer;
    }
    else {//if node_delete has 2 children
        y = node_delete->right
        while(y->left != NULL) {
            y = y->left;
        }
        color = y->color;
        node_replace = y->right;
        if (y->parent = node_delete) {
            node_replace->parent = y;
        }
    }
    delete node_delete;
    if (color == 1) {//if deleted node's color was black

    }

}

void search (Node* n, int searchnum) {
  if (n->data == searchnum) {
    cout << "Number exists." << endl;
    return;
  }
  else if (n->data > searchnum && n->left != NULL) {
    search(n->left, searchnum);
  }
  else if (n->data < searchnum && n->right != NULL) {
    search(n->right, searchnum);
  }
  else if (n->left == NULL || n->right == NULL) {//number doesn't exist
    cout << "Number doesn't exist." << endl;
    return;
  }
}