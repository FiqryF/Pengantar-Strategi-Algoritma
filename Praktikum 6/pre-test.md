# Pre-Test Praktikum 6 - BFS dan DFS

## Soal

1. Analisis graf berarah pada Gambar 6.4 dan tuliskan urutan jalurnya secara manual apabila menggunakan algoritma BFS dan DFS mulai dari simpul/node ke-0.
2. Apa perbedaan utama antara algoritma BFS dan DFS?

## Graf Gambar 6.4

Graf berarah memiliki simpul:

```text
0, 1, 2, 3, 4, 5
```

Edge yang digunakan:

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

## Analisis BFS

BFS atau Breadth First Search mengunjungi simpul secara melebar. Artinya, node yang bertetangga langsung dengan node awal dikunjungi terlebih dahulu sebelum masuk ke level berikutnya.

Mulai dari node `0`:

```text
0 -> 1 -> 2 -> 3 -> 4 -> 5
```

Urutan BFS:

```text
0 1 2 3 4 5
```

## Analisis DFS

DFS atau Depth First Search mengunjungi simpul secara mendalam. Artinya, algoritma akan masuk ke cabang terdalam terlebih dahulu sebelum kembali ke cabang lain.

Mulai dari node `0`:

```text
0 -> 1 -> 4 -> 5 -> 2 -> 3
```

Urutan DFS:

```text
0 1 4 5 2 3
```

## Perbedaan BFS dan DFS

Perbedaan utama BFS dan DFS terletak pada cara mengunjungi node.

BFS mengunjungi node berdasarkan level atau jarak terdekat dari node awal. BFS biasanya menggunakan struktur data queue.

DFS mengunjungi node dengan masuk sedalam mungkin ke salah satu cabang sebelum kembali ke cabang lain. DFS biasanya menggunakan rekursi atau stack.

## Kesimpulan

Hasil analisis manual:

```text
BFS = 0 1 2 3 4 5
DFS = 0 1 4 5 2 3
```
