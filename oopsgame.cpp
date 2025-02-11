#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;


const int width = 40;
const int height = 20;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

class Food {
public:
    int x, y;

    Food() {
        Respawn();
    }

    void Respawn() {
        x = rand() % width;
        y = rand() % height;
    }
};

class Snake {
private:
    int x, y;
    int TailX[100], TailY[100];
    int ntail;
    eDirection dir;

public:
    Snake() {
        Reset();
    }

    void Reset() {
        x = width / 2;
        y = height / 2;
        ntail = 0;
        dir = STOP;
    }

    void Move() {
        if (dir == STOP) return; 


        int prevX = TailX[0];
        int prevY = TailY[0];
        int prev2X, prev2Y;
        TailX[0] = x;
        TailY[0] = y;

        for (int i = 1; i < ntail; i++) {
            prev2X = TailX[i];
            prev2Y = TailY[i];
            TailX[i] = prevX;
            TailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

       
        switch (dir) {
            case LEFT:  x--; break;
            case RIGHT: x++; break;
            case UP:    y--; break;
            case DOWN:  y++; break;
            default: break;
        }
    }

    bool CheckCollision() {
      
        if (x < 0 || x >= width || y < 0 || y >= height) return true;

        for (int i = 0; i < ntail; i++) {
            if (TailX[i] == x && TailY[i] == y) return true;
        }
        return false;
    }

    void Grow() {
        ntail++;
    }

    void SetDirection(eDirection newDir) {
        if (dir == STOP) { 
            dir = newDir;
            return;
        }
        
   
        if ((dir == LEFT && newDir != RIGHT) ||
            (dir == RIGHT && newDir != LEFT) ||
            (dir == UP && newDir != DOWN) ||
            (dir == DOWN && newDir != UP)) {
            dir = newDir;
        }
    }

    int GetX() { return x; }
    int GetY() { return y; }
    int GetTailLength() { return ntail; }
    int GetTailX(int index) { return TailX[index]; }
    int GetTailY(int index) { return TailY[index]; }
};


class Game {
private:
    bool gameover, paused;
    Snake snake;
    Food food;
    int score;

public:
    Game() {
        gameover = false;
        paused = false;
        score = 0;
    }

    void PlaySoundEffects(int frequency, int duration) {
        Beep(frequency, duration);
    }

    void ShowStartScreen() {
        system("cls");
        cout << "#############################\n";
        cout << "#       SNAKE GAME         #\n";
        cout << "#############################\n";
        cout << "Press ENTER to Start...\n";
        PlaySoundEffects(500, 300);
        while (true) {
            if (_kbhit() && _getch() == 13) {
                break;
            }
        }
    }

    void SetCursorPosition(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void Draw() {
        SetCursorPosition(0, 0);
        
        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "#";
                if (i == snake.GetY() && j == snake.GetX()) cout << "O";
                else if (i == food.y && j == food.x) cout << "F";
                else {
                    bool print = false;
                    for (int k = 0; k < snake.GetTailLength(); k++) {
                        if (snake.GetTailX(k) == j && snake.GetTailY(k) == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print) cout << " ";
                }
                if (j == width - 1) cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
        if (paused) cout << "Game Paused. Press any key to resume...\n";
    }

    void Input() {
        if (_kbhit()) {
            char key = _getch();
            if (paused) {
                paused = false;
            } else {
                switch (key) {
                    case 'a': snake.SetDirection(LEFT); break;
                    case 'd': snake.SetDirection(RIGHT); break;
                    case 'w': snake.SetDirection(UP); break;
                    case 's': snake.SetDirection(DOWN); break;
                    case 'x': gameover = true; break;
                    default: paused = true; break;
                }
            }
        }
    }

    void Logic() {
        if (paused) return;

        snake.Move();

        if (snake.CheckCollision()) {
            gameover = true;
            return;
        }

        if (snake.GetX() == food.x && snake.GetY() == food.y) {
            score += 10;
            food.Respawn();
            snake.Grow();
            PlaySoundEffects(600, 150);
        }
    }

    void ShowGameOverScreen() {
        system("cls");
        cout << "#############################\n";
        cout << "#         GAME OVER        #\n";
        cout << "#############################\n";
        cout << "Final Score: " << score << "\n";
        cout << "Press 'R' to Restart or 'Q' to Quit...\n";
        PlaySoundEffects(400, 500);
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'r' || key == 'R') {
                    Reset();
                    break;
                } else if (key == 'q' || key == 'Q') {
                    exit(0);
                }
            }
        }
    }

    void HideCursor() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    void Reset() {
        gameover = false;
        paused = false;
        score = 0;
        snake.Reset();
        food.Respawn();
    }

    void Run() {
        HideCursor();
        ShowStartScreen();
        Reset();
        while (true) {
            while (!gameover) {
                Draw();
                Input();
                Logic();
                Sleep(200);
            }
            ShowGameOverScreen();
        }
    }
};


int main() {
    Game snakeGame;
    snakeGame.Run();
    return 0;
}
