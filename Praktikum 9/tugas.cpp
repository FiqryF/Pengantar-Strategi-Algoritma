#include <windows.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

#include <GL/freeglut.h>

#include "draws.h"
#include "graph.h"

using namespace std;

const int NUM_NODES = 7;
const int TARGET_NODE = 6;

struct WeightedEdge {
    int target;
    float weight;
};

// Weighted adjacency list untuk graf Gambar 9.2.
vector<WeightedEdge> adjList[NUM_NODES];

Graph graph;
vector<int> pathSequence;
float finalCost = 0.0f;

void addWeightedEdge(int source, int target, float weight) {
    adjList[source].push_back(WeightedEdge{target, weight});
    adjList[target].push_back(WeightedEdge{source, weight});
    graph.addEdge(source, target, weight);
}

void buildGraphFigure92() {
    graph.setIsDirected(false);

    // Posisi node dibuat berbeda dari graf praktikum, tetapi adjacency list tetap sama.
    graph.addNode(-0.88f, 0.18f);  // 0
    graph.addNode(-0.18f, 0.82f);  // 1
    graph.addNode(-0.46f, -0.46f); // 2
    graph.addNode(0.42f, 0.50f);   // 3
    graph.addNode(0.10f, -0.12f);  // 4
    graph.addNode(0.62f, -0.76f);  // 5
    graph.addNode(0.88f, 0.02f);   // 6

    addWeightedEdge(0, 1, 3.0f);
    addWeightedEdge(0, 2, 4.0f);
    addWeightedEdge(0, 3, 5.0f);
    addWeightedEdge(1, 3, 2.0f);
    addWeightedEdge(2, 4, 4.0f);
    addWeightedEdge(3, 4, 2.0f);
    addWeightedEdge(4, 5, 1.0f);
    addWeightedEdge(4, 6, 5.0f);
    addWeightedEdge(5, 6, 3.0f);
}

float heuristic(int nodeIdx) {
    // Heuristik sesuai pre-test: banyaknya busur minimal menuju target.
    vector<int> distance(NUM_NODES, -1);
    queue<int> q;

    distance[nodeIdx] = 0;
    q.push(nodeIdx);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == TARGET_NODE) {
            return static_cast<float>(distance[current]);
        }

        for (int i = 0; i < static_cast<int>(adjList[current].size()); ++i) {
            int next = adjList[current][i].target;
            if (distance[next] == -1) {
                distance[next] = distance[current] + 1;
                q.push(next);
            }
        }
    }

    return 9999.0f;
}

void AStar(int startNode, int targetNode) {
    struct QueueNode {
        int node;
        float gCost;
        float fCost;

        bool operator<(const QueueNode& other) const {
            if (fCost == other.fCost) {
                return gCost > other.gCost;
            }
            return fCost > other.fCost;
        }
    };

    vector<float> gCost(NUM_NODES, numeric_limits<float>::infinity());
    vector<int> previous(NUM_NODES, -1);
    vector<bool> closed(NUM_NODES, false);
    priority_queue<QueueNode> openSet;

    gCost[startNode] = 0.0f;
    openSet.push(QueueNode{startNode, 0.0f, heuristic(startNode)});

    cout << "Post-Test Praktikum 9" << endl;
    cout << "Representasi graf: weighted adjacency list" << endl;

    while (!openSet.empty()) {
        QueueNode current = openSet.top();
        openSet.pop();

        if (closed[current.node]) {
            continue;
        }

        closed[current.node] = true;

        if (current.node == targetNode) {
            break;
        }

        for (int i = 0; i < static_cast<int>(adjList[current.node].size()); ++i) {
            WeightedEdge edge = adjList[current.node][i];
            float tentativeG = gCost[current.node] + edge.weight;

            if (tentativeG < gCost[edge.target]) {
                previous[edge.target] = current.node;
                gCost[edge.target] = tentativeG;
                float fCost = tentativeG + heuristic(edge.target);
                openSet.push(QueueNode{edge.target, tentativeG, fCost});
            }
        }
    }

    pathSequence.clear();
    for (int node = targetNode; node != -1; node = previous[node]) {
        pathSequence.push_back(node);
    }
    reverse(pathSequence.begin(), pathSequence.end());

    finalCost = gCost[targetNode];

    cout << "Final solution = ";
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        cout << pathSequence[i];
        if (i + 1 < static_cast<int>(pathSequence.size())) {
            cout << " ";
        }
    }
    cout << " = " << finalCost << endl;
}

void printAdjacencyList() {
    cout << "Weighted adjacency list:" << endl;
    for (int i = 0; i < NUM_NODES; ++i) {
        cout << i << " -> ";
        for (int j = 0; j < static_cast<int>(adjList[i].size()); ++j) {
            cout << "(" << adjList[i][j].target << ", " << adjList[i][j].weight << ")";
            if (j + 1 < static_cast<int>(adjList[i].size())) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void drawResultPath() {
    for (int i = 1; i < static_cast<int>(pathSequence.size()); ++i) {
        int source = pathSequence[i - 1];
        int target = pathSequence[i];

        drawLine(
            graph.getNodePosition(source),
            graph.getNodePosition(target),
            Vec3(1.0f, 0.0f, 1.0f, 1.0f),
            4.0f
        );
    }

    drawText(-0.94f, 0.92f, "Post-Test Praktikum 9 - Weighted Adjacency List", Vec3(1.0f, 1.0f, 1.0f, 1.0f));

    string result = "Final solution = ";
    for (int i = 0; i < static_cast<int>(pathSequence.size()); ++i) {
        result += to_string(pathSequence[i]);
        if (i + 1 < static_cast<int>(pathSequence.size())) {
            result += " -> ";
        }
    }
    result += " = " + to_string(static_cast<int>(finalCost));

    drawText(-0.94f, -0.92f, result.c_str(), Vec3(1.0f, 0.0f, 1.0f, 1.0f));
}

void displayGraph() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawResultPath();
    drawEdges(graph);
    drawNodes(graph);

    glutSwapBuffers();
}

void reshapeView(int width, int height) {
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

int main(int argc, char** argv) {
    buildGraphFigure92();
    printAdjacencyList();
    AStar(0, TARGET_NODE);

    if (argc > 1 && string(argv[1]) == "--nogui") {
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Post-Test Praktikum 9 - A*");
    initView();
    glutDisplayFunc(displayGraph);
    glutReshapeFunc(reshapeView);
    glutMainLoop();

    return 0;
}
