
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   solution = new Trail();
   directions = new std::string[TRAIL_ARRAY_MAX_SIZE];
}

MazeSolver::~MazeSolver() {
  delete &solution;
}

void MazeSolver::solve(Maze maze) {
   coordinate b = {};
   coordinate E = {};
   int directionsLength = 0;
   //FINDING 'S' AND 'E'
   for(int y = 0; y < MAZE_DIM; ++y){
      for(int x = 0; x < MAZE_DIM; ++x){
         if(maze[y][x] == 'E'){
            E[0] = x;
            E[1] = y;
         }
         if(maze[y][x] == 'S'){
            b[0] = x;
            b[1] = y;
         }
      }
   }
   do{
      if(!solution->contains(b[0], b[1])){
         solution->addCopy(new Breadcrumb(b[0], b[1], false));
      }
      coordinate l = {};
      if(canMove(b, NORTH, maze, solution)){
         l[0] = b[0];
         l[1] = b[1] - 1;
         moveB(b, l);
         directions[directionsLength] = std::string("north");
         directionsLength += 1;
      } else if(canMove(b, EAST, maze, solution)){
         l[0] = b[0] + 1;
         l[1] = b[1];
         moveB(b, l);
         directions[directionsLength] = std::string("east");
         directionsLength += 1;
      } else if(canMove(b, SOUTH, maze, solution)){
         l[0] = b[0];
         l[1] = b[1] + 1;
         moveB(b, l);
         directions[directionsLength] = std::string("south");
         directionsLength += 1;
      } else if(canMove(b, WEST, maze, solution)){
         l[0] = b[0] - 1;
         l[1] = b[1];
         moveB(b, l);
         directions[directionsLength] = std::string("west");
         directionsLength += 1;
      } 
      else {
         for(int i = 0; i < solution->size(); ++i){
            if(solution->getPtr(i) != nullptr){
               if(solution->getPtr(i)->getX() == b[0] &&
                  solution->getPtr(i)->getY() == b[1]){
                     solution->getPtr(i)->setStale(true);
                     b[0] = solution->getPtr(i-1)->getX();
                     b[1] = solution->getPtr(i-1)->getY();
                  }
            }
         }
         
      }
   }while(!(b[0] == E[0] && b[1] == E[1]));
}
Trail* MazeSolver::getSolution() {
   int solutionLength = solution->size();
   Trail* solutionCopy = new Trail();
   for(int s = 0; s < solutionLength; ++s){
      if(solution->getPtr(s) != nullptr){
         solutionCopy->addCopy(new Breadcrumb(solution->getPtr(s)->getX(),
          solution->getPtr(s)->getY(),
           solution->getPtr(s)->isStale()));
      }
   }
   return solutionCopy;
}

std::string* MazeSolver::getDirections(){
   return directions;
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





