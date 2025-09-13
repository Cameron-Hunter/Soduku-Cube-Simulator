/*
    cube.h file for sodoku cube simulator
    Made by Cameron Hunter
    Programing buddy: Rian
    Date Started: September 10, 2025
    Date Finished: 9/12/2025

    This file contatins a struct for the cube
    This file also contains declartions for 
    rotation functions, print functions, a reset function, 
    a randomize function and declares the function to 
    calculate the heuristic value of the cube
*/
#include <string>
#include <vector>

struct tile{
    int number; // 0-9 number on the cube
    std::string color; // color of the tile

    bool operator==(const tile &other) const {
        return number == other.number && color == other.color; // compare based on number only
    }

    bool operator!=(const tile &other) const {
        return !(*this == other); // use the equality operator to define inequality
    }
};

std::string ansiColorFromCode(int code);
tile makeTile(int n, int colorCode);

struct cube{
    tile front[3][3];
    tile back[3][3];
    tile left[3][3];
    tile right[3][3];
    tile top[3][3];
    tile bottom[3][3];
};

extern cube solvedCube; // global variable to hold the solved state of the cube




// Prints the 6 faces of the cube in an unfolded layout
void printCube(const cube c);


// Resets the cube to the solved state
void resetCube(cube &c);


// rotation functions
void rotateFrontClockwise(cube &c);
void rotateFrontCounterclockwise(cube &c);
void rotateBackClockwise(cube &c);
void rotateBackCounterclockwise(cube &c);
void rotateLeftClockwise(cube &c);
void rotateLeftCounterclockwise(cube &c);
void rotateRightClockwise(cube &c);
void rotateRightCounterclockwise(cube &c);
void rotateTopClockwise(cube &c);
void rotateTopCounterclockwise(cube &c);
void rotateBottomClockwise(cube &c);
void rotateBottomCounterclockwise(cube &c);
std::vector<std::string> randomizeCube(cube &c, int n);


// Hueristic function declaration and helper functions

int calculateHeuristic(cube &c);

// compares the cube to the solved state and counts the number of misplaced pieces
int countMisplaced(cube &c);

// counts the number of conflits on the cube.
// conflicts when the same number apears on the same face
int countConflicts(cube &c);
