#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "ActorAnalyzer.h"

void run(ActorAnalyzer& actorAnalyzer, int to, int from, int k = 1, int nodeLimit = 10);

int main(int argc, char** argv) {
    auto start = std::chrono::system_clock::now();
    ActorAnalyzer AA("../csv_files/movies_id.csv");
    auto stop = std::chrono::system_clock::now();
    std::cout << "Time to construct ActorAnalyzer: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    int actor1 = std::atoi(argv[1]);
    int actor2 = std::atoi(argv[2]);

    run(AA, actor1, actor2);
    return 0;
}

void run(ActorAnalyzer& AA, int to, int from, int k, int nodeLimit) {
    auto start = std::chrono::system_clock::now();
    std::vector<int> dijkstraPath = AA.dijkstra(to, from);
    auto stop = std::chrono::system_clock::now();
    std::cout << "Time to run Dijkstra's Algorithm: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    std::vector<int> astarPath = AA.astarsearch(to, from);
    stop = std::chrono::system_clock::now();
    std::cout << "Time to run A* Search Algorithm: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
    << " ms" << std::endl;

    std::unordered_set<int> nodes = AA.kSurrondingNodes(dijkstraPath, 1, 1);

    std::ofstream adjList("../output/adjList.txt");
    std::ofstream actors("../output/actors.txt");
    std::ofstream dijkstraFile("../output/dijkstra.txt");
    std::ofstream astarFile("../output/astar.txt");

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

    if (dijkstraFile.is_open()) {
        dijkstraFile << AA.PrintPath(dijkstraPath);
        dijkstraFile.close();
    }
    else {
        std::cout << "error opening dijkstra.txt" << std::endl;
    }

    if (astarFile.is_open()) {

        astarFile << AA.PrintPath(astarPath);
        astarFile.close();

    }
    else {

        std::cout << "error opening astar.txt" << std::endl;

    }
}