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

using namespace std;



// Definition and initialization
cube solvedCube = {
    // front
    {{9,5,2},{3,8,1},{6,7,4}},
    // back
    {{9,5,2},{3,8,1},{6,7,4}},
    // left
    {{7,1,8},{2,4,6},{9,3,5}},
    // right
    {{4,6,3},{7,5,9},{1,2,8}},
    // top
    {{8,1,3},{4,6,7},{2,9,5}},
    // bottom
    {{1,2,8},{5,3,9},{7,4,6}}
};










// prints the cube in a unfolded layout
void printCube(cube c){
    cout<<"        -------"<<endl;
    // Print top face
    for(int i = 0; i < 3; i++){
        cout << "       | ";
        for(int j = 0; j < 3; j++){
            cout << c.top[i][j] << " ";
        }
        cout <<"|"<< endl;
    }
    cout<<" ------------------------------"<<endl;
    // Print left, front, right, back faces
    for(int i = 0; i < 3; i++){
        cout <<"|";
        //left face
        for (int j = 0; j < 3; j++)
        {
            cout<< c.left[i][j] << " ";
        }
        cout << "| ";
        //Front face
        for(int j = 0; j < 3; j++){
            cout << c.front[i][j] << " ";
        }
        cout << "| ";
        //right Face
        for(int j = 0; j < 3; j++){
            cout << c.right[i][j] << " ";
        }
        cout << "| ";
        //back face
        for(int j = 0; j < 3; j++){
            cout << c.back[i][j] << " ";
        }   
        cout << "| " ;
        cout << endl;
    }
      cout<<" ------------------------------"<<endl;
    // Print bottom face
    for(int i = 0; i < 3; i++){
        cout << "       | ";
        for(int j = 0; j < 3; j++){
            cout << c.bottom[i][j] << " ";
        }
        cout <<"|" <<endl;

    }
     cout<<"        -------"<<endl;
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
    // rotate the front face
    int new_front[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_front[j][2 - i] = c.front[i][j];
        }    
    }    

    memcpy(c.front, new_front, sizeof(new_front));

    // cycle the edge strips
    int temp[3];
    // save bottom row of top
    for (int i = 0; i < 3; i++){
         temp[i] = c.top[2][i];          
    }

    for (int i = 0; i < 3; i++){
        c.top[2][i]    = c.left[2 - i][2]; // top <- left col (reversed)
    }
    for (int i = 0; i < 3; i++){
         c.left[i][2]   = c.bottom[0][i];  // left <- bottom row
    }  
    for (int i = 0; i < 3; i++){
        c.bottom[0][i] = c.right[2 - i][0];// bottom <- right col (reversed)
    }
    for (int i = 0; i < 3; i++){
        c.right[i][0]  = temp[i];          // right <- saved top row
    }     
}









// rotates the front face counter-clockwise
// Rubik's notation: F'
void rotateFrontCounterclockwise(cube &c) {
    // rotate the front face
    int new_front[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_front[2 - j][i] = c.front[i][j];
        }
    }

    memcpy(c.front, new_front, sizeof(new_front));

    // cycle the edge strips (reverse of F)
    int temp[3];
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
    int new_back[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_back[j][2 - i] = c.back[i][j];
        }
    }
    memcpy(c.back, new_back, sizeof(new_back));

    // cycle the adjacent strips
    int temp[3];
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
    int new_back[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_back[2 - j][i] = c.back[i][j];
        }
    }
    memcpy(c.back, new_back, sizeof(new_back));

    // cycle the adjacent strips (reverse of B)
    int temp[3];
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
    int new_left[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_left[j][2 - i] = c.left[i][j];
        }
    }
    memcpy(c.left, new_left, sizeof(new_left));

    // cycle the adjacent strips
    int temp[3];
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
    int new_left[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_left[2 - j][i] = c.left[i][j];
        }
    }

    memcpy(c.left, new_left, sizeof(new_left));

    // cycle the adjacent strips (reverse of L)
    int temp[3];
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
    int new_right[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_right[j][2 - i] = c.right[i][j];
        }
    }
    memcpy(c.right, new_right, sizeof(new_right));

    // cycle the adjacent strips
    int temp[3];
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
    int new_right[3][3];
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            new_right[2 - j][i] = c.right[i][j];
        }
    }
    memcpy(c.right, new_right, sizeof(new_right));

    // cycle the adjacent strips (reverse of R)
    int temp[3];
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
    int new_bottom[3][3];

    // rotate bottom face 90° clockwise
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new_bottom[j][2 - i] = c.bottom[i][j];
        }
    }
    memcpy(c.bottom, new_bottom, sizeof(new_bottom));

    // Save front bottom row
    int temp[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = c.front[2][i];
    }

    // Cycle the rows clockwise
    for (int i = 0; i < 3; i++) {
        int oldRight = c.right[2][i];
        int oldBack  = c.back[2][i];
        int oldLeft  = c.left[2][i];

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
    int new_bottom[3][3];

    // rotate bottom face 90° counter-clockwise
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            new_bottom[2 - j][i] = c.bottom[i][j];
        }
    }
    memcpy(c.bottom, new_bottom, sizeof(new_bottom));

    // Save front bottom row
    int temp[3];
    for (int i = 0; i < 3; i++) {
        temp[i] = c.front[2][i];
    }

    // Cycle the rows counter-clockwise
    for (int i = 0; i < 3; i++) {
        int oldRight = c.right[2][i];
        int oldBack  = c.back[2][i];
        int oldLeft  = c.left[2][i];

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

int new_top [3][3];


for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
        new_top[j][2-i] = c.top[i][j]; // rotate top face clockwise 90
    }
}

memcpy(c.top, new_top, sizeof(new_top));

// Save front top row
int temp[3];
for (int i = 0; i < 3; i++) {
    temp[i] = c.front[0][i];
}

// Cycle the rows clockwise
for (int i = 0; i < 3; i++) {
    int oldRight = c.right[0][i];
    int oldBack = c.back[0][i];
    int oldLeft = c.left[0][i];

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
    int new_top [3][3];

    //rotate top face counterclockwise 90
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            new_top[2-j][i] = c.top[i][j];
        }
    }

    memcpy(c.top, new_top, sizeof(new_top));

    // Save front top row
     int temp[3];
    for (int i = 0; i < 3; i++) {
    temp[i] = c.front[0][i];
   }

    for (int i = 0; i < 3; i++) {

    int oldRight = c.right[0][i];
    int oldBack = c.back[0][i];
    int oldLeft = c.left[0][i];

    c.front[0][i] = oldLeft; // front <- left
    c.left [0][i] = oldBack; // left <- back
    c.back[0][i] = oldRight; // back <- right
    c.right[0][i] = temp[i]; // right <- front
    }
}









// randomizes the cube with n random moves
vector<string> randomizeCube(cube &c, int n){
// needs to record the moves made 
// there should not be more that two consecutive moves on the same face

    int randNum;
    vector<string> moves(n);

    for (int i = 0; i < n; i++){
        randNum = rand() % 12; // generates a random number between 0 and 11
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









// counts the number of conflicts on the cube
// conflicts when the same number apears on the same face
int countConflicts(cube &c){
    int conflicts = 0;
    int frequences[10]; // index 0 unused, numbers 1-9

    // check each face for conflicts
    // front face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.front[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }

    // back face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.back[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }

    // left face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.left[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }

    // right face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.right[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }

    //top face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.top[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }

    // bottom face
    for(int i = 0; i < 3; i++){
        for(int k = 1; k <= 9; k++){
            frequences[k] = 0; // reset frequencies
        }
        for(int j = 0; j < 3; j++){
            frequences[c.left[i][j]]++;
        }
        for(int k = 1; k <= 9; k++){
            if(frequences[k] > 1){
                conflicts += frequences[k] - 1; // each extra occurrence is a conflict
            }
        }
    }
    return conflicts;

}
