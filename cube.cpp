/*
    cube.cpp file for the Sodoku Cube Simulator
    Made by Cameron Hunter
    Programing buddy: Rian
    Date Started: September 10, 2025
    Date Finished: 9/12/2025

    This file contains the functions that manipulate the cube
    Functions to rotate each face clockwise and counterclockwise
    This file also contains functions to print the cube,
    reset the cube to the solved state, and randomize the cube.
    This file also contains the function to calculate the heuristic value of the cube

*/



#include <iostream>
#include "cube.h"
#include <random>
#include <string>
#include <vector>
#include <ctime>

using namespace std;









// helper function to create a tile with a number and corresponding color
tile makeTile(int n, int colorCode) {
    tile newTile;
    newTile.number = n;
    newTile.color = ansiColorFromCode(colorCode);
    
    return newTile;
}


std::string ansiColorFromCode(int code) {
    switch (code) {
        case 1: return "\x1b[34m";        // Blue
        case 2: return "\x1b[36m";        // Cyan
        case 3: return "\x1b[31m";        // Red
        case 4: return "\x1b[32m";        // Green
        case 5: return "\x1b[33m";        // Yellow
        case 6: return "\x1b[38;5;208m";  // Orange (256-color)
        default: return "\x1b[0m";        // Reset/fallback
    }
}







// Definition and initialization
cube solvedCube = {
    // front
    {{makeTile(9,2),makeTile(5,3),makeTile(2,1)},{makeTile(3,3),makeTile(8,5),makeTile(1,4)},{makeTile(6,6),makeTile(7,5),makeTile(4,3)}},
    // back
    {{makeTile(9,1),makeTile(5,2),makeTile(2,2)},{makeTile(3,4),makeTile(8,1),makeTile(1,1)},{makeTile(6,1),makeTile(7,1),makeTile(4,5)}},
    // left
    {{makeTile(7,1),makeTile(1,2),makeTile(8,5)},{makeTile(2,4),makeTile(4,2),makeTile(6,1)},{makeTile(9,2),makeTile(3,2),makeTile(5,5)}},
    // right
    {{makeTile(4,2),makeTile(6,6),makeTile(3,3)},{makeTile(7,5),makeTile(5,4),makeTile(9,6)},{makeTile(1,5),makeTile(2,3),makeTile(8,6)}},
    // top
    {{makeTile(8,3),makeTile(1,5),makeTile(3,4)},{makeTile(4,6),makeTile(6,6),makeTile(7,1)},{makeTile(2,3),makeTile(9,4),makeTile(5,6)}},
    // bottom
    {{makeTile(1,4),makeTile(2,6),makeTile(8,4)},{makeTile(5,3),makeTile(3,3),makeTile(9,5)},{makeTile(7,6),makeTile(4,2),makeTile(6,4)}}
};




void printTile(const tile &t){
    cout << t.color << t.number << "\033[0m"; // Print number with color and reset color
}




// prints the cube in a unfolded layout
void printCube(cube c){
    cout<<"         -------"<<endl;
    // Print top face
    for(int i = 0; i < 3; i++){
        cout << "        | ";
        for(int j = 0; j < 3; j++){
            printTile(c.top[i][j]);
            cout << " ";
        }
        cout <<"|"<< endl;
    }
    cout<<" ------------------------------"<<endl;
    // Print left, front, right, back faces
    // Left, Front, Right, Back

for (int i = 0; i < 3; i++) {
    std::cout << "| ";
    for (int j = 0; j < 3; j++) {
         printTile(c.left[i][j]);
         cout << " ";
         }
    std::cout << "| ";
    for (int j = 0; j < 3; j++) {
         printTile(c.front[i][j]);
         cout<< " ";
         }
    std::cout << "| ";
    for (int j = 0; j < 3; j++) { printTile(c.right[i][j]); 
    cout << " ";
    }
    std::cout << "| ";
    for (int j = 2; j >= 0; j--) { 
        printTile(c.back[i][j]); 
        cout << " ";
    } // flipped
    std::cout << "|" << std::endl;
}
      cout<<" ------------------------------"<<endl;
    // Print bottom face
    for(int i = 0; i < 3; i++){
        cout << "        | ";
        for(int j = 0; j < 3; j++){
            printTile(c.bottom[i][j]);
            cout << " ";
        }
        cout <<"|" <<endl;

    }
     cout<<"         -------"<<endl;
}









// resets the cube to the solved state
// solved state is defined in cube.h
void resetCube(cube &c){
    c = solvedCube;
}










//Rotation functions

// rotates the front face clockwise
// Rubik's notation: F

void rotateFrontClockwise(cube &c) {
    tile new_front[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_front[j][2 - i] = c.front[i][j];
        }
    }
    for (int i = 0; i < 3; i++) {
         for (int j = 0; j < 3; j++) {
            c.front[i][j] = new_front[i][j];  
    }
}

    tile temp[3];
    for (int i = 0; i < 3; i++){ 
        temp[i] = c.top[2][i];
    }
    for (int i = 0; i < 3; i++){
     c.top[2][i]    = c.left[2 - i][2];
    }

    for (int i = 0; i < 3; i++){
         c.left[i][2]   = c.bottom[0][i];
    }
    for (int i = 0; i < 3; i++){ 
        c.bottom[0][i] = c.right[2 - i][0];
    }
    for (int i = 0; i < 3; i++){
         c.right[i][0]  = temp[i];
    }
}









// rotates the front face counter-clockwise
// Rubik's notation: F'
void rotateFrontCounterclockwise(cube &c) {
    // rotate the front face
    tile new_front[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_front[2 - j][i] = c.front[i][j];
        }
    }

   for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.front[i][j] = new_front[i][j];  
    }
    }


    // cycle the edge strips (reverse of F)
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[2][i];                 // save bottom row of top
    }

    for (int i = 0; i < 3; i++){
         c.top[2][i]    = c.right[i][0];        // top <- right col
    }     

    for (int i = 0; i < 3; i++){
         c.right[i][0]  = c.bottom[0][2 - i];   // right <- bottom row (reversed)
    } 
    for (int i = 0; i < 3; i++){
         c.bottom[0][i] = c.left[i][2];         // bottom <- left col
    }     
    for (int i = 0; i < 3; i++){
         c.left[i][2]   = temp[2 - i];          // left <- saved top row (reversed)
    }
}









// rotates the back face clockwise
// Rubik's notation: B
// (clockwise when looking directly at the back face)
void rotateBackClockwise(cube &c) {
    // rotate the back face itself
    tile new_back[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_back[j][2 - i] = c.back[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.back[i][j] = new_back[i][j];  
    }
    }   

    // cycle the adjacent strips
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[0][i];          // save top row of top
    }

    for (int i = 0; i < 3; i++){
         c.top[0][i]    = c.right[i][2];      // top <- right col
    }
    for (int i = 0; i < 3; i++){
         c.right[i][2]  = c.bottom[2][2 - i]; // right <- bottom row (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.bottom[2][i] = c.left[i][0];       // bottom <- left col
    }
    for (int i = 0; i < 3; i++){
         c.left[i][0]   = temp[2 - i];        // left <- saved top row (reversed)
    }
}









// makes the B' rotation on the cube
// This notation is a bit weird here because the back face is opposite the front face
// so clockwise on the back face is counterclockwise on the front face
//and vice versa
void rotateBackCounterclockwise(cube &c)  {
    // rotate the back face itself
    tile new_back[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_back[2 - j][i] = c.back[i][j];
        }
    }
    
    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.back[i][j] = new_back[i][j];  
    }
    }   

    // cycle the adjacent strips (reverse of B)
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[0][i];          // save top row of top
    }

    for (int i = 0; i < 3; i++){
         c.top[0][i]    = c.left[2 - i][0];   // top <- left col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.left[i][0]   = c.bottom[2][i];     // left <- bottom row
    }
    for (int i = 0; i < 3; i++){
         c.bottom[2][i] = c.right[2 - i][2];  // bottom <- right col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.right[i][2]  = temp[i];            // right <- saved top row
    }


}








// makes the L rotation on the cube
// equivalent to rotating the fronts left column downwards
void rotateLeftClockwise(cube &c){
  // rotate the left face itself
    tile new_left[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_left[j][2 - i] = c.left[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.left[i][j] = new_left[i][j];  
    }
    }   

    // cycle the adjacent strips
    tile temp[3];
    for (int i = 0; i < 3; i++){
        temp[i] = c.top[i][0];                  // save left col of top
    }

    for (int i = 0; i < 3; i++){
         c.top[i][0]    = c.back[2 - i][2];      // top <- back col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.back[i][2]   = c.bottom[2 - i][0];    // back <- bottom col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.bottom[i][0] = c.front[i][0];         // bottom <- front col
    }
    for (int i = 0; i < 3; i++){
         c.front[i][0]  = temp[i];               // front <- saved top col
    }
}









// makes the L' rotation on the cube
// equivalent to rotating the fronts left column upwards
void rotateLeftCounterclockwise(cube &c){
  // rotate the left face itself
    tile new_left[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_left[2 - j][i] = c.left[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.left[i][j] = new_left[i][j];  
    }
    }   

    // cycle the adjacent strips (reverse of L)
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[i][0];          // save left col of top
    }

    for (int i = 0; i < 3; i++){
         c.top[i][0]    = c.front[i][0];     // top <- front col
    }
    for (int i = 0; i < 3; i++){
         c.front[i][0]  = c.bottom[i][0];    // front <- bottom col
    }
    for (int i = 0; i < 3; i++){
         c.bottom[i][0] = c.back[2 - i][2];  // bottom <- back col (reversed)
    }
    for (int i = 0; i < 3; i++){
        c.back[i][2]   = temp[2 - i];       // back <- saved top col (reversed)
    }
}

    







// makes the R rotation on the cube
// equivalent to rotating the fronts right column upwards
void rotateRightClockwise(cube &c){
  // rotate the right face itself
    tile new_right[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_right[j][2 - i] = c.right[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.right[i][j] = new_right[i][j];  
    }
    }   

    // cycle the adjacent strips
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[i][2];          // save right col of top
    }

    for (int i = 0; i < 3; i++){
         c.top[i][2]    = c.front[i][2];     // top <- front col
    }
    for (int i = 0; i < 3; i++){
         c.front[i][2]  = c.bottom[i][2];    // front <- bottom col
    }
    for (int i = 0; i < 3; i++){
         c.bottom[i][2] = c.back[2 - i][0];  // bottom <- back col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.back[i][0]   = temp[2 - i];       // back <- saved top col (reversed)
    }
}









// makes the R' rotation on the cube
// equivalent to rotating the fronts right column downwards
void rotateRightCounterclockwise(cube &c){
 // rotate the right face itself
    tile new_right[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_right[2 - j][i] = c.right[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.right[i][j] = new_right[i][j];  
    }
    }   

    // cycle the adjacent strips (reverse of R)
    tile temp[3];
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[i][2];          // save right col of top
    }

    for (int i = 0; i < 3; i++){
         c.top[i][2]    = c.back[2 - i][0];  // top <- back col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.back[i][0]   = c.bottom[2 - i][2];// back <- bottom col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.bottom[i][2] = c.front[i][2];     // bottom <- front col
    }
    for (int i = 0; i < 3; i++){
         c.front[i][2]  = temp[i];           // front <- saved top col
    }
}









// rotates the bottom face clockwise
// Rubik's notation D
// equivalent to rotating the front's bottom row to the RIGHT
void rotateBottomClockwise(cube &c) {
    tile new_bottom[3][3];

    // rotate bottom face 90° clockwise
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new_bottom[j][2 - i] = c.bottom[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.bottom[i][j] = new_bottom[i][j];  
    }
    }   

    // Save front bottom row
    tile temp[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = c.front[2][i];
    }

    // Cycle the rows clockwise
    for (int i = 0; i < 3; i++) {
        tile oldRight = c.right[2][i];
        tile oldBack  = c.back[2][i];
        tile oldLeft  = c.left[2][i];

        c.front[2][i] = oldRight; // front <- right
        c.right[2][i] = oldBack;  // right <- back
        c.back[2][i]  = oldLeft;  // back  <- left
        c.left[2][i]  = temp[i];  // left  <- front
    }
}









// rotates the bottom face counter-clockwise
// Rubik's notation D'
// equivalent to rotating the front's bottom row to the LEFT
void rotateBottomCounterclockwise(cube &c) {
    tile new_bottom[3][3];

    // rotate bottom face 90° counter-clockwise
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new_bottom[2 - j][i] = c.bottom[i][j];
        }
    }
    
    for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.bottom[i][j] = new_bottom[i][j];  
    }
    }   

    // Save front bottom row
    tile temp[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = c.front[2][i];
    }

    // Cycle the rows counter-clockwise
    for (int i = 0; i < 3; i++) {
        tile oldRight = c.right[2][i];
        tile oldBack  = c.back[2][i];
        tile oldLeft  = c.left[2][i];

        c.front[2][i] = oldLeft;  // front <- left
        c.left[2][i]  = oldBack;  // left  <- back
        c.back[2][i]  = oldRight; // back  <- right
        c.right[2][i] = temp[i];  // right <- front
    }
}









// rotates the top face clockwise
// rubix notation U
// equivalent to rotating the fronts top row to the right
void rotateTopClockwise(cube &c){

tile new_top [3][3];


for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        new_top[j][2-i] = c.top[i][j]; // rotate top face clockwise 90
    }
}

 for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.top[i][j] = new_top[i][j];  
    }
    }   

// Save front top row
tile temp[3];
for (int i = 0; i < 3; i++) {
    temp[i] = c.front[0][i];
}

// Cycle the rows clockwise
for (int i = 0; i < 3; i++) {
    tile oldRight = c.right[0][i];
    tile oldBack = c.back[0][i];
    tile oldLeft = c.left[0][i];

    c.front[0][i] = oldRight; // front <- right
    c.right[0][i] = oldBack;  // right <- back
    c.back[0][i] = oldLeft;   // back <- left
    c.left[0][i] = temp[i];   // left <- front 
    }

}










// rotates the top face counter-clockwise
// rubix notation U'
// equivalent to rotating the fronts top row to the left
void rotateTopCounterclockwise(cube &c){
     tile new_top [3][3];

    //rotate top face counterclockwise 90
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            new_top[2-j][i] = c.top[i][j];
        }
    }

     for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
        c.top[i][j] = new_top[i][j];  
    }
    }   

    // Save front top row
    tile temp[3];
    for (int i = 0; i < 3; i++) {
    temp[i] = c.front[0][i];
   }

    for (int i = 0; i < 3; i++) {

    tile oldRight = c.right[0][i];
    tile oldBack = c.back[0][i];
    tile oldLeft = c.left[0][i];

    c.front[0][i] = oldLeft; // front <- left
    c.left [0][i] = oldBack; // left <- back
    c.back[0][i] = oldRight; // back <- right
    c.right[0][i] = temp[i]; // right <- front
    }
}



// Map each move to its face (F=0, B=1, L=2, R=3, D=4, U=5)
int moveFaceIndex(int moveIndex) {
    return moveIndex / 2;
}

// Find the inverse of a move (e.g., F <-> F')
int inverseMoveIndex(int moveIndex) {
    if (moveIndex % 2 == 0) {
        return moveIndex + 1; // F -> F', B -> B', etc.
    } else {
        return moveIndex - 1; // F' -> F, B' -> B, etc.
    }
}


// randomizes the cube with n random moves
vector<string> randomizeCube(cube &c, int n){
// needs to record the moves made 
// there should not be more that two consecutive moves on the same face
    srand(time(0));
    int randNum;
    vector<string> moves(n);

    int repeatCount = 0;
    int lastMoveIndex = -1; // Initialize to an invalid index
    int lastFaceIndex = -1; // Initialize to an invalid face index

   
    for (int i = 0; i < n; i++){

        int moveIndex;

        while(true){
        randNum = rand() % 12; // generates a random number between 0 and 11
        int currentFaceIndex = moveFaceIndex(randNum);

        bool validMove = true;
        // Check for inverse move
        if(lastMoveIndex != -1 && randNum == inverseMoveIndex(lastMoveIndex)){
            validMove = false;
        }

        // Check for 2 repeats on the same face
        if(currentFaceIndex == lastFaceIndex && repeatCount >= 2){
            validMove = false;
        }

        if(validMove){break;}
        }
        
        switch(randNum){
            case 0:
                moves[i] = "F";
                rotateFrontClockwise(c);
                break;
            case 1:
                moves[i] = "F'";
                rotateFrontCounterclockwise(c);
                break;
            case 2:
                moves[i] = "B";
                rotateBackClockwise(c);
                break;
            case 3:
                moves[i] = "B'";
                rotateBackCounterclockwise(c);
                break;
            case 4:
                moves[i] = "L";
                rotateLeftClockwise(c);
                break;
            case 5:
                moves[i] = "L'";
                rotateLeftCounterclockwise(c);
                break;
            case 6:
                moves[i] = "R";
                rotateRightClockwise(c);
                break;
            case 7:
                moves[i] = "R'"; 
                rotateRightCounterclockwise(c);
                break;
            case 8:
                moves[i] = "D";
                rotateBottomClockwise(c);
                break;
            case 9:
                moves[i] = "D'";
                rotateBottomCounterclockwise(c);
                break;
            case 10:
                moves[i] = "U";
                rotateTopClockwise(c);
                break;
            case 11:
                moves[i] = "U'";
                rotateTopCounterclockwise(c);
                break;
            
        }

        int currentFaceIndex = moveFaceIndex(randNum);
        if(currentFaceIndex == lastFaceIndex){
            repeatCount++;
        } else {
            repeatCount = 1; // reset count for new face
            lastFaceIndex = currentFaceIndex;
        }

        //update last move index
        lastMoveIndex = randNum;
    }
    cout << "The cube has been randomized with the following moves: ";
    // print moves
    for (int i = 0; i < moves.size(); i++) {
        cout << moves[i] << " ";
    }
    cout << endl;
    return moves;
}









// Hueristic functions


// calculates the heuristic value of the cube
int calculateHeuristic(cube &c){
    int misplaced = countMisplaced(c);
    int conflicts = countConflicts(c);

    // reason for dividing misplaced by 2:
    // There will be a ton of misplaced pieces on the cube
    // i don't think that is a good representation of how far the cube is from being solved
    // each move can correct multiple misplaced pieces at once
    // i think the conflicts are much more important to fix on the cube
    return (misplaced/2) + conflicts;
}









// counts the number of misplaced pieces on the cube
int countMisplaced(cube &c){
    int count = 0;

    // compare each face to the solved cube state
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (c.front[i][j] != solvedCube.front[i][j]){
                count++;
            }
            if (c.back[i][j] != solvedCube.back[i][j]){
                count++;
            }
            if (c.left[i][j] != solvedCube.left[i][j]){
                count++;
            }
            if (c.right[i][j] != solvedCube.right[i][j]){
                count++;
            }
            if (c.top[i][j] != solvedCube.top[i][j]){
                count++;
            }
            if (c.bottom[i][j] != solvedCube.bottom[i][j]){
                count++;
            }
        }
    }
    return count;
}









// helper function to count conflicts in a single face
int countConflictsInFace(tile face[3][3]) {
    int conflicts = 0;

    // Go row by row
    for (int row = 0; row < 3; row++) {
        int frequencies[10]; 
        for (int k = 0; k < 10; k++) {
            frequencies[k] = 0; // reset frequencies for each row
        }

        // Count occurrences of each number in this row
        for (int col = 0; col < 3; col++) {
            int num = face[row][col].number;
            if (num >= 1 && num <= 9) {
                frequencies[num]++;
            }
        }

        // Check for duplicates in this row
        for (int k = 1; k <= 9; k++) {
            if (frequencies[k] > 1) {
                conflicts += (frequencies[k] - 1);
            }
        }
    }

    return conflicts;
}









// counts the number of conflicts on the cube
int countConflicts(cube &c){
 int conflicts = 0;

    conflicts += countConflictsInFace(c.front);
    conflicts += countConflictsInFace(c.back);
    conflicts += countConflictsInFace(c.left);
    conflicts += countConflictsInFace(c.right);
    conflicts += countConflictsInFace(c.top);
    conflicts += countConflictsInFace(c.bottom);

 return conflicts;
}
