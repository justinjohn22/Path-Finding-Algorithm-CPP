#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled)
{
  // TODO
  // construct node 
  this->row = row; 
  this->col = col;
  this->dist_traveled = dist_traveled;
}

Node::Node(Node& other) {
  // deconstruct node
  this->row = other.row;
  this->col = other.col;
  this->dist_traveled = other.dist_traveled;
}

Node::~Node(){
  // TODO 
}

// getters 
int Node::getRow(){
  // TODO
  return this->row;
}

int Node::getCol(){
  // TODO
  return this->col;
}

int Node::getDistanceTraveled(){
  // TODO
  return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
  // TODO
  this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
  // TODO
  // equation based on spec
  int manhatten_dist = abs(this->getCol() - goal->getCol()) 
                        + abs(this->getRow() - goal->getRow()); 

  int est_dist = this->getDistanceTraveled() + manhatten_dist;
  return est_dist;
}

bool Node::equals(Node* node) {
  bool equality = false;
  // check equality on node on grid
  if (this->row == node->getRow() && 
        this->col == node->getCol()) {
        equality = true;
  }
  return equality;

}
    
//--------------------------------                             