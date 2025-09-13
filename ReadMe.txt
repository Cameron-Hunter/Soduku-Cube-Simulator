This software is a simulation of a Sodoku cube and gui for it in a Terminal.

It uses 2 diffrent structures to hold the data. The first struct is a tile struct which holds the number of the tile and the color.
The second data structure is a struct that holds 6 3x3 matrixes of tiles.

The following is the code for the tile struct :
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

The following is the code for the cube struct:
struct cube{
    tile front[3][3];
    tile back[3][3];
    tile left[3][3];
    tile right[3][3];
    tile top[3][3];
    tile bottom[3][3];
};

The Cube is manipulated by inputing Rubix notation in the Terminal.
Rubix notation consits of the following moves:
F, F', B, B', R, R', L, L', U, U', D, D'.
Typing this in the terminal results in that move being made

The gui in the .txt file looks a little diffrent than it does in the terminal. In the terminal the numbers have the colors of the faces in the sodoku.mov 
video in campus.
The following is the output of the gui:
Welcome to the Sodoku Cube Simulator!
Made by Cameron Hunter

         -------
        | 8 1 3 |
        | 4 6 7 |
        | 2 9 5 |
 ------------------------------
| 7 1 8 | 9 5 2 | 4 6 3 | 2 5 9 |
| 2 4 6 | 3 8 1 | 7 5 9 | 1 8 3 |
| 9 3 5 | 6 7 4 | 1 2 8 | 4 7 6 |
 ------------------------------
        | 1 2 8 |
        | 5 3 9 |
        | 7 4 6 |
         -------

The Heuristic value of this cube is: 0

The following options are in Rubix cube notation.
Please select an option:
To randomize the cube, type 'Rand'
To reset the cube and move list, type 'reset'
To rotate the front face clockwise, type 'F'
To rotate the front face counterclockwise, type 'F''
To rotate the back face clockwise, type 'B'
To rotate the back face counterclockwise, type 'B''
To rotate the left face clockwise, type 'L'
To rotate the left face counterclockwise, type 'L''
To rotate the right face clockwise, type 'R'
To rotate the right face counterclockwise, type 'R''
To rotate the top face clockwise, type 'U'
To rotate the top face counterclockwise, type 'U''
To rotate the bottom face clockwise, type 'D'
To rotate the bottom face counterclockwise, type 'D''
To exit, type 'exit'

The randomizer is psuedorandom using the Srand cpp function. It produces a random number and makes a move based off of it if it is a valid move.
Invalid moves are when a move is made more than 2 times in a row and when a move is the inverse of the previous move.
The randomizer takes a user input from the terminal and does that many amount of valid moves. 
The Randomizer function returns a vector of strings of the moves made and displays it on the terminal.

The following is the code for the randomizer and its helper functions to ensure a move is valid:

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

The way you use this randomizer is by typing Rand into the terminal. It then ask for an input on how many moves to make and does that and
displaying those moves on the terminal

My Hueristic function is based on two seperate factors. First finds out how many collisons are on a cube face. A collision is when multiple instances
of the same number is on the same face. My Hueristic is also based on how diffrent it is from the corrected solved state displayed in the sodoku.mov video on 
canvas. These are not weighed equally. The number of collisions are twice as valuable as the diffrences from the main cube. This is due to multiple peices being able
put in the correct spot in one move. 

I learned alot from this first programing assignment. First i learned not to put this off till the last second because if i had to do it over again i would have
done it in python. I am worried i will get points taken off for it being in terminal and that is something that could have been prevented. I also learned 
that you can have diffrent colors for chars in the terminal which is pretty cool. 


How to run this program. 
1. Download these files
2. Put them in a folder
3. Open terminal and go to the file
4. Run this command g++ .\Main.cpp .\cube.cpp -o SodokuCube
5. Run this command after compilation: .\SodokuCube.exe

I did used chat gpt in this assignments. I used chat gpt 5. I used it for producing the diffrent colors in the terminal.
I entered multiple promps here was the first one:
Can you have diffrent colors in a windows terminal using cpp
Chat gpt responded:
Yes — you can absolutely print text in different colors in a Windows terminal (Command Prompt or PowerShell) from C++.

There are a couple of ways to do it:

1. Using ANSI Escape Codes (Windows 10+)

Modern versions of Windows 10 (build 1511 and newer) support ANSI escape codes, just like Linux terminals.
You can print colors with special sequences:

#include <iostream>

int main() {
    // Enable ANSI escape codes for Windows 10+
    // (sometimes required in older versions of Windows 10)
    system(""); 

    std::cout << "\033[31mThis is red text\033[0m\n";
    std::cout << "\033[32mThis is green text\033[0m\n";
    std::cout << "\033[34mThis is blue text\033[0m\n";
    std::cout << "\033[33mThis is yellow text\033[0m\n";
    std::cout << "\033[1;35mThis is bold magenta text\033[0m\n";

    return 0;
}


\033[31m → red foreground

\033[32m → green

\033[33m → yellow

\033[34m → blue

\033[0m → reset to default

2. Using Windows API (SetConsoleTextAttribute)

If you want to be Windows-specific and not rely on ANSI codes:

#include <iostream>
#include <windows.h>

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    setColor(12); // Light red
    std::cout << "This is red text" << std::endl;

    setColor(10); // Light green
    std::cout << "This is green text" << std::endl;

    setColor(14); // Yellow
    std::cout << "This is yellow text" << std::endl;

    setColor(7); // Reset (default grey)
    std::cout << "Back to normal" << std::endl;

    return 0;
}


Common Windows color codes:

0 = Black

7 = Light gray (default)

9 = Light blue

10 = Light green

12 = Light red

14 = Yellow

15 = White

👉 If you want cross-platform portability, I’d recommend ANSI escape codes. If you only care about Windows and want guaranteed compatibility, use SetConsoleTextAttribute.

Do you want me to make you a ready-to-use helper class where you can do something like Color::Red << "text" instead of managing codes manually?


I then asked it this: an you give me the colors for red, yellow, green, orange, and teal

it responded:
Got it 👍

Here’s the breakdown depending on which method you use (ANSI vs. Windows API).
⚠️ Note: Windows console has a limited color palette — only 16 colors with SetConsoleTextAttribute. So colors like orange and teal don’t exist exactly, but we can approximate them. With ANSI escape codes, you get more flexibility (256 colors and even true RGB).

✅ ANSI Escape Codes (Better Color Control)

You can use either basic colors (30–37) or extended 256-color codes.

Basic examples:
std::cout << "\033[31mRed\033[0m\n";     // Red
std::cout << "\033[33mYellow\033[0m\n";  // Yellow
std::cout << "\033[32mGreen\033[0m\n";   // Green

Approximations for Orange and Teal (256-color mode):
std::cout << "\033[38;5;208mOrange\033[0m\n"; // 208 = bright orange
std::cout << "\033[38;5;30mTeal\033[0m\n";    // 30 = teal-like

✅ Windows API SetConsoleTextAttribute

Here are the closest matches:

Red → 12 (Light Red)

Yellow → 14 (Yellow)

Green → 10 (Light Green)

Orange → No true orange, closest is Dark Yellow (6)

Teal → Closest is Cyan (3)

Example:

setColor(12); std::cout << "Red\n";
setColor(14); std::cout << "Yellow\n";
setColor(10); std::cout << "Green\n";
setColor(6);  std::cout << "Orange (approx)\n";
setColor(3);  std::cout << "Teal (approx)\n";
setColor(7);  std::cout << "Back to normal\n";


👉 Question for you: do you want me to give you a ready-to-use table of both ANSI + Windows API codes (so you can easily swap between methods), or just the Windows API version since you’re coding in C++ on Windows?

I additionaly left comments about it in my code.