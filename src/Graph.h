/* file = Graph.h
 * Contains Graph class and function declarations
 */

#ifndef GRAPH_H_GUARD
#define GRAPH_H_GUARD

#include <vector>
#include <unordered_map>

class Graph {
    private:
        std::unordered_map<int,int> V;
        std::vector<std::unordered_map<int,float>> G;
        int numVertices = 0;
    public:
        Graph() = default;

        /* constructs the Graph out of an input table with this schema:
        movieID | actorIDs
        862     | 31, 12898, 7167, 12899, ...
        8844    | 2157, 8537, 205, 145151, ...
        15602   | 6837, 3151, 13567, 16757, ...
        ...     | ...
        */
        Graph(const std::vector<std::pair<int,std::vector<int>>>& inTable);

        // insert an edge: from -> to
        // if edge already exists, overwrite weight
        void insertEdge(int from, int to, float weight);

        // returns the weight of an edge if it exists
        // otherwise, return 0
        float getWeight(int from, int to);

        // return true if the edge: from- -> to exists
        bool isEdge(int from, int to);

        // returns a vector of the adjacent vertices
        std::vector<int> getAdjacent(int vertex);

        // inverts all the weights (e.g. 2 ==> 0.5)
        // Should not called until after all the edges
        // have been added and/or incremented
        void invertWeights();

        // returns numVertices
        int getNumVertices();
};

#endif /* GRAPH_H_GUARD */