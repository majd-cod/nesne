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

class Point : public Entity {
public:
    Point() : Entity(10, 10) {}
    Point(int x, int y) : Entity(x, y) {}

    void MoveUp() { y--; }
    void MoveDown() { y++; }
    void MoveLeft() { x--; }
    void MoveRight() { x++; }

    void Draw() override {
        gotoxy(x, y);
        cout << "*"; // Draw snake segment
    }
};

class Map {
private:
    const int width;
    const int height;

public:
    Map(int w, int h) : width(w), height(h) {}

    void DrawBorder() {
        for (int i = 0; i <= width; i++) {
            gotoxy(i, 0);           // Top border
            cout << "#";
            gotoxy(i, height);      // Bottom border
            cout << "#";
        }
        for (int i = 0; i <= height; i++) {
            gotoxy(0, i);           // Left border
            cout << "#";
            gotoxy(width, i);
            cout << "#";
        }
    }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
};

int main()
{
    cout << "hello from mohammed" << endl;
    return 0;
}
 
