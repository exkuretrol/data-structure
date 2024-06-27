#include <iostream>
#include <ctime>
#include <functional>
#include <vector>
#include <algorithm>
#include <chrono>

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
    int range_upper = 1000000;
    int *arr = nullptr;
    int *arr_copy = nullptr;
    int **time_it_table = nullptr;
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
        if (arr != nullptr)
        {
            delete[] arr;
        }

        arr = new int[n * execution_times];
        for (int i = 0; i < n * execution_times; i++)
        {
            arr[i] = range_lower + (rand() % (range_upper - range_lower + 1));
        }
    }

    // get sort algorithm by index
    void run_sort_algorithm_by_index(int i, int len_arr)
    {
        switch (i)
        {
        case 0:
            selection_sort(len_arr);
            break;
        case 1:
            insertion_sort(len_arr);
            break;
        case 2:
            bubble_sort(len_arr);
            break;
        case 3:
            quick_sort_recursive_wrapper(len_arr);
            break;
        case 4:
            quick_sort_iterative(len_arr);
            break;
        case 5:
            merge_sort_recursive_wrapper(len_arr);
            break;
        case 6:
            merge_sort_iterative(len_arr);
            break;
        case 7:
            heap_sort(len_arr);
            break;
        case 8:
            radix_sort(len_arr);
            break;
        default:
            break;
        }
    }

    // # 0 : selection sort
    // given array length len_arr, sort from index 0 to len_arr - 1
    void selection_sort(int arr_len)
    {
        for (int i = 0; i < arr_len - 1; i++)
        {
            int min_idx = i;
            for (int j = i + 1; j < arr_len; j++)
            {
                if (arr_copy[j] < arr_copy[min_idx])
                {
                    min_idx = j;
                }
            }
            swap(arr_copy[i], arr_copy[min_idx]);
        }
    }

    // #1: insertion sort
    void insertion_sort(int arr_len)
    {
        for (int i = 1; i < arr_len; i++)
        {
            int key = arr_copy[i];
            int j = i - 1;
            while (j >= 0 && arr_copy[j] > key)
            {
                arr_copy[j + 1] = arr_copy[j];
                j--;
            }
            arr_copy[j + 1] = key;
        }
    }

    // #2: bubble sort
    void bubble_sort(int arr_len)
    {
        for (int i = 0; i < arr_len - 1; i++)
        {
            for (int j = 0; j < arr_len - i - 1; j++)
            {
                if (arr_copy[j] > arr_copy[j + 1])
                {
                    swap(arr_copy[j], arr_copy[j + 1]);
                }
            }
        }
    }

    // #3: quick sort (resursive)
    void quick_sort_recursive_wrapper(int arr_len)
    {
        quick_sort_recursive(0, arr_len - 1);
    }

    void quick_sort_recursive(int low, int high)
    {
        if (low < high)
        {
            int pi = partition(low, high);
            quick_sort_recursive(low, pi - 1);
            quick_sort_recursive(pi + 1, high);
        }
    }

    int partition(int low, int high)
    {
        int pivot = arr_copy[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr_copy[j] < pivot)
            {
                i++;
                swap(arr_copy[i], arr_copy[j]);
            }
        }
        swap(arr_copy[i + 1], arr_copy[high]);
        return i + 1;
    }

    // #4: quick sort (iterative)
    void quick_sort_iterative(int arr_len)
    {
        int low = 0;
        int high = arr_len - 1;
        vector<int> stack;
        stack.push_back(low);
        stack.push_back(high);

        while (!stack.empty())
        {
            high = stack.back();
            stack.pop_back();
            low = stack.back();
            stack.pop_back();

            int pi = partition(low, high);

            if (pi - 1 > low)
            {
                stack.push_back(low);
                stack.push_back(pi - 1);
            }

            if (pi + 1 < high)
            {
                stack.push_back(pi + 1);
                stack.push_back(high);
            }
        }
    }

    // #5: merge sort (recursive)
    void merge_sort_recursive_wrapper(int arr_len)
    {
        merge_sort_recursive(0, arr_len - 1);
    }

    void merge_sort_recursive(int low, int high)
    {
        if (low < high)
        {
            int mid = low + (high - low) / 2;
            merge_sort_recursive(low, mid);
            merge_sort_recursive(mid + 1, high);
            merge(low, mid, high);
        }
    }

    void merge(int low, int mid, int high)
    {
        int n1 = mid - low + 1;
        int n2 = high - mid;

        int *L = new int[n1];
        int *R = new int[n2];

        for (int i = 0; i < n1; i++)
        {
            L[i] = arr_copy[low + i];
        }

        for (int i = 0; i < n2; i++)
        {
            R[i] = arr_copy[mid + 1 + i];
        }

        int i = 0, j = 0, k = low;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr_copy[k] = L[i];
                i++;
            }
            else
            {
                arr_copy[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            arr_copy[k] = L[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            arr_copy[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    // #6: merge sort (iterative)
    void merge_sort_iterative(int arr_len)
    {
        for (int curr_size = 1; curr_size <= arr_len - 1; curr_size = 2 * curr_size)
        {
            for (int left_start = 0; left_start < arr_len - 1; left_start += 2 * curr_size)
            {
                int mid = min(left_start + curr_size - 1, arr_len - 1);
                int right_end = min(left_start + 2 * curr_size - 1, arr_len - 1);
                merge(left_start, mid, right_end);
            }
        }
    }

    // #7: heap sort
    void heap_sort(int arr_len)
    {
        for (int i = arr_len / 2 - 1; i >= 0; i--)
        {
            heapify(arr_len, i);
        }

        for (int i = arr_len - 1; i > 0; i--)
        {
            swap(arr_copy[0], arr_copy[i]);
            heapify(i, 0);
        }
    }
    void heapify(int arr_len, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < arr_len && arr_copy[left] > arr_copy[largest])
        {
            largest = left;
        }

        if (right < arr_len && arr_copy[right] > arr_copy[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(arr_copy[i], arr_copy[largest]);
            heapify(arr_len, largest);
        }
    }

    // #8: radix sort
    void radix_sort(int arr_len)
    {
        int max_val = *max_element(arr_copy, arr_copy + arr_len);
        for (int exp = 1; max_val / exp > 0; exp *= 10)
        {
            counting_sort(arr_len, exp);
        }
    }

    void counting_sort(int arr_len, int exp)
    {
        int *output = new int[arr_len];
        int count[10] = {0};

        for (int i = 0; i < arr_len; i++)
        {
            count[(arr_copy[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = arr_len - 1; i >= 0; i--)
        {
            output[count[(arr_copy[i] / exp) % 10] - 1] = arr_copy[i];
            count[(arr_copy[i] / exp) % 10]--;
        }

        for (int i = 0; i < arr_len; i++)
        {
            arr_copy[i] = output[i];
        }

        delete[] output;
    }

public:
    Sort(int n = 1000, int times = 10) : n(n), execution_times(times)
    {
        srand(time(0));
        this->set_time_it_table();
    }
    ~Sort()
    {
        delete[] arr;
        for (int i = 0; i < execution_times; i++)
        {
            delete[] time_it_table[i];
        }
        delete[] time_it_table;
    }

    void set_n(int n)
    {
        this->n = n;
    }

    int get_n()
    {
        return n;
    }

    void set_execution_times(int times)
    {
        if (time_it_table != nullptr)
        {
            for (int i = 0; i < execution_times; i++)
            {
                delete[] time_it_table[i];
            }
            delete[] time_it_table;
        }
        this->execution_times = times;
        set_time_it_table();
    }

    int get_execution_times()
    {
        return execution_times;
    }

    void set_range(int lower_bount, int upper_bound)
    {
        this->range_lower = lower_bount;
        this->range_upper = upper_bound;
    }

    tuple<int, int> get_range()
    {
        return make_tuple(range_lower, range_upper);
    }

    void set_sort_alg_active_list(vector<int> alg_list)
    {
        for (int i = 0; i < ALGORITHM_KINDS; i++)
        {
            sort_alg_active_list[i] = alg_list[i];
        }
    }

    vector<int> get_sort_alg_active_list()
    {
        return sort_alg_active_list;
    }

    void execution_sort()
    {
        cout << "generating random array..." << endl;
        this->generate_random_array();
        // empty the time_it_table

        cout << "emptying time_it_table..." << endl;
        for (int i = 0; i < execution_times; i++)
        {
            for (int j = 0; j < ALGORITHM_KINDS; j++)
            {
                time_it_table[i][j] = 0;
            }
        }

        for (int i = 0; i < ALGORITHM_KINDS; i++)
        {
            if (sort_alg_active_list[i] == 1)
            {
                cout << "running sort algorithm ";
                if (i == 0)
                    cout << "selection sort" << endl;
                else if (i == 1)
                    cout << "insertion sort" << endl;
                else if (i == 2)
                    cout << "bubble sort" << endl;
                else if (i == 3)
                    cout << "quick sort (recursive)" << endl;
                else if (i == 4)
                    cout << "quick sort (iterative)" << endl;
                else if (i == 5)
                    cout << "merge sort (recursive)" << endl;
                else if (i == 6)
                    cout << "merge sort (iterative)" << endl;
                else if (i == 7)
                    cout << "heap sort" << endl;
                else if (i == 8)
                    cout << "radix sort" << endl;
                for (int j = 0; j < execution_times; j++)
                {
                    int current_len = n * (j + 1);
                    cout << "\tarray length: " << current_len << endl;
                    arr_copy = new int[current_len];
                    for (int j = 0; j < current_len; j++)
                    {
                        arr_copy[j] = arr[j];
                    }
                    auto start = high_resolution_clock::now();
                    run_sort_algorithm_by_index(i, current_len);
                    auto end = high_resolution_clock::now();
                    cout << "\t\texecution time: " << duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
                    double elapsed_time = duration_cast<chrono::microseconds>(end - start).count();
                    time_it_table[j][i] = elapsed_time;
                    delete[] arr_copy;
                }
            }
        }
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
//     Sort s = Sort();
//     s.execution_sort();

//     vector<vector<int>>
//         tbl = s.get_time_it_table();
//     // output table
//     for (int i = 0; i < tbl.size(); i++)
//     {
//         for (int j = 0; j < tbl[i].size(); j++)
//         {
//             cout << tbl[i][j] << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }