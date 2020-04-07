/* 
    Berke Batmaz (s3782067)

    -I decided to stick closely to the starter code and assignment spec,
    only creating new attributes/methods where needed. The flow of the program
    remains the same with where and how values are passed.

    -I initially struggled with passing/returning arrays as parameters, especially
    when working with the typedef 'coordinate' that I defined as an int array of length
    2. I handled these issues by rewatching and understanding the video "Arrays, Pointers
    and Arrays as Pointers" and looking through sample lecture code.

    -Specifically in Milestone 3, the cardinal walking directions, even though the trail
    holds very similar information regarding where in the maze we travelled to. To minimize
    modifying the starter code and maintain readable code I decided on a new array of std strings
    called 'directions'. This makes the code clear in that, when we move in a direction, I simply\
    add that direction we just moved as a string to that array. It could get confusing and less readable
    if the breadcrumb class implemented some form of a direction attribute that tracked either the movement
    to it or movement out of it.

    -My implementation has fairly obvious occurences of code repetition, code that could be split off
    into functions. However my implementation allocates memory on the heap only when required and passes
    references rather than pointers where possible, this makes it quite efficient memory-wise and avoids
    memory leaks.
 */
#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"

// Helper test functions
void testBreadcrumb();
void testTrail();

// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);
void printMazeAndDirectionsStdout(Maze maze, Trail* solution, std::string* directionsPtr);

int main(int argc, char** argv) {

    // Load Maze from stdin
    Maze maze;
    readMazeStdin(maze);

    // Solve using MazeSolver
    MazeSolver* solver = new MazeSolver();
    Trail* solution = nullptr;
    solver->solve(maze);
    solution = solver->getSolution();

    std::string* directionsPtr = solver->getDirections();

    // Print Maze to stdout
    printMazeAndDirectionsStdout(maze, solution, directionsPtr);

    delete solver;

    return EXIT_SUCCESS;
}

void readMazeStdin(Maze maze) {
    // ASSUME THE MAZE IS A FIXED SIZE (20X20).
    for(int y = 0; y < MAZE_DIM; ++y){
        for(int x = 0; x < MAZE_DIM; ++x){
            std::cin >> maze[y][x];
        }
    }
}


void printMazeStdout(Maze maze, Trail* solution) {
    for(int y = 0; y < MAZE_DIM; ++y){
        for(int x = 0; x < MAZE_DIM; ++x){
                if(solution->contains(x, y) && solution->getIndex(x, y)->isStale() == false){
                    if(maze[y][x] == 'S'){
                        std::cout << 'S';
                    }else{
                        std::cout << ROUTE;
                    }
                }else{
                    std::cout << maze[y][x];
                }
        }
        std::cout << std::endl;
    }
}

void printMazeAndDirectionsStdout(Maze maze, Trail* solution,std::string* directionsPtr) {
    for(int y = 0; y < MAZE_DIM; ++y){
        for(int x = 0; x < MAZE_DIM; ++x){
                if(solution->contains(x, y) && solution->getIndex(x, y)->isStale() == false){
                    if(maze[y][x] == 'S'){
                        std::cout << 'S';
                    }else{
                        std::cout << ROUTE;
                    }
                }else{
                    std::cout << maze[y][x];
                }
        }
        std::cout << std::endl;
    }
    for(int i = 0; i < TRAIL_ARRAY_MAX_SIZE; ++i){
        if(solution->getPtr(i) != nullptr && solution->getPtr(i)->isStale() == false){
            std::cout << directionsPtr[i] << std::endl;
        }
        
    }
}