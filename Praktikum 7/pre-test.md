# Praktikum 7 - Pre Test

## Soal

Analisis graf pada Gambar 7.5 dan tuliskan satu cara urutan pewarnaan simpul yang mungkin secara manual dengan algoritma Backtracking apabila menggunakan 3 warna: merah, hijau, dan biru.

## Graf Gambar 7.5

Node yang digunakan:

```text
0, 1, 2, 3, 4
```

Sisi graf:

```text
0 - 1
0 - 2
1 - 2
0 - 3
3 - 4
4 - 1
```

## Aturan Pewarnaan

Dua simpul yang bertetangga tidak boleh memiliki warna yang sama.

Warna yang digunakan:

```text
1 = Merah
2 = Hijau
3 = Biru
```

## Analisis Manual dengan Backtracking

Pewarnaan dimulai dari node `0`, lalu dilanjutkan ke node berikutnya.

1. Node `0` diberi warna merah.
2. Node `1` bertetangga dengan node `0`, maka node `1` tidak boleh merah. Node `1` diberi warna hijau.
3. Node `2` bertetangga dengan node `0` dan node `1`, maka node `2` tidak boleh merah atau hijau. Node `2` diberi warna biru.
4. Node `3` bertetangga dengan node `0`, maka node `3` tidak boleh merah. Node `3` diberi warna hijau.
5. Node `4` bertetangga dengan node `3` dan node `1`, maka node `4` tidak boleh hijau. Node `4` dapat diberi warna merah.

## Hasil Pewarnaan

Salah satu solusi pewarnaan yang valid:

```text
Node 0 = Merah
Node 1 = Hijau
Node 2 = Biru
Node 3 = Hijau
Node 4 = Merah
```

Dalam bentuk angka:

```text
0 = 1
1 = 2
2 = 3
3 = 2
4 = 1
```

## Kesimpulan

Graf pada Gambar 7.5 dapat diwarnai menggunakan 3 warna. Hasil di atas valid karena tidak ada dua node bertetangga yang memiliki warna sama.
