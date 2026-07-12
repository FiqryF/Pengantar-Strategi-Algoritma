#include <windows.h>

#include <iostream>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

Graph graph;
bool colorExist = false;
int* colorList = NULL;

bool assignColor(int nodeIdx, const vector<vector<int> >& adjacency, int colorIdx) {
    for (int i = 0; i < static_cast<int>(adjacency[nodeIdx].size()); ++i) {
        int neighbor = adjacency[nodeIdx][i];
        if (colorList[neighbor] == colorIdx) {
            return false;
        }
    }

    return true;
}

bool graphColoringRecursive(const vector<vector<int> >& adjacency, int numNodes, int numColors, int nodeIdx) {
    if (nodeIdx == numNodes) {
        return true;
    }

    for (int colorIdx = 1; colorIdx <= numColors; ++colorIdx) {
        if (assignColor(nodeIdx, adjacency, colorIdx)) {
            colorList[nodeIdx] = colorIdx;

            if (graphColoringRecursive(adjacency, numNodes, numColors, nodeIdx + 1)) {
                return true;
            }

            colorList[nodeIdx] = 0;
        }
    }

    return false;
}

void graphColoring(int numColors) {
    int numNodes = graph.getNumNodes();
    colorList = new int[numNodes];

    for (int i = 0; i < numNodes; ++i) {
        colorList[i] = 0;
    }

    colorExist = graphColoringRecursive(graph.getAdjNodes(), numNodes, numColors, 0);

    if (!colorExist) {
        cout << "Tidak ada solusi pewarnaan yang mungkin" << endl;
        return;
    }

    cout << "Solusi pewarnaannya yaitu:" << endl;
    for (int i = 0; i < numNodes; ++i) {
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

    drawText(-0.92f, 0.88f, "Backtracking Graph Coloring - 3 Warna", Vec3(1.0f, 1.0f, 1.0f));
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

    graph.addNode(-0.45f, 0.00f);  // 0
    graph.addNode(0.45f, 0.00f);   // 1
    graph.addNode(0.00f, -0.55f);  // 2
    graph.addNode(-0.45f, 0.55f);  // 3
    graph.addNode(0.45f, 0.55f);   // 4

    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(0, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
}

int main(int argc, char** argv) {
    buildGraphFigure75();

    int numColors = 3;
    graphColoring(numColors);

    bool noGui = argc > 1 && string(argv[1]) == "--nogui";
    if (noGui) {
        delete[] colorList;
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum 7 - Backtracking Graph Coloring");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    delete[] colorList;
    return 0;
}
