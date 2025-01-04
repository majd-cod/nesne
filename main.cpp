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

class Snake {
private:
    Point* cell[MAXSIZE]; // Array representing the snake's body
    int size;             // Size of the snake
    char dir;             // Current direction
    Fruit fruit;          // Food
    Map gameMap;          // Game map

public:
    int score = 0;

    Snake(int mapWidth, int mapHeight) : gameMap(mapWidth, mapHeight) {
        Reset();
    }

    void Reset() {
        size = 1; // Initial size
        cell[0] = new Point(20, 20); // Initial position
        for (int i = 1; i < MAXSIZE; i++) {
            cell[i] = nullptr;
        }
        score = 0;
        fruit.GenerateNewPosition(gameMap.GetWidth(), gameMap.GetHeight());
        dir = 'h'; // Default direction
    }

    ~Snake() {
        for (int i = 0; i < size; i++) {
            delete cell[i];
        }
    }

    void AddCell(int x, int y) {
        if (size < MAXSIZE) {
            cell[size++] = new Point(x, y);
        }
    }

    void TurnUp() { dir = 'w'; }
    void TurnDown() { dir = 's'; }
    void TurnLeft() { dir = 'a'; }
    void TurnRight() { dir = 'd'; }

    bool isValidPosition() {
        for (int i = 0; i < size; i++) {
            if (cell[i]->GetX() == fruit.GetX() && cell[i]->GetY() == fruit.GetY()) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    cout << "hello from mohammed" << endl;
    return 0;
}