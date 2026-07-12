# 9.5 Langkah Praktikum

## Persiapan

1. Siapkan environment C++ yang sudah mendukung OpenGL dan FreeGLUT.
2. Buat folder project bernama `Praktikum 9`.
3. Siapkan file berikut di dalam folder project:
   - `graph.h`
   - `draws.h`
   - `praktikum09.cpp`
4. Pastikan compiler yang digunakan adalah `g++` dari MSYS2 UCRT64.
5. Gunakan opsi linker:

```text
-lfreeglut -lopengl32 -lglu32
```

## Praktikum

1. Buat struktur graf menggunakan class `Graph`.
2. Tambahkan 7 node sesuai Gambar 9.2, yaitu node `0` sampai node `6`.
3. Tambahkan edge tidak berarah dengan bobot sebagai berikut:

| Edge | Bobot |
|---|---:|
| 0 - 1 | 3 |
| 0 - 2 | 4 |
| 0 - 3 | 5 |
| 1 - 3 | 2 |
| 2 - 4 | 4 |
| 3 - 4 | 2 |
| 4 - 5 | 1 |
| 4 - 6 | 5 |
| 5 - 6 | 3 |

4. Tentukan node asal dan target:

```text
startIdx = 0
endIdx = 6
```

5. Terapkan algoritma A* dengan rumus:

```text
f(n) = g(n) + h(n)
```

6. Nilai `g(n)` dihitung dari total bobot yang sudah dilalui dari node asal.
7. Nilai `h(n)` dihitung dari banyaknya busur minimal dari node saat ini ke node target.
8. Simpan hasil jalur akhir ke dalam `pathSequence`.
9. Tampilkan hasil jalur pada console dan visualisasikan graf menggunakan OpenGL/FreeGLUT.

## Hasil

Berdasarkan program, jalur terpendek dari node `0` ke node `6` memiliki total jarak:

```text
11
```

Solusi jalur terpendek yang dihasilkan program adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

Jalur ini memiliki total jarak:

```text
5 + 2 + 1 + 3 = 11
```

Hasil ini sesuai dengan analisis pre-test karena sama-sama memperoleh total jarak minimum `11`. Terdapat juga jalur lain, yaitu `0 -> 1 -> 3 -> 4 -> 5 -> 6`, dengan total `11`, sehingga kedua jalur tersebut sama-sama benar sebagai solusi terpendek.

## Pengamatan Hasil dan Cara Kerja

Pada saat program dijalankan, algoritma A* mencari rute dari node asal `0` menuju node target `6`. Setiap node yang menjadi kandidat dihitung menggunakan rumus:

```text
f(n) = g(n) + h(n)
```

Nilai `g(n)` adalah jarak sebenarnya dari node awal ke node yang sedang diperiksa, sedangkan `h(n)` adalah nilai perkiraan menuju node target. Pada praktikum ini, nilai heuristik `h(n)` dihitung berdasarkan banyaknya busur minimal dari node saat ini menuju node target.

Program mulai dari node `0`. Dari node `0`, terdapat tiga kemungkinan awal, yaitu menuju node `1`, node `2`, dan node `3`.

```text
0 -> 1 memiliki g = 3
0 -> 2 memiliki g = 4
0 -> 3 memiliki g = 5
```

Setiap kemungkinan tersebut kemudian diberi nilai heuristik. Algoritma memilih node dengan nilai `f(n)` terkecil untuk diperiksa lebih lanjut. Jika ada beberapa node dengan nilai yang hampir sama, program tetap melanjutkan pemeriksaan sampai menemukan jalur dengan total biaya paling kecil menuju target.

Pada proses pencarian, node `3` menjadi bagian dari jalur terbaik karena dari node `3` dapat menuju node `4` dengan bobot `2`. Setelah itu node `4` memiliki dua pilihan menuju target, yaitu langsung ke node `6` atau melalui node `5`.

Jika langsung dari node `4` ke node `6`, total jaraknya:

```text
0 -> 3 -> 4 -> 6
5 + 2 + 5 = 12
```

Jika melalui node `5`, total jaraknya:

```text
0 -> 3 -> 4 -> 5 -> 6
5 + 2 + 1 + 3 = 11
```

Karena nilai `11` lebih kecil daripada `12`, maka program memilih jalur:

```text
0 -> 3 -> 4 -> 5 -> 6
```

Jadi, cara kerja program adalah mengevaluasi setiap kandidat node menggunakan gabungan jarak sebenarnya `g(n)` dan perkiraan jarak ke target `h(n)`. Dengan cara tersebut, algoritma A* tidak memilih jalur secara acak, tetapi memilih jalur yang terlihat paling menjanjikan dan tetap mempertimbangkan total bobot yang sudah dilalui.

Kesimpulannya, hasil program menunjukkan bahwa rute terpendek dari node `0` ke node `6` adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

dengan total jarak:

```text
11
```

## Cara Compile di VS Code

Gunakan `Ctrl+Shift+B`, atau jalankan perintah berikut dari terminal di folder project:

```powershell
$env:Path = 'C:\msys64\ucrt64\bin;C:\msys64\usr\bin;' + $env:Path
C:\msys64\ucrt64\bin\g++.exe praktikum09.cpp -o praktikum09.exe -lfreeglut -lopengl32 -lglu32
```

## Cara Menjalankan

Setelah compile berhasil:

```powershell
.\praktikum09.exe
```
