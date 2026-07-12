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
vector<vector<int> > bfsResult;
vector<vector<int> > dfsResult;
vector<int> bfsSequence;
vector<int> dfsSequence;
char markText[32];

void drawResult(const vector<vector<int> >& pathResult, const vector<int>& pathSequence) {
    glPushMatrix();

    for (int source = 0; source < graph.getNumNodes(); ++source) {
        for (int i = 0; i < static_cast<int>(pathResult[source].size()); ++i) {
            int target = pathResult[source].at(i);
            drawArrow(
                graph.getNodePosition(source),
                graph.getNodePosition(target),
                Vec3(1.0f, 0.0f, 1.0f),
                4.0f
            );
        }
    }

    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        int nodeIdx = pathSequence.at(i);
        NodePosition position = graph.getNodePosition(nodeIdx);

        if (i == 0) {
            sprintf(markText, "%s", "start");
        } else {
            sprintf(markText, "%d", i);
        }

        drawText(position.x + 0.08f, position.y + 0.08f, markText, Vec3(1.0f, 0.0f, 1.0f));
    }

    glPopMatrix();
}

void drawTraversalPanel(const vector<vector<int> >& pathResult, const vector<int>& pathSequence, const string& label, float offsetX) {
    glPushMatrix();
    glTranslatef(offsetX, -0.04f, 0.0f);
    glScalef(0.78f, 0.78f, 1.0f);
    drawEdges(graph);
    if (!pathSequence.empty()) {
        drawResult(pathResult, pathSequence);
    }
    drawNodes(graph);

    string title = label + ": ";
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        title += to_string(pathSequence[i]);
        if (i + 1 < static_cast<int>(pathSequence.size())) {
            title += " - ";
        }
    }
    drawText(-0.58f, 1.05f, title.c_str(), Vec3(1.0f, 1.0f, 1.0f));
    glPopMatrix();
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawTraversalPanel(bfsResult, bfsSequence, "BFS", -0.52f);
    drawTraversalPanel(dfsResult, dfsSequence, "DFS", 0.52f);

    glutSwapBuffers();
}

void BFS(Graph graph, int startIdx) {
    bool* visited = new bool[graph.getNumNodes()];
    for (int i = 0; i < graph.getNumNodes(); ++i) {
        visited[i] = false;
    }

    list<int> queue;
    visited[startIdx] = true;
    queue.push_back(startIdx);

    bfsSequence.clear();
    bfsResult.assign(graph.getNumNodes(), vector<int>());

    while (!queue.empty()) {
        startIdx = queue.front();
        cout << startIdx << " ";
        bfsSequence.push_back(startIdx);
        queue.pop_front();

        for (int i = 0; i < static_cast<int>(graph.getAdjNodes()[startIdx].size()); ++i) {
            int nodeIdx = graph.getAdjNodes()[startIdx].at(i);
            if (!visited[nodeIdx]) {
                visited[nodeIdx] = true;
                queue.push_back(nodeIdx);
                bfsResult[startIdx].push_back(nodeIdx);
            }
        }
    }

    delete[] visited;
}

void DFSRecursive(Graph graph, int startIdx, bool visited[]) {
    visited[startIdx] = true;
    cout << startIdx << " ";
    dfsSequence.push_back(startIdx);

    for (int i = 0; i < static_cast<int>(graph.getAdjNodes()[startIdx].size()); ++i) {
        int nodeIdx = graph.getAdjNodes()[startIdx].at(i);
        if (!visited[nodeIdx]) {
            dfsResult[startIdx].push_back(nodeIdx);
            DFSRecursive(graph, nodeIdx, visited);
        }
    }
}

void DFS(Graph graph, int startIdx) {
    bool* visited = new bool[graph.getNumNodes()];
    for (int i = 0; i < graph.getNumNodes(); ++i) {
        visited[i] = false;
    }

    dfsSequence.clear();
    dfsResult.assign(graph.getNumNodes(), vector<int>());
    DFSRecursive(graph, startIdx, visited);

    delete[] visited;
}

void buildGraphFigure64() {
    graph.setIsDirected(true);

    graph.addNode(0.00f, 0.20f);   // 0
    graph.addNode(-0.52f, 0.72f);  // 1
    graph.addNode(0.52f, 0.72f);   // 2
    graph.addNode(0.00f, -0.22f);  // 3
    graph.addNode(-0.52f, -0.72f); // 4
    graph.addNode(0.52f, -0.72f);  // 5

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
    buildGraphFigure64();

    int startIdx = 0;
    bool noGui = argc > 1 && string(argv[1]) == "--nogui";

    cout << "BFS mulai dari node " << startIdx << "\n";
    BFS(graph, startIdx);
    cout << endl;

    cout << "DFS mulai dari node " << startIdx << "\n";
    DFS(graph, startIdx);
    cout << endl;

    if (noGui) {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum 6 - BFS dan DFS");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
