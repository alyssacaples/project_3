#include "Graph.h"

#include <vector>
#include <unordered_map>
#include <utility>

Graph::Graph(const std::vector<std::vector<int>>& inTable) {
    for (const std::vector<int>& row : inTable) {
        for (const int& fromActorID : row) {
            for (const int& toActorID : row) {
                if (fromActorID != toActorID) {
                    this->insertEdge(fromActorID, toActorID, 
                    this->getWeight(fromActorID, toActorID) + 1);
                }
            }
        } 
    }
}

void Graph::buildGraph(const std::vector<std::vector<int>>& inTable) {
    for (const std::vector<int>& row : inTable) {
        for (const int& fromActorID : row) {
            for (const int& toActorID : row) {
                if (fromActorID != toActorID) {
                    this->insertEdge(fromActorID, toActorID, 
                    this->getWeight(fromActorID, toActorID) + 1);
                }
            }
        } 
    }
}

void Graph::insertEdge(int from, int to, float weight) {
    // check if 'from' has been mapped yet
    if (V.find(from) == V.end()) {
        V[from] = numVertices++;
        G.resize(numVertices);
    }
    // check if 'to' has been mapped yet
    if (V.find(from) == V.end()) {
        V[to] = numVertices++;
        G.resize(numVertices);
    }
    // assign the weight
    G[V[from]][to] = weight;
}

float Graph::getWeight(int from, int to) {
    // check if 'from' exists before accessing adjacent vertices
    if (V.find(from) == V.end()) return 0;
    // check if 'to' is adjacent to 'from' before accessing weight
    if (G[V[from]].find(to) == G[V[from]].end()) return 0;
    // return weight of edge: from -> to
    return G[V[from]][to];
}

bool Graph::isEdge(int from, int to) {
    // check if 'from' exists before accessing adjacent vertices
    if (V.find(from) == V.end()) return false;
    // search for 'to' in adjacent edges
    return G[V[from]].find(to) != G[V[from]].end();
}

std::vector<int> Graph::getAdjacent(int vertex) {
    std::vector<int> adjacents;
    // check if 'vertex' exists before accessing adjacent vertices
    if (V.find(vertex) != V.end()) {
        // append every adjacent vertex
        for (const std::pair<int,float>& value : G[V[vertex]]) {
            adjacents.push_back(value.first);
        }
    }
    return adjacents;
}

void Graph::invertWeights() {
    for (std::unordered_map<int,float>& adjacents : G) {
        for (std::pair<const int,float>& value : adjacents) {
            value.second = 1/value.second;
        }
    }
}

int Graph::getNumVertices() {
    return numVertices;
}