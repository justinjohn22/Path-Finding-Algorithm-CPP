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

