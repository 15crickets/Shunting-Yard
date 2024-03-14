#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

Node:: Node(){
  next = NULL;
}

Node :: ~Node(){
  next = NULL;
}

void Node :: setRight(Node* newRight){
  right = newRight;

}

void Node :: setLeft(Node* newLeft){
  left = newLeft;

}

void Node :: setNext(Node* newnext){
  next = newnext;
}

Node* Node:: getNext(){
  return next;
}

Node* Node :: getRight(){
  return right;
}

Node* Node :: getLeft(){
  return left;
}

void Node :: setInformation(char value){
  data = value;
}

char Node :: getInformation(){
  return data;

}
