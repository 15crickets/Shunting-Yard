#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;


class Node{
 public:
  Node();
  ~Node();
  Node* next;
  Node* left;
  Node* right;
  char data;

  void setRight(Node* newRight);
  void setLeft(Node* newLeft);
  Node* getRight();
  Node* getLeft();
  void setNext(Node* newnext);
  Node* getNext();
  void setInformation(char value);
  char getInformation();
 
};


#endif
