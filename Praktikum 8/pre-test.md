# Praktikum 8 - Pre Test

## Soal

Analisis graf pada Gambar 8.3 dan tuliskan satu solusi jalur dengan cost minimum yang mungkin untuk kasus TSP menggunakan algoritma Branch and Bound.

## Graf Gambar 8.3

Node:

```text
0, 1, 2, 3
```

Bobot sisi:

```text
0 - 1 = 25
0 - 2 = 15
0 - 3 = 20
1 - 2 = 35
1 - 3 = 10
2 - 3 = 30
```

## Analisis Manual

TSP mencari jalur yang melewati semua node tepat satu kali dan kembali ke node awal.

Jika dimulai dari node `0`, kemungkinan jalur yang dapat diperiksa:

```text
0 - 1 - 2 - 3 - 0 = 25 + 35 + 30 + 20 = 110
0 - 1 - 3 - 2 - 0 = 25 + 10 + 30 + 15 = 80
0 - 2 - 1 - 3 - 0 = 15 + 35 + 10 + 20 = 80
0 - 2 - 3 - 1 - 0 = 15 + 30 + 10 + 25 = 80
0 - 3 - 1 - 2 - 0 = 20 + 10 + 35 + 15 = 80
0 - 3 - 2 - 1 - 0 = 20 + 30 + 35 + 25 = 110
```

## Hasil

Salah satu jalur dengan cost minimum:

```text
0 - 1 - 3 - 2 - 0
```

Cost:

```text
25 + 10 + 30 + 15 = 80
```

## Kesimpulan

Cost minimum untuk graf Gambar 8.3 adalah:

```text
80
```

Salah satu solusi jalur minimum adalah:

```text
0 - 1 - 3 - 2 - 0
```
