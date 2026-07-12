# Pre-Test Praktikum 9 - Algoritma A*

## Diketahui

Node asal: `0`

Node target: `6`

Bobot sisi pada graf:

| Sisi | Bobot |
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

Heuristik yang digunakan adalah banyaknya busur minimal dari node saat ini ke node target.

| Node | h(n) ke node 6 |
|---|---:|
| 0 | 3 |
| 1 | 3 |
| 2 | 2 |
| 3 | 2 |
| 4 | 1 |
| 5 | 1 |
| 6 | 0 |

Rumus A*:

```text
f(n) = g(n) + h(n)
```

Keterangan:

- `g(n)` adalah total bobot/jarak dari node asal ke node saat ini.
- `h(n)` adalah estimasi jarak ke target berdasarkan jumlah busur minimal.
- `f(n)` adalah nilai evaluasi yang dipilih oleh algoritma A*.

## Proses Pencarian

Mulai dari node `0`.

Tetangga node `0`:

| Node | g(n) | h(n) | f(n) |
|---|---:|---:|---:|
| 1 | 3 | 3 | 6 |
| 2 | 4 | 2 | 6 |
| 3 | 5 | 2 | 7 |

Node `1` dan `2` memiliki nilai `f(n)` sama, yaitu `6`. Salah satu dapat dipilih terlebih dahulu. Setelah semua kemungkinan terbaik diproses, jalur melalui node `3` memberikan jarak lebih kecil menuju node `4`.

Dari node `3` ke node `4`:

```text
g(4) = 5 + 2 = 7
h(4) = 1
f(4) = 8
```

Dari node `4`, terdapat dua kemungkinan menuju target:

1. Langsung ke node `6`

```text
0 -> 3 -> 4 -> 6
total = 5 + 2 + 5 = 12
```

2. Melalui node `5` terlebih dahulu

```text
0 -> 3 -> 4 -> 5 -> 6
total = 5 + 2 + 1 + 3 = 11
```

Karena jalur melalui node `5` memiliki total jarak lebih kecil, maka jalur tersebut dipilih.

## Jawaban

Salah satu jalur terpendek dari node `0` ke node `6` adalah:

```text
0 -> 3 -> 4 -> 5 -> 6
```

Total jarak:

```text
5 + 2 + 1 + 3 = 11
```

Jadi, solusi jalur terpendek menggunakan algoritma A* adalah:

```text
0 - 3 - 4 - 5 - 6
```

dengan total jarak `11`.

Catatan: terdapat jalur lain dengan total jarak yang sama, yaitu:

```text
0 -> 1 -> 3 -> 4 -> 5 -> 6
```

Total jaraknya juga:

```text
3 + 2 + 2 + 1 + 3 = 11
```

Namun jawaban cukup menuliskan satu solusi jalur terpendek, sehingga jalur `0 -> 3 -> 4 -> 5 -> 6` dapat digunakan.
