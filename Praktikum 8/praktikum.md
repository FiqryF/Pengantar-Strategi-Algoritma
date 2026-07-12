# Praktikum 8 - Branch and Bound untuk TSP

## Tujuan Praktikum

Praktikum ini bertujuan untuk menerapkan algoritma Branch and Bound pada kasus Travelling Salesman Problem.

## Teori Singkat

Branch and Bound digunakan untuk menyelesaikan masalah optimasi. Algoritma ini membangkitkan beberapa kemungkinan solusi, menghitung batas atau estimasi cost, lalu memangkas cabang yang tidak mungkin menghasilkan solusi lebih baik.

Pada kasus TSP, tujuan algoritma adalah mencari rute dengan cost minimum yang melewati semua node tepat satu kali dan kembali ke node awal.

## Struktur Program

Program terdiri dari beberapa bagian:

1. Inisialisasi graf dan bobot sisi.
2. Fungsi untuk menghitung batas bawah.
3. Fungsi rekursif Branch and Bound.
4. Fungsi `BB()` untuk menjalankan algoritma.
5. Fungsi untuk menggambar graf dan hasil rute menggunakan OpenGL.
6. Fungsi `main()` sebagai kode tester.

## Fungsi yang Digunakan

### `firstMin()`

Fungsi ini mencari bobot sisi terkecil pertama dari sebuah node.

### `secondMin()`

Fungsi ini mencari bobot sisi terkecil kedua dari sebuah node.

### `BBRecursive()`

Fungsi ini menjalankan proses rekursif Branch and Bound.

Alurnya:

1. Pilih node berikutnya yang belum dikunjungi.
2. Hitung cost sementara.
3. Hitung estimasi cost dengan batas bawah.
4. Jika estimasi masih lebih kecil dari solusi terbaik, cabang dilanjutkan.
5. Jika tidak, cabang dipangkas.

### `BB()`

Fungsi ini menginisialisasi jalur awal, node yang sudah dikunjungi, batas awal, dan memanggil fungsi rekursif.

## Graf yang Digunakan

Graf yang digunakan sesuai Gambar 8.3:

```text
0 - 1 = 25
0 - 2 = 15
0 - 3 = 20
1 - 2 = 35
1 - 3 = 10
2 - 3 = 30
```

## Cara Menjalankan Program

Compile:

```powershell
g++ praktikum08.cpp -o praktikum08.exe -lfreeglut -lopengl32 -lglu32
```

Jalankan dengan tampilan graf:

```powershell
.\praktikum08.exe
```

Jalankan tanpa tampilan OpenGL:

```powershell
.\praktikum08.exe --nogui
```

## Hasil Praktikum

Hasil program:

```text
Final solusi = 0 1 3 2 0 = 80
```

## Penjelasan Cara Kerja

Program memulai pencarian dari node `0`. Setiap cabang menunjukkan kemungkinan rute ke node berikutnya.

Branch and Bound menghitung estimasi cost dari cabang yang sedang dibangun. Jika estimasi cost lebih besar atau sama dengan solusi terbaik sementara, cabang tersebut tidak dilanjutkan.

Dengan cara ini, program tidak perlu menelusuri semua kemungkinan rute sampai akhir jika cabang tersebut sudah terlihat tidak lebih baik.

Pada graf Gambar 8.3, salah satu rute minimum yang ditemukan adalah:

```text
0 - 1 - 3 - 2 - 0
```

Dengan cost:

```text
80
```
