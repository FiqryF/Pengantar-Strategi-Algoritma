# Post-Test Praktikum 6 - Versi Modifikasi

## Soal

1. Terapkan algoritma BFS dan DFS pada graf berarah di Gambar 6.4 mulai dari simpul ke-0 dengan memodifikasi kode tester praktikum BFS dan DFS yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Bentuk Modifikasi

Kode praktikum asli tidak perlu diubah. Untuk post-test, dibuat file baru:

```text
tugas06.cpp
```

Modifikasi dilakukan pada bagian kode tester, yaitu mengganti data graf menjadi graf Gambar 6.4.

Representasi graf yang digunakan adalah **adjacency list**, karena BFS dan DFS bekerja dengan cara membaca daftar tetangga dari node yang sedang dikunjungi.

Pada versi modifikasi ini, posisi node pada grafik juga dibuat berbeda dari tampilan praktikum. Perubahan posisi node hanya mengubah tampilan visual, bukan mengubah adjacency list atau hasil traversal.

## Graf Gambar 6.4

Adjacency list:

```text
0 -> 1, 2, 3
1 -> 4
2 -> 1
3 -> 4, 5
4 -> 5
5 -> 2
```

Jika ditulis sebagai edge:

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

Traversal dimulai dari:

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

## Hasil BFS

BFS mengunjungi node berdasarkan level atau jarak terdekat dari node awal.

Urutan BFS:

```text
0 1 2 3 4 5
```

Penjelasan:

```text
Node 0 dikunjungi lebih dulu.
Tetangga langsung node 0 adalah 1, 2, dan 3.
Setelah itu BFS melanjutkan ke node 4 dan 5.
```

## Hasil DFS

DFS mengunjungi node sedalam mungkin sebelum kembali ke cabang lain.

Urutan DFS:

```text
0 1 4 5 2 3
```

Penjelasan:

```text
DFS mulai dari 0.
Dari 0 masuk ke 1.
Dari 1 masuk ke 4.
Dari 4 masuk ke 5.
Dari 5 masuk ke 2.
Setelah cabang tersebut selesai, DFS kembali dan mengunjungi 3.
```

## Perbandingan dengan Pre-Test

Hasil pre-test:

```text
BFS = 0 1 2 3 4 5
DFS = 0 1 4 5 2 3
```

Hasil program:

```text
BFS = 0 1 2 3 4 5
DFS = 0 1 4 5 2 3
```

Hasil program sama dengan jawaban pre-test.

## Grafik Baru

Grafik baru dibuat melalui file:

```text
tugas06.cpp
tugas06.exe
```

Tampilan grafik menampilkan dua panel:

```text
Panel atas  : BFS
Panel bawah : DFS
```

Warna jalur traversal dibuat berbeda:

```text
BFS = biru muda
DFS = oranye
```

Kedua panel memakai graf yang sama, yaitu graf Gambar 6.4. Perbedaannya ada pada jalur traversal yang di-highlight.

Selain itu, bentuk visual graf dibuat berbeda dari praktikum dengan mengubah posisi node pada tampilan. Walaupun posisi node berbeda, hubungan antar node tetap sama:

```text
0 -> 1, 2, 3
1 -> 4
2 -> 1
3 -> 4, 5
4 -> 5
5 -> 2
```

## Kesimpulan

Post-test Praktikum 6 berhasil dikerjakan dengan memodifikasi kode tester menggunakan adjacency list.

Hasil akhir:

```text
BFS = 0 1 2 3 4 5
DFS = 0 1 4 5 2 3
```

Hasil tersebut sesuai dengan analisis manual pada pre-test.
