#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int N = 4; // Jumlah kota di Gambar 8.3
int final_res = INT_MAX;
int final_path[N + 1];
bool visited[N];

// Matriks jarak Gambar 8.3
int adj[N][N] = {
    {0, 10, 15, 20},
    {10, 0, 35, 25},
    {15, 35, 0, 30},
    {20, 25, 30, 0}
};

void tsp(int curr_weight, int level, int curr_path[]) {
    // Basis rekursi: semua kota dikunjungi
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int total_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (total_res < final_res) {
                final_res = total_res;
                for (int i = 0; i < N; i++) final_path[i] = curr_path[i];
                final_path[N] = curr_path[0];
            }
        }
        return;
    }

    // Branching
    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp_weight = curr_weight + adj[curr_path[level - 1]][i];
            
            // Bounding: Hanya lanjut jika belum melebihi solusi terbaik
            if (temp_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                tsp(temp_weight, level + 1, curr_path);
                visited[i] = false; // Backtrack
            }
        }
    }
}

int main() {
    int curr_path[N + 1];
    fill(visited, visited + N, false);
    curr_path[0] = 0;
    visited[0] = true;

    tsp(0, 1, curr_path);

    cout << "Cost Minimum: " << final_res << endl;
    cout << "Jalur: ";
    for (int i = 0; i <= N; i++) cout << final_path[i] << (i == N ? "" : " -> ");
    return 0;
}