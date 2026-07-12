#include <windows.h>

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

Graph graph;
vector<vector<int> > bfsTree;
vector<vector<int> > dfsTree;
vector<int> bfsOrder;
vector<int> dfsOrder;
char markText[32];

void drawTraversalResult(
    const vector<vector<int> >& traversalTree,
    const vector<int>& traversalOrder,
    const Vec3& pathColor
) {
    for (int source = 0; source < graph.getNumNodes(); ++source) {
        for (int i = 0; i < static_cast<int>(traversalTree[source].size()); ++i) {
            int target = traversalTree[source][i];
            drawArrow(
                graph.getNodePosition(source),
                graph.getNodePosition(target),
                pathColor,
                4.0f
            );
        }
    }

    for (int i = 0; i < static_cast<int>(traversalOrder.size()); ++i) {
        int nodeIdx = traversalOrder[i];
        NodePosition position = graph.getNodePosition(nodeIdx);

        if (i == 0) {
            sprintf(markText, "%s", "start");
        } else {
            sprintf(markText, "%d", i);
        }

        drawText(position.x + 0.08f, position.y + 0.08f, markText, pathColor);
    }
}

void drawOrderText(const vector<int>& order, const string& label, float y, const Vec3& color) {
    string text = label + ": ";
    for (int i = 0; i < static_cast<int>(order.size()); ++i) {
        text += to_string(order[i]);
        if (i + 1 < static_cast<int>(order.size())) {
            text += " -> ";
        }
    }

    drawText(-0.92f, y, text.c_str(), color);
}

void drawPanel(
    const vector<vector<int> >& traversalTree,
    const vector<int>& traversalOrder,
    const string& label,
    float offsetY,
    const Vec3& pathColor
) {
    glPushMatrix();
    glTranslatef(0.0f, offsetY, 0.0f);
    glScalef(0.62f, 0.42f, 1.0f);

    drawEdges(graph);
    drawTraversalResult(traversalTree, traversalOrder, pathColor);
    drawNodes(graph);

    drawText(-0.95f, 1.12f, label.c_str(), pathColor);
    glPopMatrix();
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawText(-0.72f, 0.93f, "Post-Test Praktikum 6 - Visual Modifikasi", Vec3(1.0f, 1.0f, 1.0f));
    drawPanel(bfsTree, bfsOrder, "BFS - Adjacency List", 0.35f, Vec3(0.0f, 0.85f, 1.0f));
    drawPanel(dfsTree, dfsOrder, "DFS - Adjacency List", -0.47f, Vec3(1.0f, 0.55f, 0.0f));

    drawOrderText(bfsOrder, "BFS", -0.87f, Vec3(0.0f, 0.85f, 1.0f));
    drawOrderText(dfsOrder, "DFS", -0.94f, Vec3(1.0f, 0.55f, 0.0f));

    glutSwapBuffers();
}

void BFS(int startIdx) {
    vector<bool> visited(graph.getNumNodes(), false);
    list<int> queue;

    bfsOrder.clear();
    bfsTree.assign(graph.getNumNodes(), vector<int>());

    visited[startIdx] = true;
    queue.push_back(startIdx);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop_front();

        cout << current << " ";
        bfsOrder.push_back(current);

        const vector<int>& neighbors = graph.getAdjNodes()[current];
        for (int i = 0; i < static_cast<int>(neighbors.size()); ++i) {
            int next = neighbors[i];
            if (!visited[next]) {
                visited[next] = true;
                queue.push_back(next);
                bfsTree[current].push_back(next);
            }
        }
    }
}

void DFSRecursive(int current, vector<bool>& visited) {
    visited[current] = true;

    cout << current << " ";
    dfsOrder.push_back(current);

    const vector<int>& neighbors = graph.getAdjNodes()[current];
    for (int i = 0; i < static_cast<int>(neighbors.size()); ++i) {
        int next = neighbors[i];
        if (!visited[next]) {
            dfsTree[current].push_back(next);
            DFSRecursive(next, visited);
        }
    }
}

void DFS(int startIdx) {
    vector<bool> visited(graph.getNumNodes(), false);

    dfsOrder.clear();
    dfsTree.assign(graph.getNumNodes(), vector<int>());

    DFSRecursive(startIdx, visited);
}

void buildPostTestGraph() {
    graph.setIsDirected(true);

    // Posisi node dibuat berbeda dari graf praktikum, tetapi adjacency list tetap sama.
    graph.addNode(-0.82f, 0.50f);  // 0
    graph.addNode(-0.22f, 0.78f);  // 1
    graph.addNode(0.72f, 0.45f);   // 2
    graph.addNode(-0.48f, -0.04f); // 3
    graph.addNode(0.20f, -0.42f);  // 4
    graph.addNode(0.82f, -0.78f);  // 5

    // Adjacency list graf Gambar 6.4.
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(0, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 1);
    graph.addEdge(3, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 5);
    graph.addEdge(5, 2);
}

int main(int argc, char** argv) {
    buildPostTestGraph();

    int startIdx = 0;
    bool noGui = argc > 1 && string(argv[1]) == "--nogui";

    cout << "Post-Test Praktikum 6 - Visual Modifikasi" << endl;
    cout << "Representasi graf: adjacency list" << endl;

    cout << "BFS mulai dari node " << startIdx << endl;
    BFS(startIdx);
    cout << endl;

    cout << "DFS mulai dari node " << startIdx << endl;
    DFS(startIdx);
    cout << endl;

    if (noGui) {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Post-Test Praktikum 6 - BFS dan DFS");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
