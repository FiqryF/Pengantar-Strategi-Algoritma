# Post-Test Praktikum 9 - Algoritma A*

## Soal

1. Terapkan algoritma A* pada graf di Gambar 9.2 untuk mencari rute terpendek dengan memodifikasi kode tester praktikum A* yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Graf yang Digunakan

Graf Gambar 9.2 direpresentasikan menggunakan weighted adjacency list.

```text
0 -> (1, 3), (2, 4), (3, 5)
1 -> (0, 3), (3, 2)
2 -> (0, 4), (4, 4)
3 -> (0, 5), (1, 2), (4, 2)
4 -> (2, 4), (3, 2), (5, 1), (6, 5)
5 -> (4, 1), (6, 3)
6 -> (4, 5), (5, 3)
```

Node awal:

```text
0
```

Node tujuan:

```text
6
```

## Hasil Program

Output program:

```text
Post-Test Praktikum 9
Representasi graf: weighted adjacency list
Final solution = 0 3 4 5 6 = 11
```

Rute yang diperoleh:

```text
0 -> 3 -> 4 -> 5 -> 6
```

Total cost:

```text
5 + 2 + 1 + 3 = 11
```

## Perbandingan dengan Pre-Test

Hasil program sama dengan jawaban pre-test.

```text
Pre-test = 0 -> 3 -> 4 -> 5 -> 6 = 11
Program  = 0 -> 3 -> 4 -> 5 -> 6 = 11
```

## Analisis Perbedaan

Tidak ada perbedaan cost antara hasil pre-test dan hasil program. Keduanya menghasilkan cost minimum `11`.

Pada graf ini terdapat jalur lain yang juga memiliki cost `11`, yaitu:

```text
0 -> 1 -> 3 -> 4 -> 5 -> 6
```

Cost:

```text
3 + 2 + 2 + 1 + 3 = 11
```

Jadi jika program menghasilkan salah satu dari jalur dengan cost `11`, hasil tersebut tetap benar.

## Kesimpulan

Algoritma A* berhasil diterapkan pada graf Gambar 9.2.

Hasil program sama dengan pre-test, yaitu rute minimum dengan total cost:

```text
11
```
