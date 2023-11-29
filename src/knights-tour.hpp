#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <unistd.h>
#define possible_directions 8

using namespace std;

/// @brief Warnsdorff's rule
class KnightsTour
{
private:
    /// @brief 棋盤大小
    int n;

    /// @brief 隨機產生始點
    bool random = false;

    /// @brief 預先定義的 x, y 位移
    int move_dx[possible_directions] = {1, 2, 2, 1, -1, -2, -2, -1};
    int move_dy[possible_directions] = {-2, -1, 1, 2, 2, 1, -1, -2};

    /// @brief 整個棋盤
    int **board;

    /// @brief 使用者輸入的 x, y
    int ix = -1;
    int iy = -1;

    /// @brief 產生在數字 0 ~ 棋盤寬度的隨機數
    /// @return 隨機數
    int generate_random_number()
    {
        return rand() % this->n;
    }

    /// @brief 確認 (x, y) 是否在棋盤內，且可以走
    /// @param x 陣列 x
    /// @param y 陣列 y
    /// @return 是否可以佔領
    bool is_safe(int x, int y)
    {
        return (0 <= x && x < n) &&
               (0 <= y && y < n) &&
               board[x][y] == 0;
    }

public:
    /// @brief KnightsTour 建構子，棋盤寬度預設為 10，為正方形
    /// @param size 棋盤寬度
    KnightsTour(int size = 10) : n(size)
    {
        srand(time(nullptr));
        board = new int *[n];

        for (int i = 0; i < n; i++)
            board[i] = new int[n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                board[i][j] = 0;
    }

    KnightsTour(int size, int x, int y) : KnightsTour(size)
    {
        this->ix = x;
        this->iy = y;
    }

    /// @brief 是否隨機
    void toggle_random()
    {
        this->random = !this->random;
    }

    /// @brief 執行函式，呼叫後騎士開始從起始點行走，直到走到終點或是沒有辦法行走。
    /// @return 執行結果
    bool run()
    {
        int x;
        int y;

        // 如果隨機，產生隨機的 x, y
        if (random)
        {
            x = generate_random_number();
            y = generate_random_number();
        }
        // 預設為中心點
        else if (ix == -1 && iy == -1)
        {
            x = n / 2;
            y = x;
        }
        // 使用者輸入
        else
        {
            x = ix;
            y = iy;
        }

        // 棋盤的第一步
        board[x][y] = 1;

        // 棋盤的第二至 n^2 步
        for (int step = 2; step <= n * n; step++)
        {
            vector<int> next_x;
            vector<int> next_y;

            for (int i = 0; i < possible_directions; i++)
            {
                int tx = x + move_dx[i];
                int ty = y + move_dy[i];
                // 如果新的位置可以走，送到 next_x, y 陣列中
                if (is_safe(tx, ty))
                {
                    next_x.push_back(tx);
                    next_y.push_back(ty);
                }
            }

            // 可以走的步數總數
            int next_n = next_x.size();

            // 找不到路徑時結束程式
            if (next_n == 0)
            {
                return false;
            }

            // 初始化 next_move 陣列，記錄可走方位次數用
            vector<int> next_move(next_n);
            // 用前一個 For 迴圈的結果再走下一步
            for (int i = 0; i < next_n; i++)
            {
                for (int j = 0; j < possible_directions; j++)
                {
                    int tx = next_x[i] + move_dx[j];
                    int ty = next_y[i] + move_dy[j];
                    // 如果還是可以走，可走方向次數 + 1
                    if (is_safe(tx, ty))
                    {
                        next_move[i]++;
                    }
                }
            }

            // 最小 index
            int m = 0;

            // 檢查 next_move 中的陣列，選出最小元素的 index
            for (int i = 1; i < next_n; i++)
            {
                if (next_move[i] < next_move[m])
                    m = i;
            }

            // 即為要走的下一步
            x = next_x[m];
            y = next_y[m];

            // 在棋盤上畫上步數
            board[x][y] = step;
        }
        return true;
    }

    /// @brief 印出棋盤
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 用 stringstream 格式化
                stringstream ss;
                ss << setw(4) << left << board[i][j];
                cout << ss.str() << " ";
                ss.clear();
            }
            cout << endl;
        }
    }

    /// @brief 以 vector 回傳資料，python 介接用
    /// @return 棋盤的二維陣列資料
    vector<vector<int>> get_data()
    {
        vector<vector<int>> data(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                data[i][j] = board[i][j];
        return data;
    }
};

// signed main()
// {
//     KnightsTour k(5);
//     k.toggle_random();
//     k.run();
//     k.print();
//     cout << endl;
//     sleep(1);
//     KnightsTour l(5);
//     l.toggle_random();
//     l.run();
//     l.print();
//     cout << endl;
//     sleep(1);
//     KnightsTour m(5);
//     m.toggle_random();
//     m.run();
//     m.print();
// }
