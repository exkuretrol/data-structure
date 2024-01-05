#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Honai
{
private:
    vector<string> records;

public:
    Honai() {};

    /// @brief 三根柱子的河內塔
    /// @param n 層數
    /// @param A 起點
    /// @param B 暫存
    /// @param C 終點

    void run(int n, char A = 'A', char B = 'B', char C = 'C')
    {
        if (n == 0)
            return;
        Honai::run(n - 1, A, C, B);
        string step = "Move disk " + to_string(n) + " from " + A + " to " + C;
        records.push_back(step);
        Honai::run(n - 1, B, A, C);
    }
    /// @brief 輸出
    void print()
    {
        for (int i = 0; i < static_cast<int>(records.size()); i++)
        {
            cout << records[i] << " [" << i << "]" << endl;
        }
    }

    /// @brief 取得所有排列紀錄 vector
    /// @return 排列紀錄 vector
    vector<string> getData()
    {
        return records;
    }
};

// signed main()
// {
//     Honai h = Honai();
//     h.run(3);
//     h.print();
// }