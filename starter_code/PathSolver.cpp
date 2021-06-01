#include "PathSolver.h"
#include <iostream>

#define FIRST_ELEMENT 0

PathSolver::PathSolver(){
  // TODO
  // construct path solver
  nodesExplored = new NodeList();
  openList = new NodeList();
  row = 0;
  col = 0;
}

PathSolver::~PathSolver(){
  // TODO
  // delete nodesExplored;
  delete openList;
}

// setters 
void PathSolver::setRow(int row) {
  this->row = row;
}

void PathSolver::setCol(int col) {
  this->col = col;
}

// getters
int PathSolver::getRow() {
  return this->row;
}

int PathSolver::getCol() {
  return this->col;
}

void PathSolver::forwardSearch(Env env){
  // TODO
  // get start node and goal node
  Node* nodeAtHand = getKeyPosition(env, SYMBOL_START);
  Node* nodeGoal = getKeyPosition(env, SYMBOL_GOAL);  

  // add start node to list
  openList->addElement(nodeAtHand);

  // check if current node has reached goal
  while (!nodeAtHand->equals(nodeGoal)) { 
    // get node with lowest est dist in open list
    nodeAtHand = getMinEstDist(nodeAtHand, nodeGoal);
    // check valid positions to move
    updateValidPos(nodeAtHand, env);
    // add to closed list 
    nodesExplored->addElement(nodeAtHand);
  }
  delete nodeAtHand;
  delete nodeGoal;  
}

Node* PathSolver::getKeyPosition(Env env, char key) {
  // TODO 
  // loop through matrix and find loc of start and goal
  Node* keyNode = nullptr;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      if (env[i][j] == key) {
        keyNode = new Node(i,j,0);
        }
    }
  }
  return keyNode;
}

Node* PathSolver::getMinEstDist(Node* nodeAtHand, 
                                        Node* nodeGoal) {
  // TODO  
  // linear search through openlist to find lowest node
  for (int i = 0; i < openList->getLength() - 1; ++i) {
    Node* nextNode = openList->getNode(i + 1);
    if (((this->nodesExplored)->contains(nodeAtHand)) 
            || (nodeAtHand->getEstimatedDist2Goal(nodeGoal) 
                >= nextNode->getEstimatedDist2Goal(nodeGoal) && 
                !(this->nodesExplored)->contains(nextNode))) {
    
        nodeAtHand = nextNode;
    } 
  }
  
  return nodeAtHand;
}

void PathSolver::updateValidPos(Node* nodeAtHand, Env env) {
  // check north > row - 1, col is same 
  checkNode(nodeAtHand, -1, 0, env);
  // check east  > row is same, col + 1
  checkNode(nodeAtHand, 0, 1, env);
  // check south > row + 1, col is same
  checkNode(nodeAtHand, 1, 0, env); 
  // check west  > row is same, col - 1
  checkNode(nodeAtHand, 0, -1, env);
}

void PathSolver::checkNode(Node* nodeAtHand, int rowVal, 
                                      int colVal, Env env) {
  
  // get row and col for cleaner code
  int totalRowVal = (nodeAtHand->getRow()) + rowVal;
  int totalColVal = (nodeAtHand->getCol()) + colVal;

  // see valid pos or goal
  if (env[totalRowVal][totalColVal] == SYMBOL_EMPTY ||
    env[totalRowVal][totalColVal] == SYMBOL_GOAL) {

    // if valid, addd to openlist if not exist  
    Node* node = new Node(totalRowVal, totalColVal,
            (nodeAtHand->getDistanceTraveled()) + 1);

    if (!openList->contains(node)) {
        openList->addElement(node);
    }
    delete node;
  }
}

NodeList* PathSolver::getNodesExplored(){
  //TODO
  // make copy of nodesExplored, then delete
  NodeList* copyList = new NodeList(*(nodesExplored));
  return copyList;
  //return this->nodesExplored;
}

NodeList* PathSolver::getPath(Env env){
  // TODO
  // get goal and startNode
  Node* currentNode = nodesExplored->
      getNode(nodesExplored->getLength() - 1);
  Node* goalNode = nodesExplored->getNode(FIRST_ELEMENT);
  NodeList* exploredPositions = new NodeList();

  // add start to new lsit
  exploredPositions->addElement(currentNode);

  // similiar logic to forward search 
  while (!currentNode->equals(goalNode)) {
      for (int i = 0; i < nodesExplored->getLength(); ++i) {
        Node* checkingNode = nodesExplored->getNode(i);
        // check each node to see if its 1 less
        bool checkDistance = (checkingNode->getDistanceTraveled() 
                            == currentNode->getDistanceTraveled() - 1);

        // getting adjacent node from closed list 
        // if on closed list, we know its symbol_empty 

        // check north > row - 1, col is same 
        if (currentNode->getRow() - 1 == checkingNode->getRow() 
          && currentNode->getCol() == checkingNode->getCol()) {
          if (checkDistance) {
            currentNode = nodesExplored->getNode(i);
            exploredPositions->addElement(currentNode);
          }
        }

        // check east  > row is same, col + 1
        if (currentNode->getRow() == checkingNode->getRow() 
          && currentNode->getCol() + 1 == checkingNode->getCol()) {
          if (checkDistance) {
            currentNode = nodesExplored->getNode(i);
            exploredPositions->addElement(currentNode);
          }
        }

        // check south > row + 1, col is same
        if (currentNode->getRow() + 1 == checkingNode->getRow() 
          && currentNode->getCol() == checkingNode->getCol()) {
          if (checkDistance) {
           currentNode = nodesExplored->getNode(i);
           exploredPositions->addElement(currentNode);
         }
        }

        // check west  > row is same, col - 1
        if (currentNode->getRow() == checkingNode->getRow() 
          && currentNode->getCol() - 1 == checkingNode->getCol()) {
          if (checkDistance) {
            currentNode = nodesExplored->getNode(i);
            exploredPositions->addElement(currentNode);
          }
        }
    }
  }

  delete currentNode;

  // make length here for cleaner code
  int length = exploredPositions->getLength() - 1;

  // new list to easily reverse list 
  NodeList* reversed = new NodeList();
  for (int i = 0; i <= length; ++i) {
    // add back element to top of new list
    reversed->addElement(exploredPositions->getNode(length - i));
  }

  return reversed;  
}

//-----------------------------