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

void Node :: setNext(Node* newnext){
  next = newnext;
}

Node* Node:: getNext(){
  return next;
}

void Node :: setInformation(char value){
  data = value;
}

char Node :: getInformation(){
  return data;

}