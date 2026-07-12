# Praktikum 6 - Penerapan BFS dan DFS

## Tujuan Praktikum

Praktikum ini bertujuan untuk menerapkan algoritma BFS dan DFS dalam melakukan traversal pada graf berarah.

## Persiapan

File yang digunakan:

```text
praktikum06.cpp
graph.h
draws.h
```

Library yang digunakan:

```text
OpenGL
FreeGLUT
GLU
```

## Struktur Program

Program terdiri dari beberapa bagian utama:

1. Inisialisasi graf berarah.
2. Fungsi untuk menggambar graf dan hasil traversal.
3. Fungsi BFS.
4. Fungsi DFS.
5. Fungsi `main()` sebagai kode tester.

## Fungsi BFS

Fungsi BFS menggunakan queue untuk menyimpan node yang akan dikunjungi.

Alur BFS:

1. Tandai node awal sebagai sudah dikunjungi.
2. Masukkan node awal ke queue.
3. Ambil node dari queue.
4. Kunjungi semua tetangga yang belum dikunjungi.
5. Masukkan tetangga tersebut ke queue.
6. Ulangi sampai queue kosong.

## Fungsi DFS

Fungsi DFS menggunakan rekursi.

Alur DFS:

1. Tandai node sekarang sebagai sudah dikunjungi.
2. Cetak node sekarang.
3. Periksa semua tetangga node tersebut.
4. Jika ada tetangga yang belum dikunjungi, lakukan DFS dari tetangga tersebut.
5. Jika cabang sudah habis, kembali ke node sebelumnya.

## Graf yang Digunakan

Graf berarah yang digunakan sesuai Gambar 6.4:

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

## Cara Menjalankan Program

Menjalankan program dengan tampilan grafik:

```powershell
.\praktikum06.exe
```

Program akan menampilkan dua grafik traversal sekaligus:

```text
Panel kiri  : BFS
Panel kanan : DFS
```

Menjalankan tanpa tampilan OpenGL:

```powershell
.\praktikum06.exe --nogui
```

## Hasil Praktikum

Hasil BFS:

```text
BFS mulai dari node 0
0 1 2 3 4 5
```

Hasil DFS:

```text
DFS mulai dari node 0
0 1 4 5 2 3
```

## Penjelasan Hasil

Hasil BFS berbeda dengan DFS karena BFS mengunjungi node berdasarkan level, sedangkan DFS mengunjungi node berdasarkan kedalaman cabang.

Pada BFS, node `1`, `2`, dan `3` dikunjungi lebih awal karena semuanya merupakan tetangga langsung dari node `0`.

Pada DFS, setelah node `0`, algoritma masuk ke node `1`, lalu lanjut sedalam mungkin ke `4`, `5`, dan `2`, sebelum akhirnya kembali dan mengunjungi node `3`.
