# Praktikum 7 - Post Test / Tugas 7.6

## Soal

1. Terapkan algoritma backtracking pada graf di Gambar 7.5 untuk pewarnaan simpul menggunakan 3 warna dengan memodifikasi kode tester praktikum backtracking yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Modifikasi Kode Tester

Kode tester dimodifikasi pada bagian inisialisasi graf dan jumlah warna.

Graf yang digunakan adalah graf Gambar 7.5:

```text
0 - 1
0 - 2
1 - 2
0 - 3
3 - 4
4 - 1
```

Jumlah warna:

```text
3 warna
1 = Merah
2 = Hijau
3 = Biru
```

## Hasil Program

Hasil yang diperoleh dari program:

```text
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

Node `0` diberi warna merah. Karena node `1`, `2`, dan `3` bertetangga dengan node `0`, maka node-node tersebut tidak boleh menggunakan warna merah secara bersamaan dengan node `0`.

Node `1` diberi warna hijau. Node `2` bertetangga dengan node `0` dan node `1`, sehingga node `2` harus memakai warna yang berbeda dari keduanya, yaitu biru.

Node `3` bertetangga dengan node `0`, sehingga node `3` tidak boleh merah dan dapat memakai hijau.

Node `4` bertetangga dengan node `3` dan node `1`. Karena node `3` dan node `1` memakai hijau, maka node `4` tidak boleh hijau. Node `4` dapat memakai merah.

## Kesimpulan

Program berhasil menerapkan algoritma backtracking untuk pewarnaan graf Gambar 7.5 menggunakan 3 warna.

Hasil program:

```text
0 = Merah
1 = Hijau
2 = Biru
3 = Hijau
4 = Merah
```

Hasil tersebut valid karena tidak ada node bertetangga yang memiliki warna sama.
