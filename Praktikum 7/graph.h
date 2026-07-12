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

public:
    Graph() : directed(true) {}

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
    }

    void addEdge(int source, int target) {
        if (source < 0 || source >= getNumNodes() || target < 0 || target >= getNumNodes()) {
            return;
        }

        adjacency[source].push_back(target);

        if (!directed) {
            adjacency[target].push_back(source);
        }
    }

    const std::vector<std::vector<int> >& getAdjNodes() const {
        return adjacency;
    }

    NodePosition getNodePosition(int index) const {
        return positions[index];
    }
};

#endif
