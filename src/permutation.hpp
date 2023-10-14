#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>
using namespace std;

class Permutation
{
private:
    wstring s;
    vector<string> records;
    int n;
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    bool trace = false;

public:
    /// @brief 建構子；將字串建立
    /// @param input 輸入字串
    Permutation(string input)
    {
        s = converter.from_bytes(input);
        n = s.length();
        records.clear();
    }

    Permutation(int length)
    {
        string input = "";
        for (int i = 0; i < length; i ++)
        {
            input += i + 'A';
        }
        
        s = converter.from_bytes(input);
        n = s.length();
        records.clear();
    }

    /// @brief 建構子；預設使用 ABCD 當作排列元素
    Permutation() : Permutation("ABCD") {}

    /// @brief 解構子
    ~Permutation()
    {
    }

    /// @brief 排列，產生 c[k], ..., c[n - 1] 的所有排列，並儲存至 vector<string> 中
    /// @param k 起點
    void run(int k)
    {
        // boundary condition
        if (k == n - 1)
        {
            string ss = converter.to_bytes(s);
            records.push_back(ss);
        }
        else
        {
            for (int i = k; i < n; i++)
            {
                // c[k] ~ c[n - 1] 輪流當 c[k]
                swap(s[k], s[i]);
                // 換下一位數，產生 s[k + 1] ~ s[n - 1] 所有的排列
                Permutation::run(k + 1);
                // 換完要換回來
                swap(s[k], s[i]);
            }
        }
    }

    /// @brief 觸發 trace
    void toggleTrace()
    {
        trace = !trace;
    }

    /// @brief 輸出
    void print()
    {
        for (int i = 0; i < records.size(); i++)
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
//     Permutation perm2(3);
//     perm2.run(0);
//     perm2.print();

//     return 0;
// }