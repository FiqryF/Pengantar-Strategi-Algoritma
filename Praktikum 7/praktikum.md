# Praktikum 7 - Backtracking Graph Coloring

## Tujuan Praktikum

Praktikum ini bertujuan untuk menerapkan algoritma Backtracking dalam menyelesaikan masalah pewarnaan simpul graf.

## Teori Singkat

Backtracking adalah metode pencarian solusi dengan mencoba kemungkinan satu per satu secara rekursif. Jika pilihan yang diambil tidak mengarah ke solusi, maka algoritma akan mundur ke langkah sebelumnya dan mencoba pilihan lain.

Pada kasus pewarnaan graf, backtracking digunakan untuk memberi warna pada setiap node dengan aturan bahwa dua node bertetangga tidak boleh memiliki warna yang sama.

## Struktur Program

Program terdiri dari beberapa bagian utama:

1. Inisialisasi graf.
2. Fungsi pengecekan warna.
3. Fungsi rekursif backtracking.
4. Fungsi pewarnaan graf.
5. Fungsi untuk menggambar hasil pewarnaan dengan OpenGL.
6. Fungsi `main()` sebagai kode tester.

## Fungsi yang Digunakan

### `assignColor()`

Fungsi ini mengecek apakah warna tertentu dapat dipakai pada sebuah node.

Jika ada node tetangga yang sudah memakai warna yang sama, maka warna tersebut tidak boleh digunakan.

### `graphColoringRecursive()`

Fungsi ini menjalankan proses backtracking secara rekursif.

Alurnya:

1. Jika semua node sudah diberi warna, proses selesai.
2. Coba warna pertama sampai warna terakhir.
3. Jika warna valid, pasang warna pada node.
4. Lanjut ke node berikutnya secara rekursif.
5. Jika gagal, hapus warna tersebut dan coba warna lain.

### `graphColoring()`

Fungsi ini menginisialisasi semua warna node menjadi `0`, lalu memanggil fungsi rekursif.

## Graf yang Digunakan

Graf yang digunakan sesuai Gambar 7.5:

```text
0 - 1
0 - 2
1 - 2
0 - 3
3 - 4
4 - 1
```

## Jumlah Warna

Jumlah warna yang digunakan adalah 3:

```text
1 = Merah
2 = Hijau
3 = Biru
```

## Cara Menjalankan Program

Compile program:

```powershell
g++ praktikum07.cpp -o praktikum07.exe -lfreeglut -lopengl32 -lglu32
```

Jalankan dengan tampilan graf:

```powershell
.\praktikum07.exe
```

Jalankan tanpa tampilan OpenGL:

```powershell
.\praktikum07.exe --nogui
```

## Hasil Program

Output console:

```text
Solusi pewarnaannya yaitu:
Node 0 = warna 1
Node 1 = warna 2
Node 2 = warna 3
Node 3 = warna 2
Node 4 = warna 1
```

Artinya:

```text
Node 0 = Merah
Node 1 = Hijau
Node 2 = Biru
Node 3 = Hijau
Node 4 = Merah
```

## Penjelasan Cara Kerja

Program mencoba memberi warna mulai dari node `0`. Setiap kali sebuah warna akan dipasang, program mengecek apakah warna tersebut sudah digunakan oleh node tetangga.

Jika warna masih aman, program lanjut ke node berikutnya. Jika tidak ada warna yang valid, program melakukan backtracking, yaitu kembali ke node sebelumnya dan mengganti warnanya.

Pada graf Gambar 7.5, 3 warna sudah cukup untuk menghasilkan pewarnaan yang valid.
