#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

using namespace std;

class ShortestPath
{
private:
    int n;
    int range = 1000;
    int threshold = 1000;
    int wall = 99999;
    bool directed = false;
    vector<vector<int>> W;
    vector<vector<int>> OW;
    vector<vector<int>> A;
    vector<vector<int>> E;
    vector<vector<int>> TC;
    vector<bool> found;
    vector<int> D;
    vector<int> C;
    // vector<vector<int>> W = {
    //     {0, wall, wall, wall, wall, wall, wall, wall},
    //     {300, 0, wall, wall, wall, wall, wall, wall},
    //     {1000, 800, 0, wall, wall, wall, wall, wall},
    //     {wall, wall, 1200, 0, wall, wall, wall, wall},
    //     {wall, wall, wall, 1500, 0, 250, wall, wall},
    //     {wall, wall, wall, 1000, wall, 0, 900, 1400},
    //     {wall, wall, wall, wall, wall, wall, 0, 1000},
    //     {1700, wall, wall, wall, wall, wall, wall, 0}};
    // vector<vector<int>> W = {
    //     {0, 1, wall, wall, wall, wall},
    //     {wall, 0, 1, wall, wall, wall},
    //     {wall, wall, 0, 1, wall, wall},
    //     {wall, wall, wall, 0, 1, wall},
    //     {wall, wall, wall, wall, 0, 1},
    //     {wall, wall, 1, wall, wall, 0}};

    void trace_path(int p) const
    {
        for (int v = 0; v < n; v++)
        {
            stringstream ss;
            cout << "from " << p << " to " << v << endl;
            if (p == v)
            {
                cout << "Same vertex" << endl
                     << endl;
                continue;
            }
            ss << v;
            int b = v, a = E[p][b];
            if (a == wall)
            {
                cout << "No path" << endl
                     << endl;
                continue;
            }
            for (; a != p; b = a, a = E[p][b])
            {
                if (a == wall)
                    break;
                ss.str(to_string(a) + " -- " + to_string(W[a][b]) + " --> " + ss.str());
            }
            if (a == wall)
            {
                cout << "no answer" << endl
                     << endl;
                continue;
            }
            ss.str(to_string(p) + " -- " + to_string(W[p][b]) + " --> " + ss.str());
            cout << ss.str() << endl
                 << endl;
        }
        cout << string(80, '-') << endl
             << endl;
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
        if (ignore_ind == ind)
        {
            for (int i = 0; i < n; i++)
                found[i] = true;
            return -1;
        }
        return ind;
    }

    bool check_all_found() const
    {
        for (bool f : found)
            if (!f)
                return false;
        return true;
    }

    void dijkstra(int u)
    {
        found[u] = true;
        for (int i = 0; i < n; i++)
        {
            D[i] = W[u][i];
            C[i] = u;
        }

        while (not check_all_found())
        {
            int k = get_min_index(u);
            if (k == -1)
                return;
            found[k] = true;

            for (int i = 0; i < n; i++)
            {
                if ((not found[i]) && ((D[k] + W[k][i]) < D[i]))
                {
                    D[i] = D[k] + W[k][i];
                    C[i] = k;
                }
            }
        }
    }

    void all_dijkstra()
    {
        for (int i = 0; i < n; i++)
        {
            C = vector<int>(n);
            D = vector<int>(n);
            found = vector<bool>(n);
            dijkstra(i);
            for (int j = 0; j < n; j++)
            {
                E[i][j] = C[j];
                A[i][j] = D[j];
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (A[i][j] == wall)
                    E[i][j] = wall;
    }

    void transitive_closure()
    {
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    TC[i][j] = (A[i][j] != wall) || ((A[i][k] != wall) && (A[k][j] != wall));
                }
    }

    void update_matrix()
    {
        all_dijkstra();
        transitive_closure();
    }

public:
    ShortestPath(int size = 6) : n(size), W(size, vector<int>(size)), OW(size, vector<int>(size)), A(size, vector<int>(size)), E(size, vector<int>(size)), TC(size, vector<int>(size)), found(size), D(size), C(size)
    {
        srand(time(nullptr));
    }

    ~ShortestPath()
    {
    }

    void set_wall(int w)
    {
        int p_wall = wall;
        wall = w;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (W[i][j] == p_wall)
                    W[i][j] = wall;
                if (OW[i][j] == p_wall)
                    OW[i][j] = wall;
            }
    }

    void set_range(int r)
    {
        range = r;
    }

    void set_threshold(int t)
    {
        W = OW;
        threshold = t;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (W[i][j] > threshold)
                    W[i][j] = wall;
        update_matrix();
    }

    void set_directed(bool b)
    {
        directed = b;
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
                num = num > threshold ? wall : num;
                W[i][j] = num;
                W[j][i] = num;
            }
            if (directed)
            {
                for (int j = 0; j < i; j++)
                {
                    int num = rand() % range + 1;
                    num = num > threshold ? wall : num;
                    W[i][j] = num;
                }
            }
            W[i][i] = 0;
        }
        OW = W;
        update_matrix();
    }

    void dynamic_programming()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                A[i][j] = W[i][j];
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                        continue;
                    if ((A[i][k] + A[k][j]) < A[i][j])
                        A[i][j] = A[i][k] + A[k][j];
                }
    }

    void trace_all_paths() const
    {
        for (int i = 0; i < n; i++)
            trace_path(i);
    }

    vector<vector<int>> get_matrix(string &m) const
    {
        if (m == "weight")
            return this->W;
        else if (m == "distance")
            return this->A;
        else if (m == "vertex")
            return this->E;
        else if (m == "transitive closure")
            return this->TC;
        return vector<vector<int>>();
    }

    void set_matrix(vector<vector<int>> &M)
    {
        W = M;
        update_matrix();
    }

    void print()
    {
        cout << "Weight Matrix "
             << (directed ? "(Directed Graph)" : "(Undirected Graph)")
             << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << W[i][j] << "\t";
            cout << endl;
        }
        cout << endl;

        cout << "Distance Matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << A[i][j] << "\t";
            cout << endl;
        }
        cout << endl;

        cout << "Vertex Matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << E[i][j] << "\t";
            cout << endl;
        }
        cout << endl;

        cout << "Transitive Closure Matrix" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << TC[i][j] << "\t";
            cout << endl;
        }
        cout << endl;
    }
};

// signed main()
// {
//     ShortestPath sp;
//     sp.random_weight_matrix();
//     sp.print();
//     sp.set_threshold(150);
//     sp.print();
// }