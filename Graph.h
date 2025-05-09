//
// Created by sam51 on 4/19/2025.
//

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Song {
    int serial, popularity, track_length, key, time_signature;
    string track_id, artists, album, track_name, genre;
    bool potty_words, mode;
    float danceability, energy, loudness, speechiness, acousticness, liveness, valence, tempo;
    double instrumentalness;
};

class Graph {
private:
    unordered_map<string, vector<Song>> genreMap;
    unordered_map<string, vector<vector<float>>> adjacencyMatrices;

    vector<float> GetFeatureVector(const Song& song) const;
    float EuclideanDistance(const vector<float>& a, const vector<float>& b) const;

public:
    void LoadFromCSV(ifstream& file);
    void LoadGenreFromCSV(std::ifstream& file, const std::string& target_genre);
    const vector<vector<float>>& GetAdjacencyMatrix(const string& genre) const;
    const vector<Song>& GetSongsByGenre(const string& genre) const;
    vector<string> GetAllGenres() const;
};