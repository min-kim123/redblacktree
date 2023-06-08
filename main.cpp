#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
using namespace std;
/*
Author: Min Kim
Program Description: This is a red black tree. It is a self-balancing tree. Black nodes are denoted by parentheses around that number. Help from https://www.programiz.com/dsa/red-black-tree
Date: 5/9/23
*/

class Node {
    public:
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int type;
};

class RedBlackTree {//need to put functions inside here to have access to TNULL
   public:
  Node* head;
  Node* TNULL;

  void deleteFix(Node* x) {//fix colors after deleting the node
    cout << "deletefix" << endl;
    Node* s;
    cout << x->data << endl;
    while (x != head && x->type == 2) {
        cout << "while" << endl;
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->type == 1) {
          s->type = 2;
          x->parent->type = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->type == 2 && s->right->type == 2) {
          s->type = 1;
          x = x->parent;
        } 
        else {
          if (s->right->type == 2) {
            s->left->type = 2;
            s->type = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->type = x->parent->type;
          x->parent->type = 2;
          s->right->type = 2;
          leftRotate(x->parent);
          x = head;
        }
      } 
      else {
        s = x->parent->left;
        if (s->type == 1) {
          s->type = 2;
          x->parent->type = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->type == 2 && s->right->type == 2) {
          s->type = 1;
          x = x->parent;
        } 
        else {
          if (s->left->type == 2) {
            s->right->type = 2;
            s->type = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->type = x->parent->type;
          x->parent->type = 2;
          s->left->type = 2;
          rightRotate(x->parent);
          x = head;
        }
      }
    }
    x->type = 2;
  }

  void replace(Node* u, Node* v) {
    if (u->parent == NULL) {
      head = v;
    } 
    else if (u == u->parent->left) {
      u->parent->left = v;
    } 
    else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(Node* node, int key) {
    cout << "deletenodehelper" << endl;
    Node* z = TNULL;
    Node* x;
    Node* y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } 
      else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Number does not exist" << endl;
      return;
    }

    y = z;
    int y_original_color = y->type;
    if (z->left == TNULL) {//if node only has right branch
      x = z->right;
      //for all of these cases replace whatever node with the deleted node's right child
      replace(z, z->right);
    } 
    else if (z->right == TNULL) {//if node only has left branch
      x = z->left;
      replace(z, z->left);
    } 
    else {//if node_delete has 2 children
      y = minimum(z->right);
      y_original_color = y->type;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } 
      else {
        replace(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      replace(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->type = z->type;
    }
    delete z;
    if (y_original_color == 2) {
      deleteFix(x);
    }
  }

  void insertFix(Node* k) {
    Node* u;
    while (k->parent->type == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->type == 1) {
          u->type = 2;
          k->parent->type = 2;
          k->parent->parent->type = 1;
          k = k->parent->parent;
        } 
        else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->type = 2;
          k->parent->parent->type = 1;
          leftRotate(k->parent->parent);
        }
      } 
      else {
        u = k->parent->parent->right;

        if (u->type == 1) {
          u->type = 2;
          k->parent->type = 2;
          k->parent->parent->type = 1;
          k = k->parent->parent;
        } 
        else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->type = 2;
          k->parent->parent->type = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == head) {
        break;
      }
    }
    head->type = 2;
  }

  void searchTree (Node* n, int searchnum) {
  if (n->data == searchnum) {
    cout << "Number exists." << endl;
    return;
  }
  else if (n->data > searchnum && n->left != NULL) {
    searchTree(n->left, searchnum);
  }
  else if (n->data < searchnum && n->right != NULL) {
    searchTree(n->right, searchnum);
  }
  else if (n->left == NULL || n->right == NULL) {//number doesn't exist
    cout << "Number doesn't exist." << endl;
    return;
  }
}

  void search() {
    int num = 0;
    cout << "Number: ";
    cin >> num;
    if (head) {
        searchTree(this->head, num);
        }
  }


    void printTree() {
        if (head) {
        print(this->head, 2);
        }
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

  RedBlackTree() {
    TNULL = new Node;
    TNULL->type = 2;
    TNULL->left = NULL;
    TNULL->right = NULL;
    head = TNULL;
  }

  Node* minimum(Node* node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  void leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      this->head = y;
    } 
    else if (x == x->parent->left) {
      x->parent->left = y;
    } 
    else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
      this->head = y;
    } 
    else if (x == x->parent->right) {
      x->parent->right = y;
    } 
    else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void insert(int key) {
    Node* node = new Node;
    node->parent = NULL;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->type = 1;

    Node* y = NULL;
    Node* x = this->head;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } 
      else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == NULL) {
      head = node;
    } 
    else if (node->data < y->data) {
      y->left = node;
    } 
    else {
      y->right = node;
    }

    if (node->parent == NULL) {
      node->type = 2;
      return;
    }

    if (node->parent->parent == NULL) {
      return;
    }

    insertFix(node);
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->head, data);
  }

  
};

int main() {
  RedBlackTree tree;

  bool cont = true;
  int rawinputs[80];
  int total = 0;
  int num = 0;
  char input[80];
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
                tree.insert(num);
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
                tree.insert(rawinputs[total]);
                total+=1;
            }
        }
        else if (strcmp(input, "print") == 0) {
            int numTabs = 0;
            tree.printTree();
        }
        else if (strcmp(input, "delete")==0) {
            int num = 0;
            cout << "Number to delete: ";
            cin >> num;
            tree.deleteNode(num);
        }
        else if (strcmp(input, "search") == 0) {
            tree.search();

        }
        else if (strcmp(input, "quit") == 0) {
            cont = false;
        }
        else {
            cout << "Invalid input." << endl;
        }
      }
}