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
        tl,
        tr,
        br,
        bl
    };
    // 魔術方陣大小
    int n;
    // 填寫方向，分成 tl（左上）、tr（右上）、br（右下）與 bl（左下）
    Direction d = tl;

    int **numPointer;

public:
    MagicSquare(int size) : n(size)
    {
        // 指向陣列的指標
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

    MagicSquare(int size, string direction) : MagicSquare(size)
    {
        this->d = stringToDirection(direction);
    }

    ~MagicSquare()
    {
        for (int i = 0; i < n; i++)
        {
            delete[] numPointer[i];
        }
        delete[] numPointer;
    }

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

    void run()
    {
        // 下一個位置
        int i, j;
        // 預定下一個位置
        int k, l;
        // 如果方向是往左上或是往右上
        if (d == tl || d == tr)
        {
            i = 0;
            j = (n - 1) / 2;
        }
        else
        {
            i = (n - 1);
            j = (n - 1) / 2;
        }

        int value = 0;
        numPointer[i][j] = ++value;

        while (value < n * n)
        {
            switch (d)
            {
            // up left
            case tl:
                k = (i - 1 < 0) ? n - 1 : i - 1;
                l = (j - 1 < 0) ? n - 1 : j - 1;
                if (numPointer[k][l] > 0)
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

    void print()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                stringstream ss;
                ss << setw(4) << left << numPointer[i][j];
                cout << ss.str() << " ";
                ss.clear();
            }
            cout << endl;
        }
    }

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
