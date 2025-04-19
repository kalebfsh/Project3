#include <iostream>
#include <fstream>
#include "Graph.h"
#include <algorithm>

int main() {
    ifstream file("dataset.csv");
    if (!file) {
        cerr << "Could not open dataset.csv\n";
        return 1;
    }

    Graph graph;
    graph.LoadFromCSV(file);

    string genre = "rock";
    if (auto genres = graph.GetAllGenres(); find(genres.begin(), genres.end(), genre) != genres.end()) {
        const auto& matrix = graph.GetAdjacencyMatrix(genre);
        const auto& songs = graph.GetSongsByGenre(genre);

        cout << "Number of songs in '" << genre << "': " << songs.size() << "\n";
        if (songs.size() >= 2) {
            cout << "Distance between song 0 and 1: " << matrix[0][1] << "\n";
        }
    } else {
        cout << "Genre not found: " << genre << "\n";
    }

    return 0;
}