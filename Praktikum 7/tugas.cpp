#include <windows.h>

#include <iostream>
#include <string>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

const int NUM_NODES = 5;
const int NUM_COLORS = 3;

Graph graph;
bool colorExist = false;
int colorList[NUM_NODES];

// Adjacency status matrix untuk graf Gambar 7.5.
// Nilai 1 berarti dua simpul bertetangga, nilai 0 berarti tidak bertetangga.
int adjStatus[NUM_NODES][NUM_NODES] = {
    {0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1},
    {1, 1, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 0, 1, 0}
};

bool assignColor(int nodeIdx, int colorIdx) {
    for (int i = 0; i < NUM_NODES; ++i) {
        if (adjStatus[nodeIdx][i] == 1 && colorList[i] == colorIdx) {
            return false;
        }
    }

    return true;
}

bool graphColoringRecursive(int nodeIdx) {
    if (nodeIdx == NUM_NODES) {
        return true;
    }

    for (int colorIdx = 1; colorIdx <= NUM_COLORS; ++colorIdx) {
        if (assignColor(nodeIdx, colorIdx)) {
            colorList[nodeIdx] = colorIdx;

            if (graphColoringRecursive(nodeIdx + 1)) {
                return true;
            }

            colorList[nodeIdx] = 0;
        }
    }

    return false;
}

void graphColoring() {
    for (int i = 0; i < NUM_NODES; ++i) {
        colorList[i] = 0;
    }

    colorExist = graphColoringRecursive(0);

    if (!colorExist) {
        cout << "Tidak ada solusi pewarnaan yang mungkin" << endl;
        return;
    }

    cout << "Post-Test Praktikum 7" << endl;
    cout << "Representasi graf: adjacency status matrix" << endl;
    cout << "Solusi pewarnaannya yaitu:" << endl;

    for (int i = 0; i < NUM_NODES; ++i) {
        cout << "Node " << i << " = warna " << colorList[i] << endl;
    }
}

void drawResult() {
    drawEdges(graph);

    if (colorExist) {
        drawColoredNodes(graph, colorList);
    } else {
        drawNodes(graph);
    }

    drawText(-0.92f, 0.88f, "Post-Test Praktikum 7 - Adjacency Status Matrix", Vec3(1.0f, 1.0f, 1.0f));
    drawText(-0.92f, 0.80f, "1=Merah, 2=Hijau, 3=Biru", Vec3(1.0f, 1.0f, 1.0f));
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawResult();

    glutSwapBuffers();
}

void buildGraphFigure75() {
    graph.setIsDirected(false);

    // Posisi node dibuat berbeda dari tampilan praktikum.
    // Hubungan antar simpul tetap mengikuti adjacency status matrix Gambar 7.5.
    graph.addNode(-0.78f, 0.18f);  // 0
    graph.addNode(0.18f, 0.66f);   // 1
    graph.addNode(0.76f, -0.06f);  // 2
    graph.addNode(-0.26f, -0.58f); // 3
    graph.addNode(0.62f, -0.72f);  // 4

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(0, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
}

int main(int argc, char** argv) {
    buildGraphFigure75();
    graphColoring();

    bool noGui = argc > 1 && string(argv[1]) == "--nogui";
    if (noGui) {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Post-Test Praktikum 7 - Graph Coloring");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
