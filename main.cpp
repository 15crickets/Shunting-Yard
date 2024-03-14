#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

void push(Node* &stackHead, Node* newNode, Node* tempNode);
void pop(Node* &stackHead, Node* current, Node* prev);
char peek(Node* stackHead, Node* current, Node* prev);
Node* peekNew(Node* stackHead, Node* current, Node* prev);
void enqueue(Node* &queueHead, Node* newNode, Node* tempNode);
bool precedence(char one, char two);
void printQueue(Node* current);
Node* dequeue(Node* &queueHead);


int main(){
  char input [50];
  cin.get(input, 50);
  cin.get();
  Node* stackHead = NULL;
  Node* queueHead = NULL;

  /*
  Node* tempNode1 = new Node();
  Node* tempNode2 = new Node();
  Node* tempNode3 = new Node();

  tempNode1->setInformation('1');
  tempNode2->setInformation('2');
  tempNode3->setInformation('3');

  cout << "We're so back" << endl;
  push(stackHead, tempNode1, stackHead);
  pop(stackHead, stackHead, stackHead);
  cout << peek(stackHead, stackHead, stackHead) << endl;



  push(stackHead, tempNode2, stackHead);
  push(stackHead, tempNode3, stackHead);
  pop(stackHead, stackHead, stackHead);
  cout << peek(stackHead, stackHead, stackHead) << endl;

  pop(stackHead, stackHead, stackHead);
  cout << peek(stackHead, stackHead, stackHead) << endl;
 */ 
  
  
  for(int i = 0; i < strlen(input); i++){
    if((int) input[i] < 58 && (int) input[i] > 47){
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      cout << input[i] << endl;
      cout << "ENQUEUE1" << tempNode->getInformation() << endl;
      cout << "I: " << i << endl;
      enqueue(queueHead, tempNode, queueHead);
    }
    
    else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'|| input[i] == '^' ){
      cout << "WE GETTING IN HERE? " << endl;
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      if(peek(stackHead, stackHead, stackHead) != 'a'){
        cout << "HERE? " << endl;
        while(precedence(input[i], peek(stackHead, stackHead, stackHead)) == false && peek(stackHead, stackHead, stackHead) != 'a'){
	  cout << "INPUT: " << input[i] << endl;
          Node* temp = new Node();
          temp->setInformation(peek(stackHead, stackHead, stackHead));
          cout << "ENQUEUE2" << temp->getInformation() << endl;
          enqueue(queueHead, temp, queueHead);
          cout << stackHead->getInformation() << endl;
          pop(stackHead, stackHead, stackHead);
          
          //cout << peek(stackHead, stackHead, stackHead) << endl;
          cout << "Reached end" << endl;
        }
        
      }
      cout << "WE RUNNING THIS?" << endl;
      push(stackHead, tempNode, stackHead);

    }
    else if (input[i] == '('){
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      push(stackHead, tempNode, stackHead);
    }
    else if(input[i] == ')'){
      while(peek(stackHead, stackHead, stackHead) != '('){
	Node* newTemp = new Node();
	newTemp->setInformation(peek(stackHead, stackHead, stackHead));
	enqueue(queueHead, newTemp, queueHead);
	pop(stackHead, stackHead, stackHead);
      }
      pop(stackHead, stackHead, stackHead);

    }
    
  }
  cout << "HI" << endl;
  while(peek(stackHead, stackHead, stackHead) != 'a'){
    cout << "WHOOPEDY DOO" << endl;
    Node* temporary = new Node();
    temporary->setInformation(peek(stackHead, stackHead, stackHead));
    cout << peek(stackHead, stackHead, stackHead) << endl;
    pop(stackHead, stackHead, stackHead);
    cout << "ENQUEUE3" << temporary->getInformation() << endl;
    enqueue(queueHead, temporary, queueHead);
  }

  printQueue(queueHead);

  Node* newStackHead = NULL;

  while(queueHead != NULL){
    cout << "runwhile" << endl;
    if(isdigit(queueHead->getInformation())){
      cout << "IN HERE" << endl;
      push(newStackHead, dequeue(queueHead), newStackHead);
      
    }
    else{
      cout << "MAKING IT IN " << endl;
      cout << peek(newStackHead, newStackHead, newStackHead) << endl;
      if(peek(newStackHead, newStackHead, newStackHead) != 'a'){
	queueHead->setRight(peekNew(newStackHead, newStackHead, newStackHead));
	pop(newStackHead, newStackHead, newStackHead);
	if(peek(newStackHead, newStackHead, newStackHead) != 'a'){
	  queueHead->setLeft(peekNew(newStackHead, newStackHead, newStackHead));
	  pop(newStackHead, newStackHead, newStackHead);
	  
	}
      }
      cout << "VIBING HERE? " << endl;
      push(newStackHead, dequeue(queueHead), newStackHead);
    }

  }
  cout << "FINAL WHAT WE GOT" << endl;
  cout << newStackHead->getInformation() << endl;
  cout << newStackHead->getLeft()->getInformation() << endl;
  cout << newStackHead->getRight()->getInformation() << endl;
  cout << newStackHead->getLeft()->getRight()->getInformation() << endl;
  cout << newStackHead->getLeft()->getLeft()->getInformation() << endl;
  cout << newStackHead->getLeft()->getLeft()->getLeft()->getInformation() << endl;
}


Node* dequeue(Node* &queueHead){
  Node* tempNode = queueHead;
  queueHead = queueHead->getNext();
  tempNode->setNext(NULL);
  return tempNode;
}


void printQueue(Node* current){
  while(current != NULL){
    cout << current->getInformation() << " ";
    current = current->getNext();
  }
  cout << endl;
}


bool precedence(char one, char two){
  cout << "YO WASSUP GOOD GAMERS" << endl;
  int firstPrec = 0;
  int firstAssoc = -2;
  int secAssoc = -2;
  int secPrec = 0;
  if( one == '+' ||  one == '-'){
    firstPrec = 2;
    firstAssoc = -1;
  }
  else if(one == '*' || one == '/'){
    firstPrec = 3;
    firstAssoc = -1;
  }
  else if(one == '^'){
    firstPrec = 4;
    firstAssoc = 1;
  }
  if(two == '+' ||  two == '-'){
    secPrec = 2;
    secAssoc = -1;
  }
  else if(two == '*' || two == '/'){
    secPrec = 3;
    secAssoc = -1;
  }
  else if(two == '^'){
    secPrec = 4;
    secAssoc = 1;
  }

  if(secPrec > firstPrec || (secPrec == firstPrec && secAssoc == -1)){
    cout << "SECPREC" << two << secPrec << endl;
    cout << "FIRSTPREC" << one << firstPrec << endl;
    return false;
  }
  else{
    return true;
  }

  
}

void enqueue(Node* &queueHead, Node* newNode, Node* tempNode){
  //cout << "NEWINFORMATION: " << newNode->getInformation() << endl;
  if(queueHead == NULL){
    queueHead = newNode;
  }
  else if(tempNode->getNext() == NULL){
    //cout << "version2" << endl;
    //cout << newNode->getInformation() << endl;
    tempNode->setNext(newNode);

  }
  else{
    //cout << "RECURSION TIME" << endl;
    tempNode = tempNode->getNext();
    push(queueHead, newNode, tempNode);


  }

}



void pop(Node* &stackHead, Node* current, Node* prev){
  if(stackHead == NULL){
    return;
  }
  else if(stackHead->getNext() == NULL){
    stackHead = NULL;
  }
  else if(current->getNext() == NULL){
    prev->setNext(NULL);
  }
  else{
    pop(stackHead, current->getNext(), current);

  }
}

void push(Node* &stackHead, Node* newNode, Node* tempNode){
  //cout << newNode->getInformation() << endl;
  //cout << "Tests" << endl;
  if(stackHead == NULL){
    stackHead = newNode;
  }
  else if(tempNode->getNext() == NULL){
    //cout << "version2" << endl;
    //cout << newNode->getInformation() << endl;
    tempNode->setNext(newNode);

  }
  else{
    //cout << "RECURSION TIME" << endl;
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
      return peek(stackHead, current->getNext(), current);
    }
  }
  return 'b';

}

Node* peekNew(Node* stackHead, Node* current, Node* prev){
  if(stackHead == NULL){
    return NULL;
  }
  else{
    if(current->getNext() == NULL){
      return current;
    }
    else{

      return peekNew(stackHead, current->getNext(), current);
    }


  }
  return NULL;


}

