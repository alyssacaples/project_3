#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include "Graph.h"

void parseLine (
    const std::string& line,
    std::unordered_map<int,std::string>& movies,
    std::unordered_map<int,std::string>& actors,
    std::vector<std::vector<int>>& inTable
);

int main() {
    std::ofstream log("log.txt");
    if (log.is_open()) {
        std::ifstream file("movies_id.csv");
        if (file.is_open()) {
            std::string line;
            std::getline(file,line);
            std::string columns = line;
            std::unordered_map<int,std::string> movies;
            std::unordered_map<int,std::string> actors;
            std::vector<std::vector<int>> inTable;
            auto start = std::chrono::system_clock::now();
            while(std::getline(file, line)) {
                parseLine(line, movies, actors, inTable);
            }
            auto stop = std::chrono::system_clock::now();
            std::cout << "Time to read csv into inTable: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;
            file.close();
            start = std::chrono::system_clock::now();
            Graph actorGraph(inTable);
            stop = std::chrono::system_clock::now();
            std::cout << "Time to construct Graph: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;
            start = std::chrono::system_clock::now();
            actorGraph.invertWeights();
            stop = std::chrono::system_clock::now();
            std::cout << "Time to invertWeights: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;
            int tomHanksID = 31;
            for (int actor : actorGraph.getAdjacent(tomHanksID)) {
                std::cout << actor << ' ' << actors[actor]  << ' ' << actorGraph.getWeight(tomHanksID, actor) << std::endl;
            }
        }
        else {
            log << "Error opening movies_id.csv" << std::endl;
        }
    }
    else {
        std::cout << "Error opening log file..." << std::endl;
    }
    return 0;
}

void parseLine (
    const std::string& line,
    std::unordered_map<int,std::string>& movies,
    std::unordered_map<int,std::string>& actors,
    std::vector<std::vector<int>>& inTable
) {
    int left = 0, right = 0;
    // find the movieID
    while (line[left++] != '{');
    while (line[right] != '}') right++;
    std::string movieID = line.substr(left, right-left);
    left = right = right+1;
    // find the movieTitle
    while (line[left++] != '{');
    while (line[right] != '}') right++;
    std::string movieTitle = line.substr(left,right-left);
    left = right = right+1;
    // add the movieID and movieTitle to movies
    movies[std::stoi(movieID)] = movieTitle;
    // find the list of actors
    while (line[left++] != '{');
    while (line[right] != '}') right++;
    std::string actorList = line.substr(left, right-left);
    // make space for the incoming actorList
    inTable.emplace_back();
    left = right = 0;
    while (right < actorList.length()) {
        while (actorList[left++] != '(');
        while (actorList[right] != ')') right++;
        std::string actorIdNamePair = actorList.substr(left, right-left);
        left = right = right + 1;
        int i = 0;
        while (actorIdNamePair[i] != ',') i++;
        std::string actorID = actorIdNamePair.substr(0, i);
        std::string actorName = actorIdNamePair.substr(i+1);
        // add the actorID and actorName to actors
        actors[std::stoi(actorID)] = actorName;
        // add the actorID to the incoming actorList
        inTable.back().push_back(std::stoi(actorID));
    }    
}