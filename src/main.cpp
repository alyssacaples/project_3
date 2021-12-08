#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "ActorAnalyzer.h"

void run(ActorAnalyzer& actorAnalyzer, int to, int from, int k = 1, int nodeLimit = 10);

int main() {
    auto start = std::chrono::system_clock::now();
    ActorAnalyzer AA("../movies_id.csv");
    auto stop = std::chrono::system_clock::now();
    std::cout << "Time to construct ActorAnalyzer: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    run(AA, 31, 2963);
    return 0;
}

void run(ActorAnalyzer& AA, int to, int from, int k, int nodeLimit) {
    auto start = std::chrono::system_clock::now();
    std::vector<int> path = AA.astarsearch(to, from);
    auto stop = std::chrono::system_clock::now();
    std::cout << "Time to run Dijkstra's Algorithm: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    //AA.bellmanford(to, from);

    std::unordered_set<int> nodes = AA.kSurrondingNodes(path, 1, 10);

    std::ofstream adjList("../output/adjList.txt");
    std::ofstream actors("../output/actors.txt");
    std::ofstream pathFile("../output/path.txt");

    if (adjList.is_open()) {
        adjList << AA.PrintAdjacencyList(nodes);
        adjList.close();
    } else {
        std::cout << "error opening adjList.txt" << std::endl;
    }

    if (actors.is_open()) {
        actors << AA.PrintActors(nodes);
        actors.close();
    } else {
        std::cout << "error opening actors.txt" << std::endl;
    }

    if (pathFile.is_open()) {
        pathFile << AA.PrintPath(path);
        pathFile.close();
    }
    else {
        std::cout << "error opening path.txt" << std::endl;
    }
}