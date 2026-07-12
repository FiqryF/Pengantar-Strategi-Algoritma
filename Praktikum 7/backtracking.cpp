#include <iostream>

using namespace std;

#define V 5 // Jumlah simpul
int graph[V][V] = {
    {0, 1, 1, 1, 0}, // 0 terhubung dengan 1, 2, 3
    {1, 0, 1, 0, 1}, // 1 terhubung dengan 0, 2, 4
    {1, 1, 0, 0, 0}, // 2 terhubung dengan 0, 1
    {1, 0, 0, 0, 1}, // 3 terhubung dengan 0, 4
    {0, 1, 0, 1, 0}  // 4 terhubung dengan 1, 3
};
int color[V] = {0, 0, 0, 0, 0}; // 0 berarti belum diwarnai

const char *colorNames[] = {"Tidak diwarnai", "Merah", "Hijau", "Biru"};

void printGraph()
{
    cout << "Matriks ketetanggaan graf:" << endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Fungsi untuk cek apakah warna aman
bool isSafe(int v, int c)
{
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Fungsi utama Backtracking
bool graphColoring(int m, int v)
{
    if (v == V)
        return true; // Semua simpul sudah diwarnai

    for (int c = 1; c <= m; c++)
    {
        if (isSafe(v, c))
        {
            color[v] = c;
            if (graphColoring(m, v + 1))
                return true;
            color[v] = 0; // Backtrack
        }
    }
    return false;
}

int main()
{
    int m = 3; // Jumlah warna yang tersedia
    printGraph();

    if (graphColoring(m, 0))
    {
        cout << "Solusi ditemukan!" << endl;
        cout << "Warna setiap simpul:" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << "Simpul " << i << " -> " << colorNames[color[i]] << " (" << color[i] << ")" << endl;
        }
    }
    else
    {
        cout << "Tidak ada solusi." << endl;
    }
    return 0;
}