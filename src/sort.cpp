#include <iostream>
#include <vector>
using namespace std;

class Sort
{
    private:
        vector<int> nums;
        int n;
        int range;

    public:
        Sort(int size): n(size) 
        {
            this->range = 1000;
        }
        Sort(int size, int length): Sort(size) 
        {
            this->range = length;
        }
        void print()
        {
            cout << n << " " << range;
        }
};

signed main()
{
    Sort s(5, 4);
    Sort ss(5);
    s.print();
    ss.print();
}