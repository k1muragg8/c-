#include <iostream>
#include <vector>
#include <conio.h> // For _kbhit() and _getch() (Windows)
//#include <curses.h> // For initscr(), noecho(), cbreak(), keypad(), getch(), printw(), refresh(), endwin() (Linux/macOS)
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <thread>  // For sleep_for
#include <chrono>  // For milliseconds

using namespace std;

// 游戏板尺寸
const int width = 20;
const int height = 20;

// 游戏结束标志
bool gameOver;

// 蛇的位置 (x, y 坐标)
int headX, headY;
vector<pair<int, int>> snakeBody;

// 食物的位置
int foodX, foodY;

// 蛇的移动方向 (0=停止, 1=上, 2=下, 3=左, 4=右)
int direction;

// 分数
int score;

// 函数声明
void Setup();
void Draw();
void Input();
void Logic();

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100)); // 控制游戏速度，单位毫秒
    }
    cout << "Game Over: " << score << endl;
    return 0;
}

// 初始化游戏
void Setup() {
    gameOver = false;
    direction = 0; // 初始停止
    headX = width / 2;
    headY = height / 2;
    snakeBody.clear(); // 清空蛇的身体
    score = 0;

    // 随机生成食物位置
    srand(time(0)); // 设置随机数种子
    foodX = rand() % width;
    foodY = rand() % height;
}

// 绘制游戏界面
void Draw() {
    system("cls"); // 清屏 (Windows)
    // system("clear"); // 清屏 (Linux/macOS)

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // 左边墙壁

            if (i == headY && j == headX)
                cout << "O"; // 蛇头
            else if (i == foodY && j == foodX)
                cout << "F"; // 食物
            else {
                bool isBodyPart = false;
                for (int k = 0; k < snakeBody.size(); k++) {
                    if (snakeBody[k].first == j && snakeBody[k].second == i) {
                        cout << "o"; // 蛇身
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                    cout << " "; // 空格
            }


            if (j == width - 1)
                cout << "#"; // 右边墙壁
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "score: " << score << endl;
}

// 处理用户输入
void Input() {
    if (_kbhit()) { // 检查是否有按键按下 (Windows)
    // if (kbhit()) { // 检查是否有按键按下 (Linux/macOS - 需要 curses.h)
        switch (_getch()) { // 获取按下的按键 (Windows)
        // switch (getch()) { // 获取按下的按键 (Linux/macOS - 需要 curses.h)
            case 'w': // 上
            case 72:  // 上方向键
                if (direction != 2) // 防止反向移动
                    direction = 1;
                break;
            case 's': // 下
            case 80:  // 下方向键
                if (direction != 1) // 防止反向移动
                    direction = 2;
                break;
            case 'a': // 左
            case 75:  // 左方向键
                if (direction != 4) // 防止反向移动
                    direction = 3;
                break;
            case 'd': // 右
            case 77:  // 右方向键
                if (direction != 3) // 防止反向移动
                    direction = 4;
                break;
            case 'x': // 退出游戏
                gameOver = true;
                break;
        }
    }
}

// 游戏逻辑
void Logic() {
    int prevX = snakeBody.empty() ? headX : snakeBody[0].first;
    int prevY = snakeBody.empty() ? headY : snakeBody[0].second;
    int prev2X, prev2Y;
    snakeBody.insert(snakeBody.begin(), make_pair(headX, headY)); // 在蛇身头部添加新的头位置
    snakeBody.pop_back(); // 移除蛇尾，保持蛇身长度不变

    switch (direction) {
        case 1: // 上
            headY--;
            break;
        case 2: // 下
            headY++;
            break;
        case 3: // 左
            headX--;
            break;
        case 4: // 右
            headX++;
            break;
        default:
            break;
    }

    // 边界判断
    if (headX >= width || headX < 0 || headY >= height || headY < 0) {
        gameOver = true; // 撞墙游戏结束
    }

    // 吃到食物
    if (headX == foodX && headY == foodY) {
        score += 10;
        foodX = rand() % width; // 随机生成新的食物位置
        foodY = rand() % height;
        snakeBody.push_back(make_pair(prevX, prevY)); // 蛇身增长
    }

    // 蛇头撞到身体
    for (int i = 0; i < snakeBody.size(); i++) {
        if (snakeBody[i].first == headX && snakeBody[i].second == headY) {
            gameOver = true; // 撞到自己游戏结束
        }
    }
}