/*
    Main.cpp file for the Sodoku Cube Simulator
    Made by Cameron Hunter
    Programing buddy: Rian Gallagher
    Date Started: September 10, 2025
    Date Finished: 9/12/2025

    This file contains the main function that runs the simulator
    Displays the cube and then takes a user input to manipulate the cube
*/









#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "cube.h"
using namespace std;










int main() {

    int hueristicValue;
    string userInput; 
    cube myCube;
    vector<string> moves;
    vector<string> randomizedMoves;
    resetCube(myCube); // Initialize the cube to the solved state

    cout << "Welcome to the Sodoku Cube Simulator!" << endl;
    cout << "Made by Cameron Hunter"<<endl<<endl;

    while(true){
    
    // print cube 
    printCube(myCube);
    cout << endl;
    // option menu
    hueristicValue = calculateHeuristic(myCube);
    cout<< "The Heuristic value of this cube is: "<<hueristicValue <<endl;
    cout<<endl;

    cout<<"The following options are in Rubix cube notation."<<endl;
    cout << "Please select an option:" << endl;
    cout << "To randomize the cube, type 'Rand'" << endl;
    cout << "To reset the cube and move list, type 'reset'" << endl;
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

    system("cls");
    
    if(userInput == "exit"){
        cout << "Exiting the simulator. Goodbye!" << endl;
        break;
    }
    else if (userInput == "Rand"|| userInput == "rand"){
        int n;
        cout << "How many moves do you want to be executed for the cube to be randomized" << endl;
        cin >> n;
        cout << "Randomizing the cube with " << n << " moves..." << endl;
        // randomize cube with n moves
        resetCube(myCube); // reset cube before randomizing
        moves.clear();
        randomizedMoves.clear();
        randomizedMoves=randomizeCube(myCube, n);
    }
    else if (userInput == "Reset"|| userInput == "reset"){
        cout << "Resetting the cube to the Solved State" << endl;
        // regset cube to solved state
        moves.clear();
        randomizedMoves.clear();
        resetCube(myCube);
    }
    else if (userInput == "F"|| userInput == "f"){
        cout << "Rotating the front face clockwise: F rubix notation" << endl;
        // rotate front face clockwise F Rubix notation
        moves.push_back("F");
        rotateFrontClockwise(myCube);
       
    }
    else if (userInput == "F'"|| userInput == "f'"){
        cout << "Rotated the front face counterclockwise: F' Rubix notation" << endl;
        moves.push_back("F'");
        // rotate front face counterclockwise F' Rubix notation
        rotateFrontCounterclockwise(myCube);
    }
    else if (userInput == "B"|| userInput == "b"){
        cout << "Rotating the back face clockwise: B  Rubix notation" << endl;
        moves.push_back("B");
        // rotate back face clockwise B Rubix notation
        rotateBackClockwise(myCube);
    }
    else if (userInput == "B'"|| userInput == "b'"){
        cout << "Rotating the back face counterclockwise..." << endl;
        moves.push_back("B'");
        // rotate back face counterclockwise B' Rubix notation
        rotateBackCounterclockwise(myCube);
    }
    else if (userInput == "L"|| userInput == "l"){
        cout << "Rotating the left face clockwise..." << endl;
        moves.push_back("L");
        // rotate left face clockwise L Rubix notation
        rotateLeftClockwise(myCube);
    }
    else if (userInput == "L'" || userInput == "l'"){
        cout << "Rotating the left face counterclockwise..." << endl;
        moves.push_back("L'");
        // rotate left face counterclockwise L' Rubix notation
        rotateLeftCounterclockwise(myCube);
    }
    else if (userInput == "R" || userInput == "r"){
        cout << "Rotating the right face clockwise..." << endl;
        moves.push_back("R");
        // rotate right face clockwise R Rubix notation
        rotateRightClockwise(myCube);
    }
    else if (userInput == "R'"|| userInput == "r'"){
        cout << "Rotating the right face counterclockwise..." << endl;
        moves.push_back("R'");
        // rotate right face counterclockwise R' Rubix notation
        rotateRightCounterclockwise(myCube);

    }
    else if (userInput == "U"|| userInput == "u"){
        cout << "Rotating the top face clockwise..." << endl;
        moves.push_back("U");
        // rotate top face clockwise U Rubix notation
        rotateTopClockwise(myCube);
    }
    else if (userInput == "U'"|| userInput == "u'"){
        cout << "Rotating the top face counterclockwise..." << endl;
        moves.push_back("U'");
        // rotate top face counterclockwise U' Rubix notation
        rotateTopCounterclockwise(myCube);
    }
    else if (userInput == "D"|| userInput == "d"){
        cout << "Rotating the bottom face clockwise..." << endl;
        moves.push_back("D");
        // rotate bottom face clockwise D Rubix notation
        rotateBottomClockwise(myCube);
    }
    else if (userInput == "D'"|| userInput == "d'"){
        cout << "Rotating the bottom face counterclockwise..." << endl;
        moves.push_back("D'");
        // rotate bottom face counterclockwise D' Rubix notation
        rotateBottomCounterclockwise(myCube);
    }
    else{
        cout << "Invalid input. Please input a valid option." << endl;
    }

    
    cout<<endl;
    if(randomizedMoves.size()>0){
        cout<<"Randomization moves: ";
        for (int i = 0; i < randomizedMoves.size(); i++){
            cout << randomizedMoves[i] << " ";
        }
        cout<<endl;
    }

    cout<<"Moves made so far: ";
    for (int i = 0; i < moves.size(); i++){
        cout << moves[i] << " ";
    }
    cout<<endl<<endl;
    }
    cout << "Thank you for using the Sodoku Cube Simulator!" << endl;
    cout << "Made by Cameron Hunter" << endl;
    return 0;
}
