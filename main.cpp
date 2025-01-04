#include<iostream>
using namespace std;
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>


 #define MAXSIZE 100

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}



class Entity {
protected:
    int x, y;

public:
    Entity() : x(0), y(0) {}
    Entity(int x, int y) : x(x), y(y) {}

    void SetPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int GetX() const { return x; }
    int GetY() const { return y; }

    virtual void Draw() = 0; // Pure virtual function for drawing the entity
};



class Fruit : public Entity {
public:
    Fruit() {
        GenerateNewPosition(50, 25); // Initial position
    }

    void Draw() override {
        gotoxy(x, y);
        cout << "F"; // Draw fruit
    }

    void GenerateNewPosition(int width, int height) {
        x = rand() % (width - 2) + 1; // Ensure fruit is within bounds
        y = rand() % (height - 2) + 1;
    }
};

int main()
{
    cout << "hello from mohammed" << endl;
    return 0;
}
 
