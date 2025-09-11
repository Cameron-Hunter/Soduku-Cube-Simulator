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
void randomizeCube(cube &c, int n);