#include <iostream>
#include <cmath>
using namespace std;

bool isPrima(int x) {
    if(x < 2) return false;
    if(x == 2) return true;
    if(x % 2 == 0) return false;

    for(int i = 3; i <= sqrt(x); i += 2) {
        if(x % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cout << "Masukkan angka: ";
    cin >> n;

    if(isPrima(n))
        cout << "Bilangan prima" << endl;
    else
        cout << "Bukan bilangan prima" << endl;

    return 0;
}