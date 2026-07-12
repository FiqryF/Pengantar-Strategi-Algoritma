#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
using namespace std;

// ===== GRAF (URUTAN DISESUAIKAN MODUL) =====
vector<vector<int>> graph = {
    {1,3,2}, // 0
    {4},     // 1
    {5},     // 2
    {4,5},   // 3
    {6},     // 4
    {6},     // 5
    {}       // 6
};

vector<int> bfs_res, dfs_res;

// ===== BFS =====
void BFS(int start){
    vector<bool> visited(7,false);
    queue<int> q;

    visited[start]=true;
    q.push(start);

    while(!q.empty()){
        int node=q.front(); q.pop();
        bfs_res.push_back(node);

        for(int next:graph[node]){
            if(!visited[next]){
                visited[next]=true;
                q.push(next);
            }
        }
    }
}

// ===== DFS =====
void DFS(int node, vector<bool>& visited){
    visited[node]=true;
    dfs_res.push_back(node);

    for(int next:graph[node]){
        if(!visited[next]){
            DFS(next, visited);
        }
    }
}

// ===== DRAW =====
void drawCircle(float x, float y){
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<100; i++){
        float t = 2 * 3.1416 * i / 100;
        glVertex2f(x + 0.08 * cos(t), y + 0.08 * sin(t));
    }
    glEnd();
}

void drawText(float x, float y, string s){
    glRasterPos2f(x, y);
    for(char c : s)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

// ===== DISPLAY =====
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);

    // ===== TEXT =====
    glColor3f(1.0, 1.0, 0.0); // Warna Kuning untuk Judul Teks
    drawText(-0.95, 0.85, "Hasil Traversal BFS (Start Node 0):");
    drawText(-0.95, 0.55, "Hasil Traversal DFS (Start Node 0):");

    glColor3f(1.0, 1.0, 1.0); // Warna Putih untuk Hasil Teks
    
    // Format Teks BFS
    string bfs_text = "";
    for(size_t i=0; i<bfs_res.size(); i++){
        bfs_text += to_string(bfs_res[i]);
        if(i != bfs_res.size() - 1) bfs_text += " -> ";
    }
    drawText(-0.95, 0.75, bfs_text);

    // Format Teks DFS
    string dfs_text = "";
    for(size_t i=0; i<dfs_res.size(); i++){
        dfs_text += to_string(dfs_res[i]);
        if(i != dfs_res.size() - 1) dfs_text += " -> ";
    }
    drawText(-0.95, 0.45, dfs_text);

    // ===== POSISI NODE (HIERARKI SIMETRIS) =====
    float p[7][2]={
        { 0.00,  0.60}, // 0 (Top Layer)
        { 0.50,  0.20}, // 1 (Middle Layer 1 - Right)
        {-0.50,  0.20}, // 2 (Middle Layer 1 - Left)
        { 0.00,  0.20}, // 3 (Middle Layer 1 - Center)
        { 0.25, -0.20}, // 4 (Middle Layer 2 - Right)
        {-0.25, -0.20}, // 5 (Middle Layer 2 - Left)
        { 0.00, -0.60}  // 6 (Bottom Layer)
    };

    // ===== EDGE (OTOMATIS DARI GRAF) =====
    glColor3f(0.0, 0.8, 0.8); // Warna Cyan untuk Garis Edge
    glBegin(GL_LINES);
    for(int i = 0; i < 7; i++){
        for(int next : graph[i]){
            glVertex2f(p[i][0], p[i][1]);
            glVertex2f(p[next][0], p[next][1]);
        }
    }
    glEnd();

    // ===== NODE (LINGKARAN & ANGKA) =====
    for(int i = 0; i < 7; i++){
        glColor3f(1.0, 0.5, 0.0); // Warna Orange untuk Lingkaran
        drawCircle(p[i][0], p[i][1]);
        
        glColor3f(1.0, 1.0, 1.0); // Warna Putih untuk Angka
        drawText(p[i][0] - 0.02, p[i][1] - 0.02, to_string(i));
    }

    glutSwapBuffers();
}

// ===== MAIN =====
int main(int argc, char** argv){

    BFS(0);

    vector<bool> visited(7, false);
    DFS(0, visited);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutCreateWindow("BFS & DFS Praktikum 6");

    glClearColor(0.1, 0.1, 0.1, 1); // Background sedikit gelap agar kontras

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}