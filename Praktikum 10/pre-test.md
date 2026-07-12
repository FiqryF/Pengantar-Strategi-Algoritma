# Pre-Test Praktikum 10 - Algoritma Boyer-Moore

## Soal

Baca slide kuliah materi pencocokan string dengan algoritma Boyer-Moore di halaman 41. Tulis notasi algoritma untuk algoritma Boyer-Moore tersebut.

## Jawaban

Algoritma Boyer-Moore adalah algoritma pencocokan string yang mencocokkan pattern terhadap text dari arah kanan ke kiri. Jika terjadi ketidakcocokan karakter, pattern dapat digeser lebih jauh menggunakan aturan pergeseran. Salah satu aturan yang umum digunakan adalah **bad character rule**.

Misalkan:

```text
T = text
P = pattern
n = panjang text
m = panjang pattern
```

Algoritma Boyer-Moore melakukan pra-pemrosesan pada pattern untuk membuat tabel kemunculan terakhir setiap karakter. Tabel ini digunakan untuk menentukan seberapa jauh pattern harus digeser saat terjadi mismatch.

## Notasi Algoritma Boyer-Moore

```text
Algoritma BoyerMoore(T, P)

Input:
    T = text
    P = pattern

Output:
    indeks awal kemunculan P di dalam T,
    atau -1 jika P tidak ditemukan

Langkah:
1. n <- panjang(T)
2. m <- panjang(P)
3. Buat tabel last occurrence untuk setiap karakter
4. Untuk setiap karakter c, isi last[c] <- -1
5. Untuk i <- 0 sampai m - 1:
       last[P[i]] <- i

6. i <- m - 1
7. j <- m - 1

8. Selama i < n:
       Jika T[i] = P[j], maka:
           Jika j = 0, maka:
               return i
           Selain itu:
               i <- i - 1
               j <- j - 1

       Jika T[i] != P[j], maka:
           l <- last[T[i]]
           i <- i + m - min(j, 1 + l)
           j <- m - 1

9. return -1
```

## Penjelasan

Algoritma Boyer-Moore tidak mencocokkan pattern dari kiri ke kanan, tetapi dari kanan ke kiri. Perbandingan dimulai dari karakter terakhir pattern. Jika karakter cocok, pemeriksaan dilanjutkan ke karakter sebelumnya.

Jika terjadi ketidakcocokan, algoritma tidak langsung menggeser pattern satu langkah seperti brute force. Boyer-Moore melihat posisi terakhir karakter mismatch tersebut di dalam pattern. Berdasarkan informasi itu, pattern dapat digeser lebih jauh sehingga perbandingan yang tidak perlu dapat dihindari.

Contoh aturan pergeseran saat mismatch:

```text
i <- i + m - min(j, 1 + last[T[i]])
```

Keterangan:

- `i` adalah indeks pada text.
- `j` adalah indeks pada pattern.
- `last[T[i]]` adalah posisi terakhir karakter `T[i]` di dalam pattern.
- Jika karakter tidak ada di pattern, nilai `last[T[i]] = -1`.

## Kesimpulan

Boyer-Moore lebih efisien daripada brute force karena dapat melakukan pergeseran pattern lebih jauh saat terjadi mismatch. Algoritma ini sangat baik untuk pencocokan string karena memanfaatkan informasi dari pattern sebelum proses pencarian dilakukan.
