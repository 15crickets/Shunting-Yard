#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

void push(Node* &stackHead, Node* newNode, Node* tempNode);
void pop(Node* &stackHead, Node* current, Node* prev);
char peek(Node* stackHead, Node* current, Node* prev);

int main(){
  char input [50];
  cin.get(input, 50);
  Node* stackHead = NULL;
  Node* queueHead = NULL;

  //tests

  cout << "HI" << endl;
  Node* tempNode1 = new Node();
  Node* tempNode2 = new Node();
  Node* tempNode3 = new Node();

  tempNode1->setInformation('1');
  tempNode2->setInformation('2');
  tempNode3->setInformation('3');

  cout << "We're so back" << endl;
  Node* tempNode = new Node();
  push(stackHead, tempNode1, tempNode);
  
  push(stackHead, tempNode2, tempNode);
  cout << peek(stackHead, stackHead, stackHead) << endl;

}

void pop(Node* &stackHead, Node* current, Node* prev){
  if(stackHead == NULL){
    return;
  }

  if(current->getNext() == NULL){
    delete current;
    prev->setNext(NULL);
  }
  else{
    pop(stackHead, current->getNext(), current);

  }
}

void push(Node* &stackHead, Node* newNode, Node* tempNode){
  cout << newNode->getInformation() << endl;
  cout << "YOWAZGOODBAZBALLERS" << endl;
  if(stackHead == NULL){
    stackHead = newNode;
  }
  else if(tempNode->getNext() == NULL){
    cout << "version2" << endl;
    cout << newNode->getInformation() << endl;
    tempNode->setNext(newNode);

  }
  else{
    cout << "RECURSION TIME" << endl;
    tempNode = tempNode->getNext();
    push(stackHead, newNode, tempNode);


  }
}

char peek(Node* stackHead, Node* current, Node* prev){
  if(stackHead == NULL){
    return 'a';
  }
  else{
    if(current->getNext() == NULL){
      return current->getInformation();
    }
    else{
      peek(stackHead, current->getNext(), current);
    }
  }
  return 'b';

}


