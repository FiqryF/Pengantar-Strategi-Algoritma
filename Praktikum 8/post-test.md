# Praktikum 8 - Post Test / Tugas 8.6

## Soal

1. Terapkan algoritma Branch and Bound pada graf di Gambar 8.3 untuk kasus TSP dengan memodifikasi kode tester praktikum Branch and Bound yang sudah dibuat.
2. Analisis apakah hasil dari program sama dengan jawaban pre-test.

## Modifikasi Kode Tester

Kode tester dimodifikasi pada bagian data graf.

Graf praktikum disesuaikan menjadi graf Gambar 8.3:

```text
0 - 1 = 25
0 - 2 = 15
0 - 3 = 20
1 - 2 = 35
1 - 3 = 10
2 - 3 = 30
```

Node awal yang digunakan:

```text
0
```

## Hasil Program

Output program:

```text
Final solusi = 0 1 3 2 0 = 80
```

Artinya jalur yang diperoleh:

```text
0 - 1 - 3 - 2 - 0
```

Cost:

```text
25 + 10 + 30 + 15 = 80
```

## Analisis

Hasil program sama dengan jawaban pre-test.

Pada pre-test, salah satu rute minimum yang diperoleh adalah:

```text
0 - 1 - 3 - 2 - 0
```

Dengan cost:

```text
80
```

Program juga menghasilkan cost minimum `80`, sehingga hasil program sesuai dengan analisis manual.

Perlu diperhatikan bahwa TSP dapat memiliki lebih dari satu jalur dengan cost minimum yang sama. Contohnya:

```text
0 - 2 - 3 - 1 - 0 = 80
0 - 3 - 1 - 2 - 0 = 80
```

Jadi jika program menghasilkan jalur berbeda tetapi cost-nya tetap `80`, hasil tersebut tetap benar.

## Kesimpulan

Algoritma Branch and Bound berhasil diterapkan pada graf Gambar 8.3.

Cost minimum:

```text
80
```

Salah satu jalur minimum:

```text
0 - 1 - 3 - 2 - 0
```
