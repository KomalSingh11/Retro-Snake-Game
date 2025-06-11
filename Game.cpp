#include <iostream>
#include <conio.h>
#include <windows.h>0
#include <ctime>

using namespace std;

//initialization
bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
//making the speed constant
const int speed = 100; 

//make a function for coordinates
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//make  a function for adding the color
void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//make a function for target fruit characters
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

//make a function for making the outer boundary
void Draw() {
    gotoxy(0, 0);
    SetColor(9); // Blue color for boundaries
    for (int i = 0; i < width + 2; i++) cout << "_";
    cout << endl;

    for (int i = 0; i < height; i++) {
        SetColor(9);
        cout << "|";
        for (int j = 0; j < width; j++) {
            if (i == y && j == x) {
                SetColor(10);
                cout << "O"; // Snake Head
            }
            else if (i == fruitY && j == fruitX) {
                SetColor(12);
                cout << "*"; // Red colored fruit
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        SetColor(14);
                        cout << "o"; // Tail
                        print = true;
                    }
                }
                if (!print) {
                    SetColor(7);
                    cout << " ";
                }
            }
        }
        SetColor(9);
        cout << "|" << endl;
    }

    SetColor(9);
    for (int i = 0; i < width + 2; i++) cout << "_";
    cout << endl;
    SetColor(15);
    cout << "\nScore: " << score << endl;
}

//make a function for taking the directions
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': if (dir != RIGHT) dir = LEFT; break;
        case 'd': if (dir != LEFT) dir = RIGHT; break;
        case 'w': if (dir != DOWN) dir = UP; break;
        case 's': if (dir != UP) dir = DOWN; break;
        case 'x': gameOver = true; break;
        }
    }
}

//make a function for logic of movement of the snake
void Logic() {
    int prevX = tailX[0], prevY = tailY[0], prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    srand(time(0));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(speed); // Same speed in all directions
    }
    SetColor(12);
    cout << "\nGame Over! Your Score: " << score << "\n";
    SetColor(7);
    return 0;
}