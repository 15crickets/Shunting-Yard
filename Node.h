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
  char data;

  void setNext(Node* newnext);
  Node* getNext();
  void setInformation(char value);
  char getInformation();
 
};


#endif
