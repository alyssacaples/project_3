/* file = ActorAnalyzer.h
 * Contains ActorAnalyzer class and function declarations
 */

#ifndef ACTORANALYZER_H_GUARD
#define ACTORANALYZER_H_GUARD

#include <string>
#include <unordered_map>
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
        ActorAnalyzer() = default;
        ActorAnalyzer(const std::string filename);
        std::string PrintMovies(int actorID);
        int DegreesOfSeperatiom(int from, int to);
        bool isConnected();
};

#endif /* ACTORANALYZER_H_GUARD */