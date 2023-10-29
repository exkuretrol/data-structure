#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class MagicSquare
{
private:
    enum Direction
    {
        tl, // 往左上
        tr, // 往右上
        br, // 往右下
        bl  // 往左下
    };
    // 魔術方陣大小
    int n;
    // 填寫方向，分成 tl（左上）、tr（右上）、br（右下）與 bl（左下）
    Direction d = tl;

    // 二為動態陣列指標
    int **numPointer;

public:
    /// @brief 魔術方陣建構子，數字填寫方向為往左上
    /// @param size 方陣大小
    MagicSquare(int size) : n(size)
    {
        // 初始化指向陣列的指標 (size 列)
        numPointer = new int *[size];

        // 所指的陣列都指向到一個新的列陣列
        for (int i = 0; i < n; i++)
            numPointer[i] = new int[size];

        // 列
        for (int i = 0; i < n; i++)
            // 欄
            for (int j = 0; j < n; j++)
                // 初始化每個元素
                numPointer[i][j] = 0;
    }

    /// @brief 魔術方陣建構子，同時指定方向
    /// @param size 方陣大小
    /// @param direction 數字填寫方向
    MagicSquare(int size, string direction) : MagicSquare(size)
    {
        this->d = stringToDirection(direction);
    }

    /// @brief 魔術方陣解構子，移除用 new 建立的指標
    ~MagicSquare()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] numPointer[i];
        }
        delete[] numPointer;
    }

    /// @brief 將輸入字串轉為方向
    /// @param input 輸入字串，方陣填寫方向
    /// @return 方向
    Direction stringToDirection(string &input)
    {
        if (input == "tr")
            return tr;
        else if (input == "bl")
            return bl;
        else if (input == "br")
            return br;
        else
            return tl;
    }

    /// @brief 開始遍歷、填寫魔術方陣
    void run()
    {
        // 下一個位置
        int i, j;
        // 預定下一個位置
        int k, l;
        // 如果方向是往左上或是往右上，起始點為最上排列中間
        if (d == tl || d == tr)
        {
            i = 0;
        }
        // 如果方向是往左下或是往右下，起始點為最下排列中間
        else
        {
            i = (n - 1);
        }
        j = (n - 1) / 2;

        // 初始化填入數字
        int value = 0;
        numPointer[i][j] = ++value;

        while (value < n * n)
        {
            switch (d)
            {
            // up left
            case tl:
                // 下一步是否會撞到邊界
                k = (i - 1 < 0) ? n - 1 : i - 1;
                l = (j - 1 < 0) ? n - 1 : j - 1;
                // 如果目的地有數字了
                if (numPointer[k][l] > 0)
                    // 往下位移一格
                    i = (i + 1) % n;
                else
                {
                    i = k;
                    j = l;
                }
                break;
            // up right
            case tr:
                k = (i - 1 < 0) ? n - 1 : i - 1;
                l = (j + 1 == n) ? 0 : j + 1;
                if (numPointer[k][l] > 0)
                    i = (i + 1) % n;
                else
                {
                    i = k;
                    j = l;
                }
                break;
            // bottom right
            case br:
                k = (i + 1 == n) ? 0 : i + 1;
                l = (j + 1 == n) ? 0 : j + 1;
                if (numPointer[k][l] > 0)
                    i = (i - 1 < 0) ? n - 1 : i - 1;
                else
                {
                    i = k;
                    j = l;
                }
                break;
            // bottom left
            case bl:
                k = (i + 1 == n) ? 0 : i + 1;
                l = (j - 1 < 0) ? n - 1 : j - 1;
                if (numPointer[k][l] > 0)
                    i = (i - 1 < 0) ? n - 1 : i - 1;
                else
                {
                    i = k;
                    j = l;
                }
                break;
            }
            numPointer[i][j] = ++value;
        }
    }

    /// @brief 輸出魔術方陣
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 用 stringstream 格式化
                stringstream ss;
                ss << setw(4) << left << numPointer[i][j];
                cout << ss.str() << " ";
                ss.clear();
            }
            cout << endl;
        }
    }

    // 輸出產生的魔術方陣
    vector<vector<int>> getData()
    {
        vector<vector<int>> data(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                data[i][j] = numPointer[i][j];
        return data;
    }
};

// signed main()
// {
//     cout << "tl" << endl;
//     MagicSquare ms(5, "tl");
//     ms.run();
//     ms.print();
//     cout << "tr" << endl;
//     MagicSquare ms1(5, "tr");
//     ms1.run();
//     ms1.print();
//     cout << "bl" << endl;
//     MagicSquare ms2(5, "bl");
//     ms2.run();
//     ms2.print();
//     cout << "br" << endl;
//     MagicSquare ms3(5, "br");
//     ms3.run();
//     ms3.print();
// }
