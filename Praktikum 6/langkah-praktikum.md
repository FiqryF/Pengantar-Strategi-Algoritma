# Praktikum 6 - Grafik BFS dan DFS

Program ini menerapkan traversal BFS dan DFS pada graf berarah Gambar 6.4 mulai dari node `0`.

Edge graf:

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

Cara menjalankan program dengan grafik:

```powershell
.\praktikum06.exe
```

Tampilan grafik menampilkan dua traversal sekaligus:

```text
Panel kiri  : BFS
Panel kanan : DFS
```

Mode console tanpa OpenGL:

```powershell
.\praktikum06.exe --nogui
```

Hasil traversal:

```text
BFS: 0 1 2 3 4 5
DFS: 0 1 4 5 2 3
```
