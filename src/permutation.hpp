#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>
using namespace std;

class Permutation
{
private:
    // TODO: fix warning n, records.size()
    wstring s;
    vector<string> records;
    int n;
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    bool trace = false;
    bool first_run = true;
    int layer = 0;
    int c = 0;

public:
    /// @brief 建構子；將字串建立
    /// @param input 輸入字串
    Permutation(string input)
    {
        s = converter.from_bytes(input);
        n = s.length();
        records.clear();
    }

    /// @brief 建構子；使用字典序的數字長度作為字串
    /// @param length 字典序英文長度
    Permutation(int length)
    {
        string input = "";
        for (int i = 0; i < length; i++)
        {
            input += i + 'A';
        }

        s = converter.from_bytes(input);
        n = s.length();
        records.clear();
    }

    /// @brief 建構子；預設使用 ABCD 當作排列元素
    Permutation() : Permutation(4) {}

    /// @brief 解構子
    ~Permutation()
    {
    }

    /// @brief 格式化紀錄字串
    /// @param k 排列起點
    /// @param n 總長
    /// @param i k 的遞增索引
    /// @return 格式化後的字串
    string trace_format(int k, int n, int i)
    {
        string sk = to_string(k);
        string sn = to_string(n);
        string si = to_string(i);
        string ss = converter.to_bytes(s);
        if (k == n - 1)
            return "==> (k, n) = (" + sk + ", " + sn + ")! k == n - 1 print!!";
        return "i = " + si + ", (k, n) = (" + sk + ", " + sn + "), swap[k, x] = [" + sk + ", " + si + "], list[] = " + ss;
    }

    /// @brief 排列，產生 c[k], ..., c[n - 1] 的所有排列，並儲存至 vector<string> 中
    /// @param k 起點
    void run(int k)
    {
        // 每呼叫一次增加
        layer++;
        // boundary condition
        if (k == n - 1)
        {
            string perm = converter.to_bytes(s);
            if (trace)
            {
                string ss = string(layer, '\t') + trace_format(k, n, 0);
                records.push_back(ss);
            }
            records.push_back(perm + " [" + to_string(c++) + "]");
        }
        else
        {
            for (int i = k; i < n; i++)
            {
                swap(s[k], s[i]);
                if (trace)
                {
                    string record = string(layer, '\t') + "> " + trace_format(k, n, i);
                    if (first_run)
                        record = "algorithm permutation start. (k, n) = (" + to_string(k) + ", " + to_string(n) + ") \n" + record, first_run = !first_run;
                    records.push_back(record);
                }
                // c[k] ~ c[n - 1] 輪流當 c[k]
                // 換下一位數，產生 s[k + 1] ~ s[n - 1] 所有的排列
                Permutation::run(k + 1);
                // 換完要換回來
                swap(s[k], s[i]);
                if (trace)
                {
                    string record = string(layer, '\t') + "< " + trace_format(k, n, i);
                    records.push_back(record);
                }
            }
        }
        // 每退出一次減少
        layer--;
    }

    /// @brief 觸發 trace
    void toggleTrace()
    {
        trace = !trace;
    }

    /// @brief 輸出
    void print()
    {
        for (int i = 0; i < static_cast<int>(records.size()); i++)
        {
            cout << records[i] << endl;
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
//     Permutation perm2(5);
//     perm2.toggleTrace();
//     perm2.run(0);
//     perm2.print();

//     return 0;
// }