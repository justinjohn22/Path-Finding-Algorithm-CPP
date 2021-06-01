#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathSolver {
public:
  /*                                           */
  /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
  /*                                           */

  // Constructor/Destructor
  PathSolver();
  ~PathSolver();

  // Execute forward search algorithm
  // To be implemented for Milestone 2
  void forwardSearch(Env env);

  // Get a DEEP COPY of the explored NodeList in forward search
  // To be implemented for Milestone 2
  NodeList* getNodesExplored();

  // Execute backtracking and Get a DEEP COPY of the path the 
  // robot should travel
  // To be implemented for Milestone 3
  NodeList* getPath(Env env);

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
  void setRow(int row);
  void setCol(int col);
  int getRow();
  int getCol();

private:
  /*                                           */
  /* DO NOT MOFIFY THESE VARIABLES             */
  /*                                           */

  // Nodes explored in forward search algorithm
  NodeList* nodesExplored;
  

  /*                                           */
  /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
  /*                                           */
  NodeList* openList;
  int col;
  int row;

  Node* getKeyPosition(Env env, char key); 
  Node* getMinEstDist(Node* nodeAtHand, Node* nodeGoal);
  void updateValidPos(Node* currNode, Env env);
  void checkNode(Node* nodeAtHand, int rowVal, int colVal, Env env);
  Node* getValidNode(Node* currentNode, Env env);
  
};

#endif //COSC_ASSIGN_ONE_PATHSOLVER