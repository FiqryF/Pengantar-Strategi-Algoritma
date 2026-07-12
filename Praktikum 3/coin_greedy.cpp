#include <iostream>
using namespace std;

int main() {
    int A;
    cout << "Masukkan jumlah uang: ";
    cin >> A;

    int C[] = {1000, 500, 200, 100, 50, 20, 10, 5, 1};
    int n = 9;

    int S[100]; 
    int count = 0;
    int total = 0;

    for(int i = 0; i < n; i++) {
        while(total + C[i] <= A) {
            S[count] = C[i];
            total += C[i];
            count++;
        }
    }

    if(total == A) {
        cout << "Koin yang digunakan:\n";
        for(int i = 0; i < count; i++) {
            cout << S[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Tidak ada solusi\n";
    }

    return 0;
}