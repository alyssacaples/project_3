#include "ActorAnalyzer.h"

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

inline static void parseLine (
    const std::string& line,
    std::unordered_map<int,Movie>& movies,
    std::unordered_map<int,Actor>& actors,
    std::vector<std::vector<int>>& inTable
);

ActorAnalyzer::ActorAnalyzer(const std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        std::getline(file,line);
        std::string columns = line;
        std::vector<std::vector<int>> inTable;
        while (std::getline(file, line)) {
            parseLine(line,movies,actors,inTable);
        }
        graph.buildGraph(inTable);
        graph.invertWeights();
    }
}

std::string ActorAnalyzer::PrintMovies(int actorID) {
    if (actors.find(actorID) == actors.end()) return "";
    const std::vector<int>& movies = actors[actorID].movies;
    std::string movieList;
    for (int movie : movies) {
        movieList.append('"' + this->movies[movie].name + '"' + ',');
    }
    if (!movieList.empty()) movieList.pop_back(); // eliminate extra ','
    return movieList;
}

int ActorAnalyzer::DegreesOfSeperatiom(int from, int to) {
    std::vector<int> path = graph.bfs(from, to);
    if (path.size() == 0 && from != to) return -1; // path does not exist!!!
    return path.size();
}

inline static void parseLine (
    const std::string& line,
    std::unordered_map<int,Movie>& movies,
    std::unordered_map<int,Actor>& actors,
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
    movies[std::stoi(movieID)] = {movieTitle};
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
        // add the actorID and actorName to actors + add the movie
        actors[std::stoi(actorID)].name = actorName;
        actors[std::stoi(actorID)].movies.push_back(std::stoi(movieID));
        // add the actorID to the incoming actorList
        inTable.back().push_back(std::stoi(actorID));
    }    
}

bool ActorAnalyzer::isConnected() {
    return graph.isConnected();
}