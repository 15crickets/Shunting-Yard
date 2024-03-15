/*
  Author: Vikram Vasudevan
  Date: 3/14/24
  Description: This program prompts the user to enter a mathematical expression, and then outputs that expression in postfix notation
  using the shunting yard algorithm. It then asks the user if they would like the expression to be represented in infix, postfix, or prefix notation,
  and outputs the corresponding expression.

*/

#include <iostream>
#include <cstring>
#include "Node.h"
using namespace std;

//function prototypes
void push(Node* &stackHead, Node* newNode, Node* tempNode);
void pop(Node* &stackHead, Node* current, Node* prev);
char peek(Node* stackHead, Node* current, Node* prev);
Node* peekNew(Node* stackHead, Node* current, Node* prev);
void enqueue(Node* &queueHead, Node* newNode, Node* tempNode);
bool precedence(char one, char two);
void printQueue(Node* current);
Node* dequeue(Node* &queueHead);
void prefix(Node* root);
void infix(Node* root);
void postfix(Node* root);


//main
int main(){
  //prompting the user and collecting the response.
  cout << "Enter a mathematical expression: " << endl;
  char input [50];
  cin.get(input, 50);
  cin.get();
  //creating heads for the first stack and first queue.
  Node* stackHead = NULL;
  Node* queueHead = NULL;

  //looping through the user's input.
  for(int i = 0; i < strlen(input); i++){
    //if the input is a number, push it to the queue.
    if((int) input[i] < 58 && (int) input[i] > 47){
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      enqueue(queueHead, tempNode, queueHead);
    }
    //if it is an operator, push it to the stack, and potentially pop existing operators on the stack based on precedence/associativity.
    else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'|| input[i] == '^' ){
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      if(peek(stackHead, stackHead, stackHead) != 'a'){
        while(precedence(input[i], peek(stackHead, stackHead, stackHead)) == false && peek(stackHead, stackHead, stackHead) != 'a'){
          Node* temp = new Node();
          temp->setInformation(peek(stackHead, stackHead, stackHead));
          enqueue(queueHead, temp, queueHead);
          pop(stackHead, stackHead, stackHead);
        
        }
        
      }
      //pushing to stack.
      push(stackHead, tempNode, stackHead);

    }
    //if the input is a left parenthesis, push it to the stack.
    else if (input[i] == '('){
      Node* tempNode = new Node();
      tempNode->setInformation(input[i]);
      push(stackHead, tempNode, stackHead);
    }
    //if it is a right parenthesis, pop everything before the left parenthesis in the stack, and push it to the queue. 
    else if(input[i] == ')'){
      while(peek(stackHead, stackHead, stackHead) != '('){
        Node* newTemp = new Node();
        newTemp->setInformation(peek(stackHead, stackHead, stackHead));
        enqueue(queueHead, newTemp, queueHead);
        pop(stackHead, stackHead, stackHead);
      }
      //pop the left parenthesis
      pop(stackHead, stackHead, stackHead);

    }
    
  }
  //once the program has looped through the input fully, pop everything remaining in the stack, and push it to the queue.
  while(peek(stackHead, stackHead, stackHead) != 'a'){
    Node* temporary = new Node();
    temporary->setInformation(peek(stackHead, stackHead, stackHead));
    pop(stackHead, stackHead, stackHead);
    enqueue(queueHead, temporary, queueHead);
  }
  //print the queue, which is the postfix notation.
  printQueue(queueHead);

  //creating a new head for the next stack.
  Node* newStackHead = NULL;

  //forming the expression tree
  while(queueHead != NULL){
    //if the information in the queueHead is a number, push it to the stack
    if(isdigit(queueHead->getInformation())){
      push(newStackHead, dequeue(queueHead), newStackHead);
      
    }
    //if it is an operator, check the stack to see what are the current top two items in the stack.
    else{
      if(peek(newStackHead, newStackHead, newStackHead) != 'a'){
        //set the first item to the right node of the queueHead.
        queueHead->setRight(peekNew(newStackHead, newStackHead, newStackHead));
        pop(newStackHead, newStackHead, newStackHead);
        if(peek(newStackHead, newStackHead, newStackHead) != 'a'){
          //set the second item to the left node of the queueHead.
          queueHead->setLeft(peekNew(newStackHead, newStackHead, newStackHead));
          pop(newStackHead, newStackHead, newStackHead);	  
        }
      }
      //after deleting the top two items, push the queueHead to the stack, and dequeue it.
      push(newStackHead, dequeue(queueHead), newStackHead);
    }

  }

  bool stillAsking = true;
  while (stillAsking == true){
    //asking the user how they'd like the expression to be outputted.
    char choice[50];
    cout << "Would you like to express the answer in PREFIX, POSTFIX, or INFIX? Or would you like to QUIT " << endl;
    cin.get(choice, 50);
    cin.get();
    if(strcmp(choice, "PREFIX") == 0){
      prefix(newStackHead);

    }
    else if(strcmp(choice, "POSTFIX") == 0){
      postfix(newStackHead);

    }
    else if(strcmp(choice, "INFIX") == 0){
      infix(newStackHead);

    }
    else if(strcmp(choice, "QUIT") == 0){
      stillAsking = false;

    }


    
  }
}

//function that outputs the expression in prefix form: self, left, right.
void prefix(Node* root){
  cout << root->getInformation() << " ";
  if(root->getLeft() != NULL){
    prefix(root->getLeft());

  }
  if(root->getRight() != NULL){
    prefix(root->getRight());
  }

}

//function that outputs the expression in postfix form: left, right, self.
void postfix(Node* root){
  if(root->getLeft() != NULL){
    postfix(root->getLeft());
  }
  if(root->getRight() != NULL){
    postfix(root->getRight());
  }
  cout << root->getInformation() << " ";

}
//function that outputs the expression in infix form: left, self, right.
void infix(Node* root){
  if(root->getLeft() != NULL){
    infix(root->getLeft());
  }

  cout << root->getInformation() << " ";
  
  if(root->getRight() != NULL){
    infix(root->getRight());
  }
}

//the dequeue function, which removes the head of the queue, and sets the head to the next node.
Node* dequeue(Node* &queueHead){
  Node* tempNode = queueHead;
  queueHead = queueHead->getNext();
  tempNode->setNext(NULL);
  return tempNode;
}

//function that prints the information in the queue.
void printQueue(Node* current){
  while(current != NULL){
    cout << current->getInformation() << " ";
    current = current->getNext();
  }
  cout << endl;
}

//function that determines the precedence and associativity of each operator.
bool precedence(char one, char two){
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
  //if the precedence of the second character, which is the character at the top of the stack, is greater than that of the new input
  //char, or they have the same precedence but the character at the top of the stack is left associative, return false, and eventually pop
  //the character at the top of the stack. Otherwise, return true, and eventually add the new character to the stack as is.
  if(secPrec > firstPrec || (secPrec == firstPrec && secAssoc == -1)){
    return false;
  }
  else{
    return true;
  }

  
}

//function that adds nodes to the queue.
void enqueue(Node* &queueHead, Node* newNode, Node* tempNode){
  if(queueHead == NULL){
    queueHead = newNode;
  }
  else if(tempNode->getNext() == NULL){
    tempNode->setNext(newNode);

  }
  else{
    tempNode = tempNode->getNext();
    push(queueHead, newNode, tempNode);

  }

}


//function that takes the node at the end of the stack and removes it from the chain.
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
//function that adds nodes to the stack.
void push(Node* &stackHead, Node* newNode, Node* tempNode){
  if(stackHead == NULL){
    stackHead = newNode;
  }
  else if(tempNode->getNext() == NULL){
    tempNode->setNext(newNode);

  }
  else{
    tempNode = tempNode->getNext();
    push(stackHead, newNode, tempNode);


  }
}
//function that looks at and returns the top character in the stack.
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

//this function is essentially the same as peek, except it returns the node at the top of the stack, rather than the node's character.
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

