#include "Graph.h"


#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>
#include <limits>

#include <iostream> // debugging only

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

bool Graph::isConnected() {
    std::unordered_set<int> visited;
    std::queue<int> q;
    // verify that the graph is not empty
    if (V.begin() == V.end()) return false;
    int source = V.begin()->first;
    q.push(source);
    visited.insert(source);
    while(!q.empty()) {
        int vertex = q.front(); q.pop();
        std::vector<int> adj = getAdjacent(vertex);
        for (int v : adj) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                q.push(v);
            }
        }
    }
    for (auto& elem : V)
        if (visited.find(elem.first) == visited.end()) return false;
    return true;
}

std::vector<int> Graph::bfs(int from, int to) {
    if (from == to) return {from};

    std::unordered_set<int> visited;
    std::unordered_map<int,int> parents;
    std::queue<int> q;
    bool toFound = false;
    q.push(from);
    visited.insert(from);
    while(!q.empty()) {
        int vertex = q.front(); q.pop();
        std::vector<int> adj = getAdjacent(vertex);
        for (int v : adj) {
            if (visited.find(v) == visited.end()) {
                visited.insert(v);
                q.push(v);
                parents[v] = vertex;
                if (v == to) {
                    toFound = true;
                    break;
                }
            }
        }
        if (toFound) break;
    }
    if (!toFound) {
        return {};
    }

    // construct the path from parents
    std::vector<int> path;
    int currVert = to;
    while (parents.find(currVert) != parents.end()) {
        path.push_back(currVert);
        currVert = parents[currVert];
    }
    path.push_back(currVert);
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Graph::dijkstra(int from, int to) {
    if (from == to) return {from};
    
    std::vector<bool> visited(numVertices,false);
    std::vector<int> parents(numVertices,-1);
    std::vector<float> cost(numVertices, std::numeric_limits<float>::infinity());
    bool toFound = false;

    // pair::first is the cost, pair::second is the vertex
    std::priority_queue<std::pair<float,int>, std::vector<std::pair<float,int>>, std::greater<std::pair<float,int>>> pq;

    cost[V[from]] = 0;
    pq.push(std::make_pair(0,from));

    while(!pq.empty()) {
        std::pair<float,int> vertex = pq.top(); pq.pop();
        
        // check if the cost of the vertex has been relaxed before continuing
        if (visited[V[vertex.second]])
            continue; // this element in the pq is "invalid", we already processed the node
        visited[V[vertex.second]] = true;
            
        // early stopping condition once we process the to vertex
        if (vertex.second == to) break;

        //int baseCost = cost[V[vertex.second]];
        float baseCost = vertex.first;
        const std::vector<int> adj = getAdjacent(vertex.second);
        for (const int v : adj) {
            // "relax" every adjacent vertex v that has not been visited
            if (!visited[V[v]] && baseCost + getWeight(vertex.second, v) < cost[V[v]]) {
                cost[V[v]] = baseCost + getWeight(vertex.second, v);
                parents[V[v]] = vertex.second;
                pq.push(std::make_pair(cost[V[v]], v));
                if (v == to) {
                    toFound = true;
                }
            }
        }
    }
    if (!toFound) return {};

    // construct the path from parents
    std::vector<int> path;
    int currVert = to;
    while (currVert != -1) {
        path.push_back(currVert);
        currVert = parents[V[currVert]];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Graph::a_star(int from, int to) {
    return {};
}