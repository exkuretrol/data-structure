#include <iostream>
#include <vector>
#define maxsize 100
using namespace std;

class Heap
{
private:
    int s, i, n = 0;
    vector<int> heap;

public:
    Heap(int size) : s(size), heap(size) {}

    int insert_heap(int x)
    {
        if (n == s)
        {
            // cout << "heap is full" << endl;
            return -1;
        }
        n++;
        i = n;
        while ((i > 1) && (x > heap[i / 2]))
        {
            heap[i] = heap[i / 2];
            i /= 2;
        }
        heap[i] = x;
        return 0;
    }

    int delete_heap()
    {
        int temp, i, j;
        if (n == 0)
        {
            // cout << "heap is empty" << endl;
            return -1;
        }
        temp = heap[1];
        heap[1] = heap[n];
        n--;
        i = 1;
        while (i <= n / 2)
        {
            if (heap[2 * i] > heap[2 * i + 1])
                j = 2 * i;
            else
                j = 2 * i + 1;
            if (heap[i] > heap[j])
                break;
            swap(heap[i], heap[j]);
            i = j;
        }
        return temp;
    }

    int get_n()
    {
        return n;
    }

    void print()
    {
        for (int i = 1; i <= n; i++)
            cout << ((i == 1) ? "" : "_") << heap[i];
    }
};
