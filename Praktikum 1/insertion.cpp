#include <iostream>
using namespace std;

void insertionSort(int A[], int n)
{
    for (int j = 1; j < n; j++)
    {
        int key = A[j];
        int i = j - 1;

        while (i >= 0 && A[i] > key)
        {
            A[i + 1] = A[i];
            i--;
        }

        A[i + 1] = key;
    }
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << A[i];
        if (i < n - 1) cout << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "=== INSERTION SORT ===\n\n";

    cout << "Masukkan jumlah data : ";
    cin >> n;

    int A[100];

    cout << "Masukkan data (" << n << " elemen):\n";
    for (int i = 0; i < n; i++)
    {
        cout << "Data ke-" << i + 1 << " : ";
        cin >> A[i];
    }

    cout << "\nArray sebelum diurutkan : ";
    printArray(A, n);

    insertionSort(A, n);

    cout << "Array setelah diurutkan : ";
    printArray(A, n);

    return 0;
}