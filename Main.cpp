#include <iostream>
#include <string>
#include "cube.h"
using namespace std;



int main() {

    string userInput;
    cube myCube;
    resetCube(myCube); // Initialize the cube to the solved state

    cout << "Welcome to the Sodoku Cube Simulator!" << endl;
    cout << "Made by Cameron Hunter"<<endl<<endl;

    while(true){
    
    // print cube 
    printCube(myCube);
    cout << endl;
    // option menu
    cout<<"The following options are in Rubix cube notation."<<endl;
    cout << "Please select an option:" << endl;
    cout << "To randomize the cube, type 'Rand'" << endl;
    cout << "To reset the cube, type 'reset'" << endl;
    cout << "To rotate the front face clockwise, type 'F'" << endl;
    cout << "To rotate the front face counterclockwise, type 'F''" << endl;
    cout << "To rotate the back face clockwise, type 'B'" << endl;
    cout << "To rotate the back face counterclockwise, type 'B''" << endl;
    cout << "To rotate the left face clockwise, type 'L'" << endl;
    cout << "To rotate the left face counterclockwise, type 'L''" << endl;
    cout << "To rotate the right face clockwise, type 'R'" << endl;
    cout << "To rotate the right face counterclockwise, type 'R''" << endl;
    cout << "To rotate the top face clockwise, type 'U'" << endl;
    cout << "To rotate the top face counterclockwise, type 'U''" << endl;
    cout << "To rotate the bottom face clockwise, type 'D'" << endl;
    cout << "To rotate the bottom face counterclockwise, type 'D''" << endl;
    cout << "To exit, type 'exit'" << endl;
    
    cin >> userInput;
    if(userInput == "exit"){
        cout << "Exiting the simulator. Goodbye!" << endl;
        break;
    }
    else if (userInput == "Rand"){
        int n;
        cout << "How many moves do you want to be executed for the cube to be randomized" << endl;
        cin >> n;
        cout << "Randomizing the cube with " << n << " moves..." << endl;
        // randomize cube with n moves
        // randomizeCube(cube, n);
    }
    else if (userInput == "reset"){
        cout << "Resetting the cube to the Solved State" << endl;
        // regset cube to solved state
        // resetCube(cube);
    }
    else if (userInput == "F"){
        cout << "Rotating the front face clockwise..." << endl;
        // rotate front face clockwise F Rubix notation
        rotateFrontClockwise(myCube);
        cout<<endl<<endl;
    }
    else if (userInput == "F'"){
        cout << "Rotating the front face counterclockwise..." << endl;
        // rotate front face counterclockwise F' Rubix notation
        rotateFrontCounterclockwise(myCube);
    }
    else if (userInput == "B"){
        cout << "Rotating the back face clockwise..." << endl;
        // rotate back face clockwise B Rubix notation
        // rotateBackClockwise(cube);
    }
    else if (userInput == "B'"){
        cout << "Rotating the back face counterclockwise..." << endl;
        // rotate back face counterclockwise B' Rubix notation
        // rotateBackCounterclockwise(cube);
    }
    else if (userInput == "L"){
        cout << "Rotating the left face clockwise..." << endl;
        // rotate left face clockwise L Rubix notation
        // rotateLeftClockwise(cube);
    }
    else if (userInput == "L'"){
        cout << "Rotating the left face counterclockwise..." << endl;
        // rotate left face counterclockwise L' Rubix notation
        // rotateLeftCounterclockwise(cube);
    }
    else if (userInput == "R"){
        cout << "Rotating the right face clockwise..." << endl;
        // rotate right face clockwise R Rubix notation
        // rotateRightClockwise(cube);
    }
    else if (userInput == "R'"){
        cout << "Rotating the right face counterclockwise..." << endl;
        // rotate right face counterclockwise R' Rubix notation
        // rotateRightCounterclockwise(cube);

    }
    else{
        cout << "Invalid input. Please input a valid option." << endl;
    }

    }
    
   
    return 0;
}
