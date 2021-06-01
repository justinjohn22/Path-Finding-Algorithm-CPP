/*
 * The approach I took was to follow the psuedocode directly.
 * I planned to make a brute force algorithm and then to 
 * optimise it once I know that the algorithm is working.
 * I also took the time to draw diagrams as well as do desk
 * checks when completing this assignment, especially for 
 * milestone 4.
 *  
 * the main issue I encountered was memeory allocation and 
 * deallocation, this was a new concept to me working with a 
 * project as big as this. I also had to spend a lot of time
 * trying to fix segmentation fault. Overall it was a good
 * experience learning about these new concepts and 
 * having to really spent time debugging code. I wish I had 
 * more time to remove code duplication in one part of my 
 * code.
 * 
 * MileStone 3: Was a lot easier than milestone 2, 
 * in the video, it again asked to check for open spaces 
 * from current node, i felt like this was unnecessary 
 * as everything on the closed list would already have to 
 * be on an open space.
 * 
 * MileStone 4: Was the hardest out of the 4, I spent a lot 
 * of time trying different things to get the env into the 
 * program. I eventually ended up finding a logic using an
 * input stream. I was really excited when it worked!!
 */
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
// void testNode();
// void testNodeList();

// // Read a environment from standard input.
Env readEnvStdin(Env env, PathSolver* pathSolver);

// // Print out a Environment to standard output with path.
// // To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution, PathSolver* ps);

void delete_env(Env env, int rows, int cols);
Env make_env(const int rows, const int cols);



int main(int argc, char** argv){
  // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
  // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
  // AS YOU GO ALONG.
  // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
  // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
  // testNode();
  // testNodeList();
  // std::cout << "DONE TESTING" << std::endl << std::endl;

  // Load Environment 
  Env env;
  env = nullptr;

  // MILESTONE 4

  // create pathsolver obj
  PathSolver* pathSolver = new PathSolver();

  // use pathsolver to get env
  env = readEnvStdin(env, pathSolver); 

  // find path  
  pathSolver->forwardSearch(env);

  // get shortest path
  NodeList* solution = pathSolver->getPath(env);

  // output solution
  printEnvStdout(env, solution, pathSolver);

  NodeList* exploredPositions = nullptr;
  exploredPositions = pathSolver->getNodesExplored();

  // memory management
  delete_env(env, pathSolver->getRow(), pathSolver->getCol());
  delete pathSolver;
  delete exploredPositions;
  delete solution;


  // // Solve using forwardSearch
  // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
  // PathSolver* pathSolver = new PathSolver();

  //pathSolver->forwardSearch(env);


  // NodeList* exploredPositions = nullptr;
  // exploredPositions = pathSolver->getNodesExplored();

  // std::cout << exploredPositions << std::endl;

  // // Get the path
  // // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
  //NodeList* solution = pathSolver->getPath(env);

  //printEnvStdout(env, solution);

  // delete pathSolver;
  //delete exploredPositions;
  // delete solution;

}

// read method
Env readEnvStdin(Env env, PathSolver* ps){
  // TODO
  std::string input_stream = "";

  // change into string stream
  while (!std::cin.eof()) {  
    char c;
    std::cin.get(c);
    input_stream.push_back(c); 
  }
  input_stream.pop_back();

  int rowCount = 1;
  int colCount = 1;
  bool check = false;

  // find col and row based on new line char
  for (std::string::size_type i = 0; i < input_stream.size(); ++i) {
    
    if (input_stream[i] != '\n' && !check) {
        colCount++;
    } 
    if (input_stream[i] == '\n'){
        rowCount++;
        check = true;
    }
  }

  // set row and col for later use in pathsolver 
  ps->setRow(rowCount);
  ps->setCol(colCount);

  // allocate memory for env
  Env newEnv = make_env(rowCount, colCount);

  int traceChar = 0;

  for (int i = 0; i < rowCount; ++i) {
    for (int j = 0; j < colCount; ++j) {
        newEnv[i][j] = input_stream[traceChar];
        traceChar++;  
    }
  }

  // add env to allocated memory
  env = newEnv;
  return env;
}

/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols) {
   Env env = nullptr;

   if (rows >= 0 && cols >= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[cols];
      }
   }
   return env;
}

// /*
//  * This function is to help you delete a 
//  * dynamically allocated 2D Environment.
//  */
void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
}

// output final path solution
void printEnvStdout(Env env, NodeList* solution, PathSolver* ps) {
  // TODO
  for (int i = 1; i < solution->getLength() - 1; ++i) {
    Node* currentNode = solution->getNode(i);
    Node* nextNode = solution->getNode(i + 1);
    int cRow = currentNode->getRow();
    int cCol = currentNode->getCol();
    int nRow = nextNode->getRow();
    int nCol = nextNode->getCol();
    
    // check difference to find right arrow 
    if (nCol - cCol == 1) { // Move Right
        env[cRow][cCol] = '>';
    } else if (nRow - cRow == 1) { // Move Down
        env[cRow][cCol] = 'v';
    } else if (nCol - cCol == -1) { // Move Left
        env[cRow][cCol] = '<';
    } else if (nRow - cRow == -1) { // Move Up
        env[cRow][cCol] = '^';
    }
  }

  // Final output to console 
  for (int i = 0; i < ps->getRow(); ++i) {
    for (int j = 0; j < ps->getCol(); ++j) {
      std::cout << env[i][j];                       
    }
  }
  std::cout << std::endl;
}


// void testNode() {
//     std::cout << "TESTING Node" << std::endl;

//     // Make a Node and print out the contents
//     Node* node = new Node(1, 1, 2);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceTraveled() << std::endl;
//     delete node;

//     // Change Node and print again
//     node = new Node(4, 2, 3);
//     std::cout << node->getRow() << ",";
//     std::cout << node->getCol() << ",";
//     std::cout << node->getDistanceTraveled() << std::endl;
//     delete node;
// }

// void testNodeList() {
//     std::cout << "TESTING NodeList" << std::endl;

//     // Make a simple NodeList, should be empty size
//     NodeList* nodeList = new NodeList();
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add a Node to the NodeList, print size
//     Node* b1 = new Node(1, 1, 1);
//     std::cout << "Passed creating node" << std::endl;
//     nodeList->addElement(b1);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Add second Nodetest
//     Node* b2 = new Node(0, 0, 1);
//     nodeList->addElement(b2);
//     std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

//     // Test Get-ith - should be 0,0,1
//     Node* getB = nodeList->getNode(1);
//     std::cout << getB->getRow() << ",";
//     std::cout << getB->getCol() << ",";
//     std::cout << getB->getDistanceTraveled() << std::endl;

//     // Print out the NodeList
//     std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
// }