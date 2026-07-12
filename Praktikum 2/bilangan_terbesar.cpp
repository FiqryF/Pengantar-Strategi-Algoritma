#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Masukkan jumlah elemen: ";
    cin >> n;

    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int maks = a[0];
    for(int i = 1; i < n; i++) {
        if(a[i] > maks) {
            maks = a[i];
        }
    }

    cout << "Elemen terbesar: " << maks << endl;
    return 0;
}