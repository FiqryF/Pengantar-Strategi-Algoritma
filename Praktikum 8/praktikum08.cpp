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

Graph graph;
vector<int> pathSequence;
int bestCost = INT_MAX;
char markText[64];

int firstMin(int nodeIdx, const vector<vector<int> >& dist) {
    int minValue = INT_MAX;
    for (int i = 0; i < static_cast<int>(dist.size()); ++i) {
        if (i != nodeIdx && dist[nodeIdx][i] > 0) {
            minValue = min(minValue, dist[nodeIdx][i]);
        }
    }
    return minValue;
}

int secondMin(int nodeIdx, const vector<vector<int> >& dist) {
    int first = INT_MAX;
    int second = INT_MAX;

    for (int i = 0; i < static_cast<int>(dist.size()); ++i) {
        if (i == nodeIdx || dist[nodeIdx][i] == 0) {
            continue;
        }

        if (dist[nodeIdx][i] <= first) {
            second = first;
            first = dist[nodeIdx][i];
        } else if (dist[nodeIdx][i] < second) {
            second = dist[nodeIdx][i];
        }
    }

    return second;
}

void BBRecursive(
    const vector<vector<int> >& dist,
    vector<int>& currentPath,
    vector<bool>& visited,
    int currentBound,
    int currentCost,
    int level
) {
    int numNodes = static_cast<int>(dist.size());

    if (level == numNodes) {
        int last = currentPath[level - 1];
        int first = currentPath[0];

        if (dist[last][first] != 0) {
            int totalCost = currentCost + dist[last][first];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                pathSequence = currentPath;
                pathSequence.push_back(first);
            }
        }
        return;
    }

    for (int i = 0; i < numNodes; ++i) {
        int previous = currentPath[level - 1];
        if (dist[previous][i] != 0 && !visited[i]) {
            int savedBound = currentBound;
            int nextCost = currentCost + dist[previous][i];

            if (level == 1) {
                currentBound -= (firstMin(previous, dist) + firstMin(i, dist)) / 2;
            } else {
                currentBound -= (secondMin(previous, dist) + firstMin(i, dist)) / 2;
            }

            int estimatedCost = nextCost + currentBound;
            if (estimatedCost < bestCost) {
                currentPath[level] = i;
                visited[i] = true;

                BBRecursive(dist, currentPath, visited, currentBound, nextCost, level + 1);
            }

            currentBound = savedBound;
            visited[i] = false;
        }
    }
}

void BB(int startIdx) {
    const vector<vector<int> >& dist = graph.getNodeDistance();
    int numNodes = graph.getNumNodes();
    int currentBound = 0;

    bestCost = INT_MAX;
    pathSequence.clear();

    vector<int> currentPath(numNodes, -1);
    vector<bool> visited(numNodes, false);

    for (int i = 0; i < numNodes; ++i) {
        currentBound += firstMin(i, dist) + secondMin(i, dist);
    }

    currentBound = (currentBound + 1) / 2;
    currentPath[0] = startIdx;
    visited[startIdx] = true;

    BBRecursive(dist, currentPath, visited, currentBound, 0, 1);

    cout << "Final solusi = ";
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        cout << pathSequence[i];
        if (i + 1 < static_cast<int>(pathSequence.size())) {
            cout << " ";
        }
    }
    cout << " = " << bestCost << endl;
}

void drawResult() {
    for (int i = 1; i < static_cast<int>(pathSequence.size()); ++i) {
        int source = pathSequence[i - 1];
        int target = pathSequence[i];
        drawLine(
            graph.getNodePosition(source),
            graph.getNodePosition(target),
            Vec3(1.0f, 0.0f, 1.0f),
            4.0f
        );
    }

    if (!pathSequence.empty()) {
        int startNode = pathSequence[0];
        NodePosition position = graph.getNodePosition(startNode);
        drawText(position.x + 0.08f, position.y + 0.08f, "start", Vec3(1.0f, 0.0f, 1.0f));
    }

    std::snprintf(markText, sizeof(markText), "Cost minimum = %d", bestCost);
    drawText(-0.92f, 0.88f, markText, Vec3(1.0f, 1.0f, 1.0f));
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawEdges(graph);
    drawResult();
    drawNodes(graph);

    glutSwapBuffers();
}

void buildGraphFigure83() {
    graph.setIsDirected(false);

    graph.addNode(0.00f, 0.72f);   // 0
    graph.addNode(-0.62f, -0.58f); // 1
    graph.addNode(0.62f, -0.58f);  // 2
    graph.addNode(0.00f, 0.02f);   // 3

    graph.addEdge(0, 1, 25);
    graph.addEdge(0, 2, 15);
    graph.addEdge(0, 3, 20);
    graph.addEdge(1, 2, 35);
    graph.addEdge(1, 3, 10);
    graph.addEdge(2, 3, 30);
}

int main(int argc, char** argv) {
    buildGraphFigure83();
    BB(0);

    bool noGui = argc > 1 && string(argv[1]) == "--nogui";
    if (noGui) {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Praktikum 8 - Branch and Bound TSP");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
