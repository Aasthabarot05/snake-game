#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

class SnakeGame {
private:
    bool gameover;
    bool gamewin;
    const int width;
    const int height;
    int x, y, fruitY, score, fruitX;
    int TailX[100];
    int TailY[100];
    int ntail;
    const int maxTailLength;
    bool paused;

    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

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

    void Setup() {
        gameover = false;
        gamewin = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        score = 0;
        ntail = 0;

        do {
            fruitX = rand() % width;
            fruitY = rand() % height;
        } while (fruitX == x && fruitY == y);
    }

    void SetCursorPosition(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void Draw() {
        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "#"; 
                if (i == y && j == x) cout << "O"; 
                else if (i == fruitY && j == fruitX) cout << "F"; 
                else {
                    bool print = false;
                    for (int k = 0; k < ntail; k++) {
                        if (TailX[k] == j && TailY[k] == i) {
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

        for (int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;

        cout << "Score: " << score << endl;
        if (paused) {
            cout << "Game Paused. Press any key to resume...\n";
        }
        if (gamewin) {
            cout << "You Win! Press 'R' to Restart or 'Q' to Quit...\n";
        }
    }

    void Input() {
        if (_kbhit()) {
            char key = _getch();
            if (paused) {
                paused = false;
            } else {
                switch (key) {
                case 'a':
                    if (dir != RIGHT) 
                        dir = LEFT;
                    break;
                case 'd':
                    if (dir != LEFT) 
                        dir = RIGHT;
                    break;
                case 'w':
                    if (dir != DOWN) 
                        dir = UP;
                    break;
                case 's':
                    if (dir != UP) 
                        dir = DOWN;
                    break;
                case 'x':
                    gameover = true;
                    break;
                default:
                    paused = true;
                    break;
                }
            }
        }
    }

    void Logic() {
        if (paused || gamewin) return;

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
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }

        if (x < 0 || x >= width || y < 0 || y >= height) {
            gameover = true;
            return;
        }

        for (int i = 0; i < ntail; i++) {
            if (TailX[i] == x && TailY[i] == y)
                gameover = true;
        }

        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % width;
            fruitY = rand() % height;
            ntail++;
            PlaySoundEffects(600, 150);
            if (ntail == maxTailLength) {
                gamewin = true;
            }
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
                    Setup();
                    break;
                } else if (key == 'q' || key == 'Q') {
                    exit(0);
                }
            }
        }
    }

    void ShowGameWinScreen() {
        system("cls");
        cout << "#############################\n";
        cout << "#        YOU WIN!          #\n";
        cout << "#############################\n";
        cout << "Final Score: " << score << "\n";
        cout << "Press 'R' to Restart or 'Q' to Quit...\n";
        PlaySoundEffects(700, 500);
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'r' || key == 'R') {
                    Setup();
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

public:
    SnakeGame() : width(40), height(20), maxTailLength(100) {}

    void Run() {
        HideCursor(); 
        ShowStartScreen();
        Setup();
        while (true) {
            while (!gameover && !gamewin) {
                SetCursorPosition(0, 0); 
                Draw();
                Input();
                Logic();
                Sleep(200);
            }
            if (gameover) {
                ShowGameOverScreen();
            } else if (gamewin) {
                ShowGameWinScreen();
            }
        }
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}
