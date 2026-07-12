# Post-Test Praktikum 6 - BFS dan DFS

## Soal

1. Terapkan algoritma BFS dan DFS pada graf berarah di Gambar 6.4 mulai dari simpul ke-0 dengan memodifikasi kode tester praktikum BFS dan DFS yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## 1. Penerapan BFS dan DFS

Kode tester dimodifikasi agar graf yang digunakan sesuai dengan Gambar 6.4.

Edge yang dimasukkan ke program:

```text
0 -> 1
0 -> 2
0 -> 3
1 -> 4
2 -> 1
3 -> 4
3 -> 5
4 -> 5
5 -> 2
```

Traversal dimulai dari node:

```text
0
```

## Hasil Program BFS

Output program:

```text
BFS mulai dari node 0
0 1 2 3 4 5
```

Jadi hasil BFS adalah:

```text
0 -> 1 -> 2 -> 3 -> 4 -> 5
```

## Hasil Program DFS

Output program:

```text
DFS mulai dari node 0
0 1 4 5 2 3
```

Jadi hasil DFS adalah:

```text
0 -> 1 -> 4 -> 5 -> 2 -> 3
```

## 2. Analisis Perbandingan dengan Pre-Test

Hasil program BFS:

```text
0 1 2 3 4 5
```

Hasil pre-test BFS:

```text
0 1 2 3 4 5
```

Hasil program DFS:

```text
0 1 4 5 2 3
```

Hasil pre-test DFS:

```text
0 1 4 5 2 3
```

Berdasarkan perbandingan tersebut, hasil program sama dengan jawaban pre-test.

## Kesimpulan

Algoritma BFS dan DFS berhasil diterapkan pada graf berarah Gambar 6.4.

BFS menghasilkan urutan:

```text
0 1 2 3 4 5
```

DFS menghasilkan urutan:

```text
0 1 4 5 2 3
```

Hasil program sesuai dengan analisis manual pada pre-test.
