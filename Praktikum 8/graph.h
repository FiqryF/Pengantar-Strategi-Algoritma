#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct NodePosition {
    float x;
    float y;
};

class Graph {
private:
    bool directed;
    std::vector<NodePosition> positions;
    std::vector<std::vector<int> > adjacency;
    std::vector<std::vector<int> > distanceMatrix;

public:
    Graph() : directed(false) {}

    void setIsDirected(bool value) {
        directed = value;
    }

    bool getIsDirected() const {
        return directed;
    }

    int getNumNodes() const {
        return static_cast<int>(positions.size());
    }

    void addNode(float x, float y) {
        positions.push_back(NodePosition{x, y});
        adjacency.push_back(std::vector<int>());

        for (int i = 0; i < static_cast<int>(distanceMatrix.size()); ++i) {
            distanceMatrix[i].push_back(0);
        }

        distanceMatrix.push_back(std::vector<int>(positions.size(), 0));
    }

    void addEdge(int source, int target, int distance) {
        if (source < 0 || source >= getNumNodes() || target < 0 || target >= getNumNodes()) {
            return;
        }

        adjacency[source].push_back(target);
        distanceMatrix[source][target] = distance;

        if (!directed) {
            adjacency[target].push_back(source);
            distanceMatrix[target][source] = distance;
        }
    }

    const std::vector<std::vector<int> >& getAdjNodes() const {
        return adjacency;
    }

    const std::vector<std::vector<int> >& getNodeDistance() const {
        return distanceMatrix;
    }

    NodePosition getNodePosition(int index) const {
        return positions[index];
    }
};

#endif
