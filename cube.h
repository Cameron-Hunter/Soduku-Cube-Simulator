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

struct cube{
    int front[3][3];
    int back[3][3];
    int left[3][3];
    int right[3][3];
    int top[3][3];
    int bottom[3][3];
};

void printCube(cube c);

void resetCube(cube &c);

void rotateFrontClockwise(cube &c);
void rotateFrontCounterclockwise(cube &c);
void rotateBackClockwise(cube &c);
void rotateBackCounterclockwise(cube &c);
void rotateLeftClockwise(cube &c);
void rotateLeftCounterclockwise(cube &c);
void rotateRightClockwise(cube &c);
void rotateRightCounterclockwise(cube &c);
std::vector<std::string> randomizeCube(cube &c, int n);