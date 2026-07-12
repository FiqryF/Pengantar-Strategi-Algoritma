#include <iostream>
using namespace std;

void merge(int arr[], int kiri, int tengah, int kanan)
{
    int i = kiri, j = tengah + 1, k = 0;
    int temp[100];

    while (i <= tengah && j <= kanan)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= tengah)
        temp[k++] = arr[i++];

    while (j <= kanan)
        temp[k++] = arr[j++];

    for (i = kiri, k = 0; i <= kanan; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(int arr[], int kiri, int kanan)
{
    if (kiri < kanan)
    {
        int tengah = (kiri + kanan) / 2;

        mergeSort(arr, kiri, tengah);     
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan); 
    }
}

int main()
{
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;

    int arr[100];

    cout << "Masukkan data:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    mergeSort(arr, 0, n - 1);

    cout << "Hasil setelah diurutkan: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    return 0;
}