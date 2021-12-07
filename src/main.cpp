#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "ActorAnalyzer.h"

int main() {
    auto start = std::chrono::system_clock::now();
    ActorAnalyzer AA("../movies_id.csv");
    auto stop = std::chrono::system_clock::now();
    std::cout << "Time to construct ActorAnalyzer: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    std::vector<int> path = AA.dijkstra(31, 2963);

    std::unordered_set<int> nodes = AA.kSurrondingNodes(path, 1, 0);

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
    return 0;
}