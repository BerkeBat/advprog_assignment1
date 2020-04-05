
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   solution = new Trail();
}

MazeSolver::~MazeSolver() {
   // TODO delete solution;
}

void MazeSolver::solve(Maze maze) {
   coordinate b = {};
   coordinate E = {};
   //FINDING 'E'
   for(int y = 0; y < MAZE_DIM; ++y){
      for(int x = 0; x < MAZE_DIM; ++x){
         if(maze[y][x] == 'E'){
            E[0] = x;
            E[1] = y;
         }
      }
   }
   //FINDING 'S'
   for(int y = 0; y < MAZE_DIM; ++y){
      for(int x = 0; x < MAZE_DIM; ++x){
         if(maze[y][x] == 'S'){
            b[0] = x;
            b[1] = y;
         }
      }
   }
   // std::cout << "Starting at: " << b[0] << ", " << b[1] << std::endl;
   do{
      if(!solution->contains(b[0], b[1])){
         solution->addCopy(new Breadcrumb(b[0], b[1], false));
      }
      // std::cout << "Can move N?: " << canMove(b, NORTH, maze, solution) << std::endl;
      // std::cout << "Can move E?: " << canMove(b, EAST, maze, solution) << std::endl;
      // std::cout << "Can move S?: " << canMove(b, SOUTH, maze, solution) << std::endl;
      // std::cout << "Can move W?: " << canMove(b, WEST, maze, solution) << std::endl;
      
      
      //CHECKING DIRECTION FOR POTENTIAL MOVE
      bool foundMove = false;
      int direction = 0;
      coordinate l = {};
      while(foundMove == false){
         if(canMove(b, direction, maze, solution)){
            if(direction == NORTH){
               l[0] = b[0];
               l[1] = b[1] - 1;
            } else if(direction == EAST){
               l[0] = b[0] + 1;
               l[1] = b[1];
            } else if(direction == SOUTH){
               l[0] = b[0];
               l[1] = b[1] + 1;
            } else if(direction == WEST){
               l[0] = b[0] - 1;
               l[1] = b[1];
            } 
            foundMove = true;
         }
         direction += 1;
      }
      moveB(b, l);
      std::cout << "b: " << b[0] << "," << b[1] << std::endl; 
   }while(!(b[0] == E[0] && b[1] == E[1]));
}

// bool canMove(int b, int direction){
   
// }

Trail* MazeSolver::getSolution() {
   return solution;
}

void MazeSolver::moveB(coordinate b, coordinate destination){
   b[0] = destination[0];
   b[1] = destination[1];
}

bool MazeSolver::canMove(coordinate b, int direction, Maze maze, Trail* solution){
   coordinate lToCheck = {};
   if(direction == NORTH){
      lToCheck[0] = b[0];
      lToCheck[1] = b[1] - 1;
   } else if(direction == EAST){
      lToCheck[0] = b[0] + 1;
      lToCheck[1] = b[1];
   } else if(direction == SOUTH){
      lToCheck[0] = b[0];
      lToCheck[1] = b[1] + 1;
   } else if(direction == WEST){
      lToCheck[0] = b[0] - 1;
      lToCheck[1] = b[1];
   } 
   if(lToCheck[0] < 0 ||
      lToCheck[0] > MAZE_DIM ||
      lToCheck[1] < 0 ||
      lToCheck[1] > MAZE_DIM){
         return false;
   }
   if(solution->contains(lToCheck[0], lToCheck[1]) ||
      maze[lToCheck[1]][lToCheck[0]] == WALL){
      return false;
   }
   return true; 
}

// coordinate* getL(int* b, int direction, coordinate l){
   // if(direction == NORTH){
   //    l[0] = b[0];
   //    l[1] = b[1] - 1;
   // } else if(direction == EAST){
   //    l[0] = b[0] + 1;
   //    l[1] = b[1];
   // } else if(direction == SOUTH){
   //    l[0] = b[0];
   //    l[1] = b[1] + 1;
   // } else if(direction == WEST){
   //    l[0] = b[0] - 1;
   //    l[1] = b[1];
   // } 
//    return l;
// }





