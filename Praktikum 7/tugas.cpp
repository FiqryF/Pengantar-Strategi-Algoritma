#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Fungsi Boyer-Moore untuk mencari pola (pattern) dalam teks
void boyerMooreSearch(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();
    
    // Tabel 'bad character'
    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) badChar[(int)pat[i]] = i;

    int s = 0; // s adalah pergeseran pola terhadap teks
    while (s <= (n - m)) {
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[s + j]) j--;

        if (j < 0) {
            cout << "Pola ditemukan pada posisi: " << s << endl;
            s += (s + m < n) ? m - badChar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badChar[txt[s + j]]);
        }
    }
}

int main() {
    // Teks dan Pattern sesuai modul praktikum
    string txt = "abacaabacabacababa";
    string pat = "acabaca";
    
    cout << "Teks: " << txt << endl;
    cout << "Pola: " << pat << endl;
    
    boyerMooreSearch(txt, pat);
    
    return 0;
}