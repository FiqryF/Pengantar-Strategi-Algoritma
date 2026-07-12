# Post-Test Praktikum 6 - BFS dan DFS

## Soal

1. Terapkan algoritma BFS dan DFS pada graf berarah di Gambar 6.4 mulai dari simpul ke-0 dengan memodifikasi kode tester praktikum BFS dan DFS yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Graf yang Digunakan

Graf Gambar 6.4 direpresentasikan menggunakan adjacency list.

```text
0 -> 1, 2, 3
1 -> 4
2 -> 1
3 -> 4, 5
4 -> 5
5 -> 2
```

Traversal dimulai dari node:

```text
0
```

## Hasil Program

Output program:

```text
Post-Test Praktikum 6 - Visual Modifikasi
Representasi graf: adjacency list
BFS mulai dari node 0
0 1 2 3 4 5
DFS mulai dari node 0
0 1 4 5 2 3
```

Hasil BFS:

```text
0 1 2 3 4 5
```

Hasil DFS:

```text
0 1 4 5 2 3
```

## Perbandingan dengan Pre-Test

Hasil program sama dengan jawaban pre-test.

```text
Pre-test BFS  = 0 1 2 3 4 5
Program BFS   = 0 1 2 3 4 5

Pre-test DFS  = 0 1 4 5 2 3
Program DFS   = 0 1 4 5 2 3
```

## Perbedaan BFS dan DFS

BFS mengunjungi node berdasarkan level. Dari node `0`, BFS mengunjungi semua tetangga langsung terlebih dahulu, yaitu `1`, `2`, dan `3`, kemudian lanjut ke node berikutnya.

DFS mengunjungi node sedalam mungkin terlebih dahulu. Dari node `0`, DFS masuk ke `1`, lalu `4`, lalu `5`, lalu `2`, sebelum akhirnya kembali dan mengunjungi `3`.

## Kesimpulan

Algoritma BFS dan DFS berhasil diterapkan pada graf Gambar 6.4.

Hasil program:

```text
BFS = 0 1 2 3 4 5
DFS = 0 1 4 5 2 3
```

Hasil tersebut sama dengan hasil analisis manual pada pre-test.
