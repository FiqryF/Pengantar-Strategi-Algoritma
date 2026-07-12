#include <windows.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

const int NUM_NODES = 4;

// Weighted adjacency matrix untuk graf Gambar 8.3.
// Nilai cost[i][j] menyatakan jarak dari node i ke node j.
int cost[NUM_NODES][NUM_NODES] = {
    {0, 25, 15, 20},
    {25, 0, 35, 10},
    {15, 35, 0, 30},
    {20, 10, 30, 0}
};

Graph graph;
int bestCost = INT_MAX;
vector<int> bestPath;

void branchAndBoundTSP(
    int currentNode,
    int startNode,
    int currentCost,
    vector<bool>& visited,
    vector<int>& currentPath
) {
    if (static_cast<int>(currentPath.size()) == NUM_NODES) {
        int totalCost = currentCost + cost[currentNode][startNode];

        if (totalCost < bestCost) {
            bestCost = totalCost;
            bestPath = currentPath;
            bestPath.push_back(startNode);
        }

        return;
    }

    for (int nextNode = 0; nextNode < NUM_NODES; ++nextNode) {
        if (!visited[nextNode] && cost[currentNode][nextNode] > 0) {
            int nextCost = currentCost + cost[currentNode][nextNode];

            if (nextCost >= bestCost) {
                continue;
            }

            visited[nextNode] = true;
            currentPath.push_back(nextNode);

            branchAndBoundTSP(nextNode, startNode, nextCost, visited, currentPath);

            currentPath.pop_back();
            visited[nextNode] = false;
        }
    }
}

void solveTSP(int startNode) {
    vector<bool> visited(NUM_NODES, false);
    vector<int> currentPath;

    bestCost = INT_MAX;
    bestPath.clear();

    visited[startNode] = true;
    currentPath.push_back(startNode);

    branchAndBoundTSP(startNode, startNode, 0, visited, currentPath);
}

void printMatrix() {
    cout << "Weighted adjacency matrix:" << endl;
    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = 0; j < NUM_NODES; ++j) {
            cout << cost[i][j];
            if (j + 1 < NUM_NODES) {
                cout << "\t";
            }
        }
        cout << endl;
    }
}

void printResult() {
    cout << "Final solusi = ";
    for (int i = 0; i < static_cast<int>(bestPath.size()); ++i) {
        cout << bestPath[i];
        if (i + 1 < static_cast<int>(bestPath.size())) {
            cout << " ";
        }
    }
    cout << " = " << bestCost << endl;
}

void buildGraphFromMatrix() {
    graph.setIsDirected(false);

    graph.addNode(-0.78f, 0.48f);  // 0
    graph.addNode(-0.52f, -0.56f); // 1
    graph.addNode(0.74f, -0.46f);  // 2
    graph.addNode(0.18f, 0.18f);   // 3

    for (int i = 0; i < NUM_NODES; ++i) {
        for (int j = i + 1; j < NUM_NODES; ++j) {
            if (cost[i][j] > 0) {
                graph.addEdge(i, j, cost[i][j]);
            }
        }
    }
}

void drawResultPath() {
    for (int i = 1; i < static_cast<int>(bestPath.size()); ++i) {
        int source = bestPath[i - 1];
        int target = bestPath[i];

        drawLine(
            graph.getNodePosition(source),
            graph.getNodePosition(target),
            Vec3(1.0f, 0.0f, 1.0f),
            4.0f
        );
    }

    drawText(-0.92f, 0.88f, "Post-Test Praktikum 8 - Weighted Adjacency Matrix", Vec3(1.0f, 1.0f, 1.0f));

    string result = "Final solusi = ";
    for (int i = 0; i < static_cast<int>(bestPath.size()); ++i) {
        result += to_string(bestPath[i]);
        if (i + 1 < static_cast<int>(bestPath.size())) {
            result += " -> ";
        }
    }
    result += " = " + to_string(bestCost);

    drawText(-0.92f, -0.90f, result.c_str(), Vec3(1.0f, 0.0f, 1.0f));
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawEdges(graph);
    drawResultPath();
    drawNodes(graph);

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    int startNode = 0;
    bool noGui = argc > 1 && string(argv[1]) == "--nogui";

    cout << "Post-Test Praktikum 8" << endl;
    cout << "Representasi graf: weighted adjacency matrix" << endl;
    printMatrix();

    buildGraphFromMatrix();
    solveTSP(startNode);
    printResult();

    if (noGui) {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Post-Test Praktikum 8 - TSP");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
