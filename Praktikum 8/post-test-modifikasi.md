# Post-Test Praktikum 8 - Branch and Bound TSP

## Soal

1. Terapkan algoritma Branch and Bound pada graf di Gambar 8.3 untuk kasus TSP dengan memodifikasi kode tester praktikum Branch and Bound yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Graf yang Digunakan

Graf Gambar 8.3:

```text
0 - 1 = 25
0 - 2 = 15
0 - 3 = 20
1 - 2 = 35
1 - 3 = 10
2 - 3 = 30
```

Graf direpresentasikan menggunakan weighted adjacency matrix:

```text
    0   1   2   3
0 | 0   25  15  20
1 | 25  0   35  10
2 | 15  35  0   30
3 | 20  10  30  0
```

Dalam kode:

```cpp
int cost[4][4] = {
    {0, 25, 15, 20},
    {25, 0, 35, 10},
    {15, 35, 0, 30},
    {20, 10, 30, 0}
};
```

## Hasil Program

Output program:

```text
Post-Test Praktikum 8
Representasi graf: weighted adjacency matrix
Final solusi = 0 1 3 2 0 = 80
```

Jalur yang diperoleh:

```text
0 - 1 - 3 - 2 - 0
```

Cost:

```text
25 + 10 + 30 + 15 = 80
```

## Perbandingan dengan Pre-Test

Hasil program sama dengan jawaban pre-test.

```text
Pre-test = 0 - 1 - 3 - 2 - 0 = 80
Program  = 0 - 1 - 3 - 2 - 0 = 80
```

## Analisis Perbedaan

Tidak ada perbedaan cost antara hasil manual pada pre-test dan hasil program. Keduanya menghasilkan cost minimum `80`.

Pada kasus TSP, jalur minimum bisa lebih dari satu. Contoh jalur lain dengan cost yang sama:

```text
0 - 2 - 3 - 1 - 0 = 80
0 - 3 - 1 - 2 - 0 = 80
```

Jadi jika program menghasilkan urutan jalur berbeda tetapi cost akhirnya tetap `80`, hasil tersebut tetap valid.

## Kesimpulan

Algoritma Branch and Bound berhasil diterapkan pada graf Gambar 8.3.

Hasil program sama dengan pre-test, yaitu cost minimum:

```text
80
```
