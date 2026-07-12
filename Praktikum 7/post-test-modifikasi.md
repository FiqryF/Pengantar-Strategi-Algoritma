# Post-Test Praktikum 7 - Backtracking Graph Coloring

## Soal

1. Terapkan algoritma backtracking pada graf di Gambar 7.5 untuk pewarnaan simpul menggunakan 3 warna dengan memodifikasi kode tester praktikum backtracking yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Graf yang Digunakan

Graf Gambar 7.5:

```text
0 - 1
0 - 2
1 - 2
0 - 3
3 - 4
4 - 1
```

Graf direpresentasikan menggunakan adjacency status matrix:

```text
    0 1 2 3 4
0 | 0 1 1 1 0
1 | 1 0 1 0 1
2 | 1 1 0 0 0
3 | 1 0 0 0 1
4 | 0 1 0 1 0
```

Warna yang digunakan:

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

## Perbandingan dengan Pre-Test

Hasil program sama dengan jawaban pre-test.

```text
Pre-test:
0 = Merah
1 = Hijau
2 = Biru
3 = Hijau
4 = Merah

Program:
0 = Merah
1 = Hijau
2 = Biru
3 = Hijau
4 = Merah
```

## Analisis Perbedaan

Tidak ada perbedaan hasil antara jawaban pre-test dan hasil program. Keduanya menghasilkan pewarnaan yang valid.

Node yang bertetangga tidak memiliki warna yang sama:

```text
0 - 1 : Merah dan Hijau
0 - 2 : Merah dan Biru
1 - 2 : Hijau dan Biru
0 - 3 : Merah dan Hijau
3 - 4 : Hijau dan Merah
4 - 1 : Merah dan Hijau
```

## Kesimpulan

Algoritma backtracking berhasil diterapkan untuk pewarnaan graf Gambar 7.5 dengan 3 warna.

Hasil program sama dengan jawaban pre-test dan valid karena tidak ada dua simpul bertetangga yang memiliki warna sama.
