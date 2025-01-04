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

    };

int main()
{
    cout << "hello from mohammed" << endl;
    return 0;
}
 
