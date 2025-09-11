#include <iostream>
#include "cube.h"
#include <random>
#include <string>
#include <vector>

using namespace std;


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
void resetCube(cube &c){
    cube resetCube;

    // solved state of the cube 
    //from canvas SodokuCube.mov file
    int front[3][3] = {{9,5,2},{3,8,1},{6,7,4}};
    int right[3][3] = {{4,6,3},{7,5,9},{1,2,8}};
    int back[3][3] =  {{9,5,2},{3,8,1},{6,7,4}};
    int left[3][3] =  {{7,1,8},{2,4,6},{9,3,5}};
    int top[3][3] =   {{8,1,3},{4,6,7},{2,9,5}};
    int bottom[3][3] = {{1,2,8},{5,3,9},{7,4,6}};

    memcpy(c.front,  front,  sizeof(front));
    memcpy(c.right,  right,  sizeof(right));
    memcpy(c.back,   back,   sizeof(back));
    memcpy(c.left,   left,   sizeof(left));
    memcpy(c.top,    top,    sizeof(top));
    memcpy(c.bottom, bottom, sizeof(bottom));
}




// makes the F rotation on the cube
void rotateFrontClockwise(cube &c){

// temporary arrays to hold new face values
int new_front [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_right [3][3];


//Front face rotation shenanigans
//front top row becomes left col reversed
new_front[0][0] = c.front[2][0];
new_front[0][1] = c.front[1][0];
new_front[0][2] = c.front[0][0];

//new front middle row
new_front[1][0] = c.front[2][1];
new_front[1][1] = c.front[1][1];
new_front[1][2] = c.front[0][1];

//new front bottom row
new_front[2][0] = c.front[2][2];
new_front[2][1] = c.front[1][2];
new_front[2][2] = c.front[0][2];

//Top face rotation shenanigans
//top two rows stay the same 
for(int i = 0; i < 2; i++){
    for(int j = 0; j < 3; j++){
        new_top[i][j] = c.top[i][j];
    }
}
//top face bottom row becomes left face right col reversed
new_top[2][0] = c.left[2][2];
new_top[2][1] = c.left[1][2];
new_top[2][2] = c.left[0][2];

//left face rotation shenanigans
//left face left col + middle col stays the same
for(int i = 0; i < 3; i++){
    new_left[i][0] = c.left[i][0];
    new_left[i][1] = c.left[i][1];
}
//left face right col becomes bottom face top row
new_left[0][2] = c.bottom[0][0];
new_left[1][2] = c.bottom[0][1];
new_left[2][2] = c.bottom[0][2];

//bottom face rotation shenanigans
//bottom face middle and bottom row stays the same
for(int i = 1; i < 3; i++){
    for(int j = 0; j < 3; j++){
        new_bottom[i][j] = c.bottom[i][j];
    }
}
//bottom face top row becomes right face left col
new_bottom[0][0] = c.right[2][0];
new_bottom[0][1] = c.right[1][0];
new_bottom[0][2] = c.right[0][0];

//right face rotation shenanigans

//right face middle and right col stays the same
for(int i = 0; i < 3; i++){
    new_right[i][1] = c.right[i][1];
    new_right[i][2] = c.right[i][2];
    }

//right face left col becomes top face bottom row reversed
new_right[0][0] = c.top[2][0];
new_right[1][0] = c.top[2][1];
new_right[2][0] = c.top[2][2];

//copy new arrays back to cube
memcpy(c.front,  new_front,  sizeof(new_front));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.right,  new_right,  sizeof(new_right));

}




// makes the F' rotation on the cube
void rotateFrontCounterclockwise(cube &c){
// temporary arrays to hold new face values
int new_front [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_right [3][3];


//Front face rotation shenanigans
//front top row becomes left col reversed
new_front[0][0] = c.front[2][0];
new_front[0][1] = c.front[1][0];
new_front[0][2] = c.front[0][0];

//new front middle row
new_front[1][0] = c.front[2][1];
new_front[1][1] = c.front[1][1];
new_front[1][2] = c.front[0][1];

//new front bottom row
new_front[2][0] = c.front[2][2];
new_front[2][1] = c.front[1][2];
new_front[2][2] = c.front[0][2];

//Top face rotation shenanigans
//top two rows stay the same 
for(int i = 0; i < 2; i++){
    for(int j = 0; j < 3; j++){
        new_top[i][j] = c.top[i][j];
    }
}
//top face bottom row becomes left face right col reversed
new_top[2][0]=c.right[0][0];
new_top[2][1]=c.right[1][0];
new_top[2][2]=c.right[2][0];

//left face rotation shenanigans
//left face left col + middle col stays the same
for(int i = 0; i < 3; i++){
    new_left[i][0] = c.left[i][0];
    new_left[i][1] = c.left[i][1];
}
//left face right col becomes bottom face top row
new_left[0][2] = c.top[2][2];
new_left[1][2] = c.top[2][1];
new_left[2][2] = c.top[2][0];

//bottom face rotation shenanigans
//bottom face middle and bottom row stays the same
for(int i = 1; i < 3; i++){
    for(int j = 0; j < 3; j++){
        new_bottom[i][j] = c.bottom[i][j];
    }
}

//bottom face top row becomes right face left col
new_bottom[0][0] = c.left[0][2];
new_bottom[0][1] = c.left[1][2];
new_bottom[0][2] = c.left[2][2];

//right face rotation shenanigans
//right face middle and right col stays the same
for(int i = 0; i < 3; i++){
    new_right[i][1] = c.right[i][1];
    new_right[i][2] = c.right[i][2];
    }

//right face left col becomes top face bottom row reversed
new_right[0][0] = c.bottom[0][2];
new_right[1][0] = c.bottom[0][1];
new_right[2][0] = c.bottom[0][0];

//copy new arrays back to cube
memcpy(c.front,  new_front,  sizeof(new_front));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.right,  new_right,  sizeof(new_right));

}




// makes the B rotation on the cube
void rotateBackClockwise(cube &c)  {
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_right [3][3];

//Back face rotation shenanigans

//Top face rotation shenanigans

//left face rotation shenanigans

//bottom face rotation shenanigans

//right face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,  new_back,  sizeof(new_back));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.right,  new_right,  sizeof(new_right));
}

// makes the B' rotation on the cube
void rotateBackCounterClockwise(cube &c)  {
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_right [3][3];

//Back face rotation shenanigans

//Top face rotation shenanigans

//left face rotation shenanigans

//bottom face rotation shenanigans

//right face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,  new_back,  sizeof(new_back));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.right,  new_right,  sizeof(new_right));


}




// makes the L rotation on the cube
void rotateLeftClockwise(cube &c){
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,  new_back,  sizeof(new_back));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.front,  new_front,  sizeof(new_front));
}




// makes the L' rotation on the cube
void rotateLeftCounterclockwise(cube &c){
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,  new_back,  sizeof(new_back));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.front,  new_front,  sizeof(new_front));
}




// makes the R rotation on the cube
void rotateRightClockwise(cube &c){
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_right [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,   new_back,   sizeof(new_back));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.right,  new_right,  sizeof(new_right));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.front,  new_front,  sizeof(new_front));
}




// makes the R' rotation on the cube
void rotateRightCounterclockwise(cube &c){
int new_back [3][3];
int new_top [3][3];
int new_bottom [3][3];
int new_right [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,    new_back,    sizeof(new_back));
memcpy(c.top,     new_top,     sizeof(new_top));
memcpy(c.right,   new_right,   sizeof(new_right));
memcpy(c.bottom,  new_bottom,  sizeof(new_bottom));
memcpy(c.front,   new_front,   sizeof(new_front));
}




void rotateBottomClockwise(cube &c){
int new_back [3][3];
int new_right [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,   new_back,   sizeof(new_back));
memcpy(c.right,  new_right,  sizeof(new_right));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.front,  new_front,  sizeof(new_front));
}




void rotateBottomCounterclockwise(cube &c){
int new_back [3][3];
int new_right [3][3];
int new_bottom [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,   new_back,   sizeof(new_back));
memcpy(c.right,  new_right,  sizeof(new_right));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.bottom, new_bottom, sizeof(new_bottom));
memcpy(c.front,  new_front,  sizeof(new_front));
}




void rotateTopClockwise(cube &c){
int new_back [3][3];
int new_right [3][3];
int new_top [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,   new_back,   sizeof(new_back));
memcpy(c.right,  new_right,  sizeof(new_right));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.front,  new_front,  sizeof(new_front));
}




void rotateTopCounterclockwise(cube &c){
int new_back [3][3];
int new_right [3][3];
int new_top [3][3];
int new_left [3][3];
int new_front [3][3];

//left face rotation shenanigans

//front rotation shenanigans

//back face rotation shenanigans

//bottom face rotation shenanigans

//top face rotation shenanigans


//copy new arrays back to cube
memcpy(c.back,   new_back,   sizeof(new_back));
memcpy(c.right,  new_right,  sizeof(new_right));
memcpy(c.left,   new_left,   sizeof(new_left));
memcpy(c.top,    new_top,    sizeof(new_top));
memcpy(c.front,  new_front,  sizeof(new_front));
}




// randomizes the cube with n random moves
void randomizeCube(cube &c, int n){
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
                rotateBackCounterClockwise(c);
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
    for (int i = 0; i < n; i++){
        cout << moves[i] << " ";
    }

}