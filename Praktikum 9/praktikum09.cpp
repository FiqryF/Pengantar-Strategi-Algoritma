#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

Graph graph;
vector<int> pathSequence;
float finalCost = 0.0f;
char markText[32];

int windowWidth = 900;
int windowHeight = 700;

int heuristicEdgeCount(const Graph& graph, int startIdx, int endIdx) {
    vector<int> distance(graph.getNumNodes(), -1);
    queue<int> queueNodes;

    distance[startIdx] = 0;
    queueNodes.push(startIdx);

    while (!queueNodes.empty()) {
        int current = queueNodes.front();
        queueNodes.pop();

        if (current == endIdx) {
            return distance[current];
        }

        const vector<int>& neighbors = graph.getAdjNodes()[current];
        for (int i = 0; i < static_cast<int>(neighbors.size()); ++i) {
            int next = neighbors[i];
            if (distance[next] == -1) {
                distance[next] = distance[current] + 1;
                queueNodes.push(next);
            }
        }
    }

    return 9999;
}

float computeHeuristic(const Graph& graph, int nodeIdx, int endIdx) {
    return static_cast<float>(heuristicEdgeCount(graph, nodeIdx, endIdx));
}

float computeCost(float distanceToTravel, float distanceToTarget) {
    return distanceToTravel + distanceToTarget;
}

float getPathCost(const Graph& graph, const vector<int>& path) {
    float total = 0.0f;

    for (int i = 1; i < static_cast<int>(path.size()); ++i) {
        total += graph.getNodeDistanceTo(path[i - 1], path[i]);
    }

    return total;
}

void AStar(const Graph& graph, int startIdx, int endIdx) {
    struct QueueNode {
        int nodeIdx;
        float fCost;
        float gCost;

        bool operator<(const QueueNode& other) const {
            if (fCost == other.fCost) {
                return gCost > other.gCost;
            }

            return fCost > other.fCost;
        }
    };

    const int nodeCount = graph.getNumNodes();
    vector<float> gCost(nodeCount, numeric_limits<float>::infinity());
    vector<int> previous(nodeCount, -1);
    vector<bool> visited(nodeCount, false);
    priority_queue<QueueNode> openSet;

    gCost[startIdx] = 0.0f;
    openSet.push(QueueNode{startIdx, computeHeuristic(graph, startIdx, endIdx), 0.0f});

    cout << "Proses A* dari node " << startIdx << " ke node " << endIdx << endl;
    cout << "----------------------------------------" << endl;

    while (!openSet.empty()) {
        QueueNode current = openSet.top();
        openSet.pop();

        if (visited[current.nodeIdx]) {
            continue;
        }

        visited[current.nodeIdx] = true;

        cout << "Ekspansi node " << current.nodeIdx
             << " | g(n)=" << current.gCost
             << " | h(n)=" << computeHeuristic(graph, current.nodeIdx, endIdx)
             << " | f(n)=" << current.fCost << endl;

        if (current.nodeIdx == endIdx) {
            break;
        }

        const vector<int>& neighbors = graph.getAdjNodes()[current.nodeIdx];
        for (int i = 0; i < static_cast<int>(neighbors.size()); ++i) {
            int neighborIdx = neighbors[i];
            float edgeCost = graph.getNodeDistanceTo(current.nodeIdx, neighborIdx);
            float tentativeGCost = gCost[current.nodeIdx] + edgeCost;

            if (tentativeGCost < gCost[neighborIdx]) {
                previous[neighborIdx] = current.nodeIdx;
                gCost[neighborIdx] = tentativeGCost;
                float hCost = computeHeuristic(graph, neighborIdx, endIdx);
                float fCost = computeCost(tentativeGCost, hCost);

                openSet.push(QueueNode{neighborIdx, fCost, tentativeGCost});

                cout << "  Kandidat node " << neighborIdx
                     << " | g(n)=" << tentativeGCost
                     << " | h(n)=" << hCost
                     << " | f(n)=" << fCost << endl;
            }
        }
    }

    pathSequence.clear();
    for (int node = endIdx; node != -1; node = previous[node]) {
        pathSequence.push_back(node);
    }
    reverse(pathSequence.begin(), pathSequence.end());

    finalCost = getPathCost(graph, pathSequence);

    cout << "----------------------------------------" << endl;
    cout << "Final solution = ";
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        cout << pathSequence[i] << " ";
    }
    cout << "= " << finalCost << endl;
}

void drawResult() {
    glPushMatrix();

    float radius = 0.06f;
    for (int i = 1; i < static_cast<int>(pathSequence.size()); ++i) {
        int sourceIdx = pathSequence[i - 1];
        int targetIdx = pathSequence[i];

        drawLine(
            graph.getNodePosition(sourceIdx),
            graph.getNodePosition(targetIdx),
            Vec3(1.0f, 0.0f, 1.0f, 1.0f),
            4.0f
        );
    }

    if (!pathSequence.empty()) {
        sprintf(markText, "%s", "start");
        NodePosition startPosition = graph.getNodePosition(pathSequence.front());
        drawText(startPosition.x + 0.08f, startPosition.y + 0.04f, markText, Vec3(1.0f, 0.0f, 1.0f, 1.0f));

        sprintf(markText, "%s", "finish");
        NodePosition endPosition = graph.getNodePosition(pathSequence.back());
        drawText(endPosition.x + 0.08f, endPosition.y + 0.04f, markText, Vec3(1.0f, 0.0f, 1.0f, 1.0f));
    }

    glPopMatrix();
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawResult();
    drawEdges(graph);
    drawNodes(graph);

    char resultText[128];
    sprintf(resultText, "Final solution = ");
    string solutionText = resultText;
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        solutionText += to_string(pathSequence[i]) + " ";
    }
    solutionText += "= " + to_string(static_cast<int>(finalCost));
    drawText(-0.95f, 0.92f, solutionText.c_str(), Vec3(1.0f, 1.0f, 1.0f, 1.0f));

    glutSwapBuffers();
}

void reshapeView(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void initView() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void buildGraphFromFigure92() {
    graph.setIsDirected(false);
    graph.setNumLevels(4);

    graph.addNode(-0.75f, 0.70f);  // 0
    graph.addNode(0.55f, 0.70f);   // 1
    graph.addNode(-0.78f, 0.30f);  // 2
    graph.addNode(0.58f, 0.30f);   // 3
    graph.addNode(0.10f, -0.25f);  // 4
    graph.addNode(-0.80f, -0.70f); // 5
    graph.addNode(0.58f, -0.70f);  // 6

    graph.addEdge(0, 1, 3.0f);
    graph.addEdge(0, 2, 4.0f);
    graph.addEdge(0, 3, 5.0f);
    graph.addEdge(1, 3, 2.0f);
    graph.addEdge(2, 4, 4.0f);
    graph.addEdge(3, 4, 2.0f);
    graph.addEdge(4, 5, 1.0f);
    graph.addEdge(4, 6, 5.0f);
    graph.addEdge(5, 6, 3.0f);
}

int main(int argc, char** argv) {
    buildGraphFromFigure92();

    int startIdx = 0;
    int endIdx = 6;
    AStar(graph, startIdx, endIdx);

    if (argc > 1 && string(argv[1]) == "--nogui") {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum 9 - Algoritma A*");

    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
