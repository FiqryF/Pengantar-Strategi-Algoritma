# Post-Test Praktikum 10 - Boyer-Moore

## Soal

Terapkan string matching menggunakan algoritma Boyer-Moore dengan memodifikasi kode praktikum KMP yang sudah dibuat, kemudian analisis hasilnya.

## Text dan Pattern

Text:

```text
abacaabacabacababa
```

Pattern:

```text
acabaca
```

## Representasi yang Digunakan

Post-test menggunakan **last occurrence table** atau **bad character table**.

Tabel ini menyimpan posisi terakhir kemunculan setiap karakter pada pattern. Tabel tersebut digunakan oleh algoritma Boyer-Moore untuk menentukan pergeseran pattern ketika terjadi ketidakcocokan karakter.

Untuk pattern:

```text
acabaca
```

Last occurrence table:

```text
a = 6
c = 5
b = 3
```

## Hasil Program

Output program:

```text
Post-Test Praktikum 10
Representasi: last occurrence table / bad character table
cari: [acabaca] di dalam teks: [abacaabacabacababa]
pola ditemukan pada posisi-7
```

Artinya pattern `acabaca` ditemukan mulai dari indeks ke-7 pada text.

## Perbandingan dengan Praktikum KMP

Hasil Boyer-Moore sama dengan hasil KMP.

```text
KMP          = pola ditemukan pada posisi-7
Boyer-Moore = pola ditemukan pada posisi-7
```

## Analisis Perbedaan

Perbedaan terletak pada cara pencocokan:

```text
KMP:
- Mencocokkan pattern dari kiri ke kanan.
- Menggunakan fail table dari fungsi computeFail().

Boyer-Moore:
- Mencocokkan pattern dari kanan ke kiri.
- Menggunakan last occurrence table / bad character table.
```

Walaupun cara kerja kedua algoritma berbeda, hasil akhirnya sama karena text dan pattern yang digunakan sama.

## Kesimpulan

Algoritma Boyer-Moore berhasil diterapkan pada post-test Praktikum 10.

Pattern:

```text
acabaca
```

ditemukan pada text:

```text
abacaabacabacababa
```

di posisi:

```text
7
```
