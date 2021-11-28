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
    std::cout << "Time to construct ActorAnalyzer: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;

    start = std::chrono::system_clock::now();
    std::cout << AA.DegreesOfSeperation(31,-1) << std::endl; // should print "-1"
    stop = std::chrono::system_clock::now();
    std::cout << "Time to run bfs: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;

    AA.PrintMovies(31);

    start = std::chrono::system_clock::now();
    std::cout << (AA.isConnected() ? "connected" : "not connected") << std::endl;
    stop = std::chrono::system_clock::now();
    std::cout << "Time to run isConnected: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;

    return 0;
}