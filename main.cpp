#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <set>
#include "Graph.h"
#include "FL/Fl.h"
#include "FL/Fl_Window.H"

using namespace std;

int main() {
    Fl_Window win(300,300,"FL");
    win.show();
    string genre;
    cout << "Enter a genre: ";
    getline(cin, genre);

    ifstream file("dataset.csv");
    if (!file) {
        cerr << "Could not open dataset.csv\n";
        return 1;
    }

    Graph graph;
    graph.LoadGenreFromCSV(file, genre); // Only loads songs from that genre

    const auto& songs = graph.GetSongsByGenre(genre);
    const auto& matrix = graph.GetAdjacencyMatrix(genre);

    if (songs.size() < 10) {
        cout << "Not enough songs in this genre to find 10 closest.\n";
        return 1;
    }

    // Pick a random song
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, songs.size() - 1);
    int startIndex = dist(gen);

    cout << "\nStarting song: " << songs[startIndex].track_name << " by " << songs[startIndex].artists << "\n\n";

    // Set to track unique recommendations by name+artist
    set<string> seen;
    seen.insert(songs[startIndex].track_name + songs[startIndex].artists);

    vector<pair<float, int>> distances;
    for (size_t i = 0; i < matrix[startIndex].size(); ++i) {
        if (i != static_cast<size_t>(startIndex)) {
            distances.emplace_back(matrix[startIndex][i], i);
        }
    }

    sort(distances.begin(), distances.end());

    cout << "9 closest songs:\n";
    int count = 0;
    for (const auto& [dist, index] : distances) {
        string key = songs[index].track_name + songs[index].artists;
        if (seen.count(key)) continue;

        seen.insert(key);
        cout << " - " << songs[index].track_name << " by " << songs[index].artists << "\n";
        if (++count == 9) break;
    }

    return 0;
}