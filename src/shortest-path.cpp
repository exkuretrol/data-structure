#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class ShortestPath
{
private:
    int n;
    int range;
    int threshold;
    int wall = 99999;
    // vector<vector<int>> W = {
    //     {0, wall, wall, wall, wall, wall, wall, wall},
    //     {300, 0, wall, wall, wall, wall, wall, wall},
    //     {1000, 800, 0, wall, wall, wall, wall, wall},
    //     {wall, wall, 1200, 0, wall, wall, wall, wall},
    //     {wall, wall, wall, 1500, 0, 250, wall, wall},
    //     {wall, wall, wall, 1000, wall, 0, 900, 1400},
    //     {wall, wall, wall, wall, wall, wall, 0, 1400},
    //     {1700, wall, wall, wall, wall, wall, wall, 0}};
    vector<vector<int>> W;
    vector<vector<int>> A;
    vector<bool> found;
    vector<int> D;
    vector<int> C;
    // int

public:
    ShortestPath(int size = 8, int range = 1000, int threshold = 1000, int wall = 99999) : n(size), range(range), threshold(threshold), wall(wall), D(size), C(size), found(size), W(size, vector<int>(size)), A(size, vector<int>(size))
    {
        srand(0);
        random_weight_matrix();

        cout << "Weight Matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << W[i][j] << "\t";
            cout << endl;
        }
        cout << endl;

        dijkstra(0);
        dynamic_programming();
        cout << "Answer Matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << A[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
        // for (int i = 0; i < n; i++)
        // {
        //     dijkstra(i), print();
        //     found = vector<bool>(n);
        //     D = vector<int>(n);
        //     C = vector<int>(n);
        // }
    }

    ~ShortestPath()
    {
    }

    void random_weight_matrix()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (i == j)
                    continue;
                int num = rand() % range + 1;
                W[i][j] = num > threshold ? wall : num;
                W[j][i] = num;
            }
            W[i][i] = wall;
        }
    }

    void dijkstra(int u = 4)
    {
        found[u] = true;
        for (int i = 0; i < n; i++)
        {
            D[i] = W[u][i];
            C[i] = i == u ? -1 : u;
        }

        while (not check_iter_all())
        {
            int k = get_min_index(u);
            found[k] = true;

            cout << "k = " << k << endl;
            print();
            cout << endl
                 << endl;

            for (int i = 0; i < n; i++)
            {
                if ((not found[i]) & ((D[k] + W[k][i]) < D[i]))
                {
                    D[i] = D[k] + W[k][i];
                    C[i] = k;
                }
            }
        }
    }

    void dynamic_programming()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = W[i][j];
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if ((A[i][k] + A[k][j]) < A[i][j])
                        A[i][j] = A[i][k] + A[k][j];
    }

    int get_min_index(int ignore_ind)
    {
        int m = wall;
        int ind = ignore_ind;
        for (int i = 0; i < n; i++)
        {
            if (i == ignore_ind || found[i])
                continue;
            if (D[i] < m)
                m = D[i], ind = i;
        }
        return ind;
    }

    bool check_iter_all()
    {
        for (int i = 0; i < n; i++)
        {
            if (found[i] == false)
                return false;
        }
        return true;
    }

    void print() const
    {

        cout << "Found Array" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << found[i] << "\t";
        }
        cout << endl;

        cout << "D Array" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << D[i] << "\t";
        }
        cout << endl;

        cout << "C Array" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << C[i] << "\t";
        }
        cout << endl;
    }
};

signed main()
{
    ShortestPath sp = ShortestPath();
    sp.print();
}