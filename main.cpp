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
void Move() {
        system("cls");         // Clear the screen
        gameMap.DrawBorder();  // Draw the borders

        // Display the score at the bottom of the screen
        gotoxy(0, gameMap.GetHeight() + 2); // Position cursor below the map
        cout << "Score: " << score; // Display the current score

        // Move the snake's body
        for (int i = size - 1; i > 0; i--) {
            cell[i]->SetPoint(cell[i - 1]->GetX(), cell[i - 1]->GetY());
        }

        // Move the head
        switch (dir) {
            case 'w': cell[0]->MoveUp(); break;
            case 's': cell[0]->MoveDown(); break;
            case 'a': cell[0]->MoveLeft(); break;
            case 'd': cell[0]->MoveRight(); break;
        }

        // Check if the snake has eaten the fruit
        if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
            AddCell(0, 0);       // Add a new segment to the snake
            score += 10;         // Increment the score by 10
            do {
                fruit.GenerateNewPosition(gameMap.GetWidth(), gameMap.GetHeight());
            } while (!isValidPosition()); // Ensure the fruit is not inside the snake
        }

        // Check for collision with the walls
        if (cell[0]->GetX() <= 0 || cell[0]->GetX() >= gameMap.GetWidth() || 
            cell[0]->GetY() <= 0 || cell[0]->GetY() >= gameMap.GetHeight()) {
            cout << "\nGame Over! You hit the wall.\n";
            AskToContinue();
        }

        // Check for self-collision
        for (int i = 1; i < size; i++) {
            if (cell[0]->GetX() == cell[i]->GetX() && cell[0]->GetY() == cell[i]->GetY()) {
                cout << "\nGame Over! You hit yourself.\n";
                AskToContinue();
            }
        }

        // Draw the snake and the fruit
        for (int i = 0; i < size; i++) {
            cell[i]->Draw();
        }
        fruit.Draw();

        Sleep(100); // Control the speed of the game
    }
     void AskToContinue() {
        char choice;
        cout << "Do you want to continue playing? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            Reset(); // Reset the game state
        } else {
            exit(0); // Exit the game
        }
    }
};


int main()
{
    cout << "hello from mohammed" << endl;
    return 0;
}