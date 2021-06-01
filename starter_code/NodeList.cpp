#include "NodeList.h"
#include <iostream>

#define INITIAL_LENGTH 0


NodeList::NodeList(){
  // TODO
  // construct nodelist
  this->length = INITIAL_LENGTH;
  nodes = new Node* [NODE_LIST_ARRAY_MAX_SIZE];
}

NodeList::~NodeList(){
  // TODO
  // deconstruct nodelist
  for (int i = 0; i < length; i++) {
      delete this->nodes[i];
  }
  delete nodes;
}

// DEEP COPY
NodeList::NodeList(NodeList& other) :
  length(other.length)
{   
  // TODO
  this->nodes = new Node*[NODE_LIST_ARRAY_MAX_SIZE];

  // copy all elements from other node
  for (int i = 0; i < other.getLength(); ++i) {
    Node* node = other.getNode(i);
    Node* copyNode = new Node(*node);
    this->nodes[i] = copyNode;
  }  
}

// getters 
int NodeList::getLength(){
  // TODO
  return this->length;
}

void NodeList::addElement(Node* newPos){
  // TODO
  // make copy then add to list
  Node* copyNode = new Node(*newPos);
  nodes[length] = copyNode; // adding to the back
  length++;
}

Node* NodeList::getNode(int i){
  // TODO
  return nodes[i]; // returing the ith element
}

bool NodeList::contains(Node* node) {
  bool found = false;
  // check if node exits in list
  for (int i = 0; i < this->getLength(); ++i) {
    Node* currNode = this->getNode(i);
    if (currNode->equals(node)) {
      found = true;
    }
  }   
  return found;
}
