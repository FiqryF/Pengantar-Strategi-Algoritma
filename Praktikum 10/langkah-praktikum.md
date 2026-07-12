# 10.5 Langkah Praktikum - KMP

## Tujuan

Menerapkan algoritma string matching menggunakan Knuth-Morris-Pratt (KMP) untuk mencari sebuah pattern di dalam text.

## Data Uji

Text:

```text
abacaabacabacababa
```

Pattern:

```text
acabaca
```

## Fungsi yang Digunakan

### `computeFail()`

Fungsi `computeFail()` digunakan untuk membuat tabel fail dari pattern. Tabel ini menyimpan informasi kecocokan awalan dan akhiran pada pattern, sehingga saat terjadi mismatch algoritma tidak perlu mengulang pencocokan dari awal.

### `KMPMatch()`

Fungsi `KMPMatch()` digunakan untuk mencocokkan pattern dengan text. Fungsi ini mengembalikan indeks awal pattern jika ditemukan, dan mengembalikan `-1` jika pattern tidak ditemukan.

## Hasil Program

Output console:

```text
cari: [acabaca] di dalam teks: [abacaabacabacababa]
pola ditemukan pada posisi-7
```

Artinya pattern `acabaca` ditemukan mulai dari indeks ke-7 pada text.

## Penjelasan Cara Kerja

KMP mencocokkan pattern dari kiri ke kanan. Ketika karakter text dan pattern cocok, indeks text dan pattern sama-sama maju. Jika terjadi mismatch, KMP tidak menggeser pattern satu per satu seperti brute force. KMP menggunakan tabel fail untuk menentukan posisi pattern berikutnya yang masih mungkin cocok.

Pada data uji ini, pattern:

```text
acabaca
```

ditemukan di dalam text:

```text
abacaabacabacababa
```

mulai dari indeks `7`.

## Cara Compile

```powershell
$env:Path = 'C:\msys64\ucrt64\bin;C:\msys64\usr\bin;' + $env:Path
C:\msys64\ucrt64\bin\g++.exe praktikum10.cpp -o praktikum10.exe -lfreeglut -lopengl32 -lglu32
```

## Cara Menjalankan

Dengan tampilan OpenGL:

```powershell
.\praktikum10.exe
```

Tanpa tampilan OpenGL:

```powershell
.\praktikum10.exe --nogui
```
