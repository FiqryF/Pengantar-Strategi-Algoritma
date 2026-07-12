# Post-Test Praktikum 7 - Versi Modifikasi

## Soal

1. Terapkan algoritma backtracking pada graf di Gambar 7.5 untuk pewarnaan simpul menggunakan 3 warna dengan memodifikasi kode tester praktikum backtracking yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Bentuk Modifikasi

Kode praktikum asli tidak perlu diubah. Untuk post-test, dibuat file baru:

```text
tugas.cpp
```

Modifikasi dilakukan dengan mengganti data graf menjadi graf Gambar 7.5 dan menggunakan **adjacency status matrix**.

Adjacency status matrix dipilih karena graph coloring perlu mengecek apakah dua simpul bertetangga sebelum memberi warna.

## Graf Gambar 7.5

Sisi graf:

```text
0 - 1
0 - 2
1 - 2
0 - 3
3 - 4
4 - 1
```

Adjacency status matrix:

```text
    0 1 2 3 4
0 | 0 1 1 1 0
1 | 1 0 1 0 1
2 | 1 1 0 0 0
3 | 1 0 0 0 1
4 | 0 1 0 1 0
```

Dalam kode:

```cpp
int adjStatus[5][5] = {
    {0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1},
    {1, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0}
};
```

## Warna yang Digunakan

```text
1 = Merah
2 = Hijau
3 = Biru
```

## Hasil Program

Output program:

```text
Post-Test Praktikum 7
Representasi graf: adjacency status matrix
Solusi pewarnaannya yaitu:
Node 0 = warna 1
Node 1 = warna 2
Node 2 = warna 3
Node 3 = warna 2
Node 4 = warna 1
```

Dalam bentuk warna:

```text
Node 0 = Merah
Node 1 = Hijau
Node 2 = Biru
Node 3 = Hijau
Node 4 = Merah
```

## Analisis

Hasil program sama dengan jawaban pre-test.

Pengecekan warna dilakukan dengan melihat adjacency status matrix. Jika `adjStatus[node][i] == 1`, maka node tersebut bertetangga dengan node `i`. Warna yang akan dipasang tidak boleh sama dengan warna node tetangganya.

Contoh pengecekan:

```text
Node 2 bertetangga dengan node 0 dan node 1.
Node 0 memakai merah.
Node 1 memakai hijau.
Maka node 2 memakai biru.
```

## Kesimpulan

Post-test Praktikum 7 berhasil dikerjakan dengan memodifikasi kode tester menggunakan adjacency status matrix.

Hasil akhir:

```text
0 = Merah
1 = Hijau
2 = Biru
3 = Hijau
4 = Merah
```

Hasil tersebut valid karena tidak ada dua simpul bertetangga yang memiliki warna sama.
