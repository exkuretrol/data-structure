#include <iostream>
#include <ctime>
#include <functional>
#include <vector>

#define ALGORITHM_KINDS 9

using namespace std;
using chrono::duration_cast;
using chrono::high_resolution_clock;
using chrono::microseconds;

class Sort
{
private:
    int n = 1000;
    int execution_times = 10;
    int range_lower = 0;
    int range_upper = 10000;
    int *arr;
    int **time_it_table;
    vector<int> sort_alg_active_list = vector<int>(ALGORITHM_KINDS, 1);

    void set_time_it_table()
    {
        time_it_table = new int *[execution_times];
        for (int i = 0; i < execution_times; i++)
        {
            time_it_table[i] = new int[ALGORITHM_KINDS];
        }
    }

    // generate random array with n elements, each element is in the range [range_lower, range_upper]
    void generate_random_array()
    {
        arr = new int[n * execution_times];
        for (int i = 0; i < n * execution_times; i++)
        {
            arr[i] = range_lower + (rand() % (range_upper - range_lower + 1));
        }

        // Pre-warm the cache
        volatile int temp;
        for (int i = 0; i < n * execution_times; i++)
        {
            temp = arr[i];
        }
    }
    // get sort algorithm by index
    function<void(int)> get_sort_algorithm_by_index(int i)
    {
        switch (i)
        {
        case 0:
            return [this](int x)
            { selection_sort(x); };
        case 1:
            return [this](int x)
            { insertion_sort(x); };
        case 2:
            return [this](int x)
            { bubble_sort(x); };
        case 3:
            return [this](int x)
            { quick_sort_recursive_wrapper(x); };
        case 4:
            return [this](int x)
            { quick_sort_iterative(x); };
        case 5:
            return [this](int x)
            { merge_sort_recursive_wrapper(x); };
        case 6:
            return [this](int x)
            { merge_sort_iterative(x); };
        case 7:
            return [this](int x)
            { heap_sort(x); };
        case 8:
            return [this](int x)
            { radix_sort(x); };
        default:
            return [this](int x)
            { selection_sort(x); };
        }
    }

    // # 0 : selection sort
    // get an input index x, from x, generate start index with x *n, end index with(x + 1) * n void selection_sort(int x)
    void selection_sort(int x)
    {
        for (int i = x * n; i < (x + 1) * n; i++)
        {
            int min_index = i;
            for (int j = i + 1; j < (x + 1) * n; j++)
            {
                if (arr[j] < arr[min_index])
                {
                    min_index = j;
                }
            }
            swap(arr[i], arr[min_index]);
        }
    }

    // #1: insertion sort
    void insertion_sort(int x)
    {
        for (int i = x * n + 1; i < (x + 1) * n; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= x * n && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // #2: bubble sort
    void bubble_sort(int x)
    {
        int lb = x * n;
        int ub = (x + 1) * n - 1;
        bool swapped;
        for (int i = lb; i < ub; i++)
        {
            swapped = false;
            for (int j = lb; j < ub - (i - lb); j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
    }

    // // #3: quick sort (resursive)
    void quick_sort_recursive_wrapper(int x)
    {
        quick_sort_recursive(x, x * n, (x + 1) * n - 1);
    }

    void quick_sort_recursive(int x, int low, int high)
    {
        if (low < high)
        {
            int pi = this->partition(low, high, x);
            quick_sort_recursive(x, low, pi - 1);
            quick_sort_recursive(x, pi + 1, high);
        }
    }

    int partition(int low, int high, int x)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // #4: quick sort (iterative)
    void quick_sort_iterative(int x)
    {
        int low = x * n;
        int high = (x + 1) * n - 1;
        int stack[high - low + 1];
        int top = -1;
        stack[++top] = low;
        stack[++top] = high;
        while (top >= 0)
        {
            high = stack[top--];
            low = stack[top--];
            int pi = this->partition(low, high, x);
            if (pi - 1 > low)
            {
                stack[++top] = low;
                stack[++top] = pi - 1;
            }
            if (pi + 1 < high)
            {
                stack[++top] = pi + 1;
                stack[++top] = high;
            }
        }
    }

    // #5: merge sort (recursive)
    void merge_sort_recursive_wrapper(int x)
    {
        merge_sort_recursive(x, x * n, (x + 1) * n - 1);
    }

    void merge_sort_recursive(int x, int low, int high)
    {
        if (low < high)
        {
            int mid = low + (high - low) / 2;
            merge_sort_recursive(x, low, mid);
            merge_sort_recursive(x, mid + 1, high);
            merge(x, low, mid, high);
        }
    }

    void merge(int x, int low, int mid, int high)
    {
        int n1 = mid - low + 1;
        int n2 = high - mid;
        int L[n1], R[n2];
        for (int i = 0; i < n1; i++)
        {
            L[i] = arr[x * n + low + i];
        }
        for (int j = 0; j < n2; j++)
        {
            R[j] = arr[x * n + mid + 1 + j];
        }
        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[x * n + k] = L[i];
                i++;
            }
            else
            {
                arr[x * n + k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            arr[x * n + k] = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            arr[x * n + k] = R[j];
            j++;
            k++;
        }
    }

    // #6: merge sort (iterative)
    void merge_sort_iterative(int x)
    {
        for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
        {
            for (int low = 0; low < n - 1; low += 2 * curr_size)
            {
                int mid = min(low + curr_size - 1, n - 1);
                int high = min(low + 2 * curr_size - 1, n - 1);
                merge(x, low, mid, high);
            }
        }
    }

    // #7: heap sort
    void heap_sort(int x)
    {
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(x, n, i);
        }
        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[x * n], arr[x * n + i]);
            heapify(x, i, 0);
        }
    }

    void heapify(int x, int n, int i)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[x * n + l] > arr[x * n + largest])
        {
            largest = l;
        }
        if (r < n && arr[x * n + r] > arr[x * n + largest])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(arr[x * n + i], arr[x * n + largest]);
            heapify(x, n, largest);
        }
    }

    // #8: radix sort
    void radix_sort(int x)
    {
        int m = get_max(x);
        for (int exp = 1; m / exp > 0; exp *= 10)
        {
            count_sort(x, exp);
        }
    }

    int get_max(int x)
    {
        int mx = arr[x * n];
        for (int i = x * n + 1; i < (x + 1) * n; i++)
        {
            if (arr[i] > mx)
            {
                mx = arr[i];
            }
        }
        return mx;
    }

    void count_sort(int x, int exp)
    {
        int output[n];
        int count[10] = {0};
        for (int i = x * n; i < (x + 1) * n; i++)
        {
            count[(arr[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }
        for (int i = (x + 1) * n - 1; i >= x * n; i--)
        {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = x * n; i < (x + 1) * n; i++)
        {
            arr[i] = output[i - x * n];
        }
    }

public:
    Sort(int n = 1000, int times = 10) : n(n), execution_times(times)
    {
        srand(time(0));
        this->set_time_it_table();
        this->generate_random_array();
    }
    ~Sort()
    {
        delete[] arr;
        delete[] time_it_table;
    }

    void set_n(int n)
    {
        this->n = n;
        this->generate_random_array();
    }

    void set_execution_times(int times)
    {
        this->execution_times = times;
        this->generate_random_array();
        this->set_time_it_table();
    }

    void set_range(int lower_bount, int upper_bound)
    {
        this->range_lower = lower_bount;
        this->range_upper = upper_bound;
    }

    void set_sort_alg_active_list(vector<int> alg_list)
    {
        for (int i = 0; i < ALGORITHM_KINDS; i++)
        {
            sort_alg_active_list[i] = alg_list[i];
        }
    }

    void execution_sort()
    {
        // empty the time_it_table
        for (int i = 0; i < execution_times; i++)
        {
            for (int j = 0; j < ALGORITHM_KINDS; j++)
            {
                time_it_table[i][j] = 0;
            }
        }

        int *arr_copy = new int[n * execution_times];
        for (int j = 0; j < n * execution_times; j++)
        {
            arr_copy[j] = arr[j];
        }

        for (int i = 0; i < ALGORITHM_KINDS; i++)
        {

            if (sort_alg_active_list[i] == 1)
            {
                for (int j = 0; j < execution_times; j++)
                {
                    auto start = high_resolution_clock::now();
                    get_sort_algorithm_by_index(i)(j);
                    auto end = high_resolution_clock::now();
                    double elapsed_time = duration_cast<chrono::microseconds>(end - start).count();
                    time_it_table[j][i] = elapsed_time;
                }
            }

            for (int j = 0; j < n * execution_times; j++)
            {
                arr[j] = arr_copy[j];
            }
        }
        delete[] arr_copy;
    }

    vector<vector<int>> get_time_it_table()
    {
        vector<vector<int>> res;
        for (int i = 0; i < execution_times; i++)
        {
            vector<int> row;
            for (int j = 0; j < ALGORITHM_KINDS; j++)
            {
                row.push_back(time_it_table[i][j]);
            }
            res.push_back(row);
        }
        return res;
    }
};

// int main()
// {
//     srand(time(0));
//     Sort s = Sort(1000, 5);
//     s.execution_sort();
//     s.print_time_it_table();

//     cout << endl;
//     s.execution_sort();
//     s.print_time_it_table();
//     return 0;
// }