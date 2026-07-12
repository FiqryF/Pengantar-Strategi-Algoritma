#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <limits>
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
    std::vector<std::vector<float> > distance;

public:
    Graph() : directed(false) {}

    void setIsDirected(bool value) {
        directed = value;
    }

    bool getIsDirected() const {
        return directed;
    }

    void setNumLevels(int) {
        // Kept for compatibility with the practicum template.
    }

    int getNumNodes() const {
        return static_cast<int>(positions.size());
    }

    void addNode(float x, float y) {
        positions.push_back(NodePosition{x, y});
        adjacency.push_back(std::vector<int>());

        for (int i = 0; i < static_cast<int>(distance.size()); ++i) {
            distance[i].push_back(std::numeric_limits<float>::infinity());
        }

        distance.push_back(std::vector<float>(positions.size(), std::numeric_limits<float>::infinity()));
        distance.back()[positions.size() - 1] = 0.0f;
    }

    void addEdge(int source, int target, float weight) {
        if (!isValidNode(source) || !isValidNode(target)) {
            return;
        }

        adjacency[source].push_back(target);
        distance[source][target] = weight;

        if (!directed) {
            adjacency[target].push_back(source);
            distance[target][source] = weight;
        }
    }

    bool isValidNode(int index) const {
        return index >= 0 && index < getNumNodes();
    }

    const std::vector<std::vector<int> >& getAdjNodes() const {
        return adjacency;
    }

    const std::vector<std::vector<float> >& getNodeDistance() const {
        return distance;
    }

    NodePosition getNodePosition(int index) const {
        return positions[index];
    }

    float getNodeDistanceTo(int source, int target) const {
        if (!isValidNode(source) || !isValidNode(target)) {
            return std::numeric_limits<float>::infinity();
        }

        return distance[source][target];
    }

    void estimateNodePosition() {
        // Positions are assigned manually in this practicum.
    }
};

#endif
