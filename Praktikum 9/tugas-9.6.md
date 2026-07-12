# 9.6 Tugas

## 1. Penerapan Algoritma A* pada Graf Gambar 9.2

Algoritma A* diterapkan pada graf Gambar 9.2 untuk mencari rute terpendek dari node asal `0` menuju node target `6`.

Graf yang digunakan memiliki node:

```text
0, 1, 2, 3, 4, 5, 6
```

Edge dan bobot yang digunakan:

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

Pada program, graf tersebut dibuat pada fungsi:

```cpp
void buildGraphFromFigure92()
```

Potongan kode edge yang digunakan:

```cpp
graph.addEdge(0, 1, 3.0f);
graph.addEdge(0, 2, 4.0f);
graph.addEdge(0, 3, 5.0f);
graph.addEdge(1, 3, 2.0f);
graph.addEdge(2, 4, 4.0f);
graph.addEdge(3, 4, 2.0f);
graph.addEdge(4, 5, 1.0f);
graph.addEdge(4, 6, 5.0f);
graph.addEdge(5, 6, 3.0f);
```

Algoritma A* menggunakan rumus:

```text
f(n) = g(n) + h(n)
```

Keterangan:

- `g(n)` adalah total jarak dari node asal ke node saat ini.
- `h(n)` adalah heuristik menuju target.
- `f(n)` adalah nilai evaluasi yang digunakan untuk memilih node berikutnya.

Heuristik yang digunakan adalah banyaknya busur minimal dari node saat ini menuju node target.

## Hasil Program

Setelah program dijalankan, hasil yang muncul adalah:

```text
Final solution = 0 3 4 5 6 = 11
```

Artinya, rute terpendek yang ditemukan program adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

Total jaraknya:

```text
5 + 2 + 1 + 3 = 11
```

## 2. Analisis Perbandingan dengan Jawaban Pre-Test

Pada jawaban pre-test, rute terpendek yang diperoleh adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

dengan total jarak:

```text
11
```

Hasil program sama dengan jawaban pre-test karena keduanya menghasilkan total jarak minimum `11`.

Pada graf ini juga terdapat jalur lain dengan total jarak yang sama, yaitu:

```text
0 -> 1 -> 3 -> 4 -> 5 -> 6
```

Total jaraknya:

```text
3 + 2 + 2 + 1 + 3 = 11
```

Jadi, apabila program menghasilkan salah satu dari dua jalur tersebut, hasilnya tetap benar selama total jaraknya `11`. Pada program yang dibuat, jalur yang dipilih adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

## Kesimpulan

Algoritma A* berhasil diterapkan pada graf Gambar 9.2. Program menemukan rute terpendek dari node `0` ke node `6`, yaitu:

```text
0 -> 3 -> 4 -> 5 -> 6
```

dengan total jarak:

```text
11
```

Hasil program sesuai dengan analisis pre-test, sehingga implementasi algoritma A* pada tugas ini sudah benar.
