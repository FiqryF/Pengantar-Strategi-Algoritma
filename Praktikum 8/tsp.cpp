#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

const int N = 4; // Jumlah kota (sesuai graf 8.3)
int final_res = INT_MAX;
int final_path[N + 1];
bool visited[N];

// Matriks jarak berdasarkan Gambar 8.3
int adj[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

void tsp(int curr_bound, int curr_weight, int level, int curr_path[]) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int final_res_val = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (final_res_val < final_res) {
                final_res = final_res_val;
                for (int i = 0; i < N; i++) final_path[i] = curr_path[i];
                final_path[N] = curr_path[0];
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_weight;
            curr_weight += adj[curr_path[level - 1]][i];

            if (curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                tsp(curr_bound, curr_weight, level + 1, curr_path);
            }

            curr_weight = temp;
            visited[i] = false;
        }
    }
}

int main() {
    int curr_path[N + 1];
    for (int i = 0; i < N; i++) visited[i] = false;

    curr_path[0] = 0;
    visited[0] = true;

    tsp(0, 0, 1, curr_path);

    cout << "Cost Minimum: " << final_res << endl;
    cout << "Jalur: ";
    for (int i = 0; i <= N; i++) cout << final_path[i] << (i == N ? "" : " -> ");
    cout << endl;

    return 0;
}