/* file = ActorAnalyzer.h
 * Contains ActorAnalyzer class and function declarations
 */

#ifndef ACTORANALYZER_H_GUARD
#define ACTORANALYZER_H_GUARD

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Graph.h"

struct Movie {
    std::string name;
};

struct Actor {
    std::string name;
    std::vector<int> movies;
};

class ActorAnalyzer {
    private:
        Graph graph;
        std::unordered_map<int,Movie> movies;
        std::unordered_map<int,Actor> actors;
    public:
        ActorAnalyzer() = delete;
        ActorAnalyzer(const std::string filename);
        std::string PrintMovies(int actorID);
        int DegreesOfSeparation(int from, int to);
        bool isConnected();
        std::vector<int> dijkstra(int from, int to);
        std::unordered_set<int> kSurrondingNodes(const std::vector<int>& path, int k, int nodeLimit);
        std::string PrintAdjacencyList(const std::unordered_set<int>& nodes);
        std::string PrintActors(const std::unordered_set<int>& nodes);
        std::string PrintPath(const std::vector<int>& path);
};

#endif /* ACTORANALYZER_H_GUARD */