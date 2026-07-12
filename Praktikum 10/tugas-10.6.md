# 10.6 Tugas / Post-Test

## 1. Program Boyer-Moore

Pada tugas ini, kode praktikum KMP dimodifikasi menjadi algoritma Boyer-Moore. Text dan pattern yang digunakan tetap sama seperti praktikum KMP.

Text:

```text
abacaabacabacababa
```

Pattern:

```text
acabaca
```

Program Boyer-Moore dibuat pada file:

```text
praktikum10_boyer_moore.cpp
```

## Konsep Modifikasi

Pada praktikum KMP, pencocokan dilakukan dari kiri ke kanan dan menggunakan fungsi `computeFail()`.

Pada Boyer-Moore, pencocokan dilakukan dari kanan ke kiri. Program membuat tabel `last occurrence` untuk menyimpan posisi terakhir kemunculan setiap karakter pada pattern.

Jika terjadi mismatch, pattern digeser menggunakan aturan:

```text
i = i + m - min(j, 1 + last[text[i]])
```

Keterangan:

- `i` adalah indeks pada text.
- `j` adalah indeks pada pattern.
- `m` adalah panjang pattern.
- `last[text[i]]` adalah posisi terakhir karakter `text[i]` di dalam pattern.

## 2. Penerapan pada Text dan Pattern yang Sama

Program dijalankan dengan text:

```text
abacaabacabacababa
```

dan pattern:

```text
acabaca
```

Output program:

```text
cari: [acabaca] di dalam teks: [abacaabacabacababa]
pola ditemukan pada posisi-7
```

Artinya, pattern `acabaca` ditemukan mulai dari indeks ke-7 pada text.

## Analisis Hasil

Hasil Boyer-Moore sama dengan hasil praktikum KMP, yaitu pattern ditemukan pada posisi `7`.

Perbedaannya terletak pada cara pencarian:

- KMP mencocokkan pattern dari kiri ke kanan dan memakai tabel fail.
- Boyer-Moore mencocokkan pattern dari kanan ke kiri dan memakai tabel posisi terakhir karakter.

Keduanya menghasilkan posisi yang sama karena text dan pattern yang dicari juga sama.

## Kesimpulan

Algoritma Boyer-Moore berhasil diterapkan dengan memodifikasi kode praktikum KMP. Pattern:

```text
acabaca
```

ditemukan di dalam text:

```text
abacaabacabacababa
```

pada posisi:

```text
7
```
