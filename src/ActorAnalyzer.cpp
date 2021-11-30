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
        movieList.append('<' + this->movies[movie].name + '>' + ',');
    }
    if (!movieList.empty()) movieList.pop_back(); // eliminate extra ','
    return movieList;
}

int ActorAnalyzer::DegreesOfSeparation(int from, int to) {
    std::vector<int> path = graph.bfs(from, to);
    if (path.size() == 0 && from != to) return -1; // path does not exist!!!
    return path.size() - 1;
}

inline static void parseLine (
    const std::string& line,
    std::unordered_map<int,Movie>& movies,
    std::unordered_map<int,Actor>& actors,
    std::vector<std::vector<int>>& inTable
) {
    // get movie id and title information
    int leftBracket = 0; int rightBracket = 0;
    while (line[leftBracket++] != '{');
    while (line[rightBracket] != '}') rightBracket++;
    std::string movieInfo = line.substr(leftBracket, rightBracket-leftBracket);

    // move past current brackets
    leftBracket = ++rightBracket;

    // get actor id and name information
    while (line[leftBracket++] != '[');
    while (line[rightBracket] != ']') rightBracket++;
    std::string actorInfoString = line.substr(leftBracket, rightBracket-leftBracket);

    // move into current actorInfoString
    leftBracket = rightBracket = 0;

    // build a vector of actorInfo strings
    std::vector<std::string> actorInfoVector;

    while (rightBracket < actorInfoString.length()) {
        // find next actor info packet
        while(actorInfoString[leftBracket++] != '{');
        while(actorInfoString[rightBracket] != '}') rightBracket++;
        // add the actor info to the vector
        actorInfoVector.push_back(actorInfoString.substr(leftBracket, rightBracket-leftBracket));
        // move past current brackets
        leftBracket = ++rightBracket;
    }

    // process the movieInfo string for the id and title
    // use the : and , to get the id
    int left = 0; int right = 0;
    while (movieInfo[left++] != ':');
    while (movieInfo[right] != ',') right++;
    int movieID = std::stoi(movieInfo.substr(left, right-left));
    // move past ID toward title
    left = ++right;
    // use the < and > to get the title
    while (movieInfo[left++] != '<');
    while (movieInfo[right] != '>') right++;
    std::string movieTitle = movieInfo.substr(left, right-left);

    // add the movie id and title to the map
    movies[movieID] = {movieTitle};

    // generate a list of the actors in the current movie
    std::vector<int> coActors;
    
    for (const std::string& actorInfo : actorInfoVector) {
        // process each actorInfo for the id and name
        // use the : and , to get the id
        int left = 0; int right = 0;
        while (actorInfo[left++] != ':');
        while (actorInfo[right] != ',') right++;
        int actorID = std::stoi(actorInfo.substr(left, right-left));
        coActors.push_back(actorID);
        // move past ID toward name
        left = ++right;
        // use the < and > to get the name
        while (actorInfo[left++] != '<');
        while (actorInfo[right] != '>') right++;
        std::string actorName = actorInfo.substr(left, right-left);

        Actor& actor = actors[actorID];
        actor.name = actorName;
        actor.movies.push_back(movieID);
    }

    inTable.push_back(coActors);
}

bool ActorAnalyzer::isConnected() {
    return graph.isConnected();
}

std::vector<int> ActorAnalyzer::dijkstra(int from, int to) {
    return graph.dijkstra(from, to);
}