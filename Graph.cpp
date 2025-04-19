//
// Created by sam51 on 4/19/2025.
//

#include "Graph.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

vector<float> Graph::GetFeatureVector(const Song& song) const {
    return {
        song.danceability,
        song.energy,
        song.speechiness,
        song.acousticness,
        static_cast<float>(song.instrumentalness),
        song.liveness,
        song.valence,
        song.tempo
    };
}

float Graph::EuclideanDistance(const vector<float>& a, const vector<float>& b) const {
    float sum = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

void Graph::LoadFromCSV(ifstream& file) {
    string temp;
    getline(file, temp); // Skip header

    while (file.is_open() && file.peek() != EOF) {
        Song song;
        getline(file, temp, ','); // skip first field

        bool inQuotes = false;
        string line;
        getline(file, line); // rest of row

        string current;
        vector<string> result;
        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == '"') {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                    current += '"';
                    ++i;
                } else {
                    inQuotes = !inQuotes;
                }
            } else if (c == ',' && !inQuotes) {
                result.push_back(current);
                current.clear();
            } else {
                current += c;
            }
        }
        result.push_back(current);

        if (result.size() < 20) continue;

        song.track_id = result[0];
        song.artists = result[1];
        song.album = result[2];
        song.track_name = result[3];
        song.popularity = stoi(result[4]);
        song.track_length = stoi(result[5]);

        temp = result[6];
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        istringstream(temp) >> boolalpha >> song.potty_words;

        song.danceability = stof(result[7]);
        song.energy = stof(result[8]);
        song.key = stoi(result[9]);
        song.loudness = stof(result[10]);
        song.mode = stoi(result[11]);
        song.speechiness = stof(result[12]);
        song.acousticness = stof(result[13]);
        song.instrumentalness = stod(result[14]);
        song.liveness = stof(result[15]);
        song.valence = stof(result[16]);
        song.tempo = stof(result[17]);
        song.time_signature = stoi(result[18]);
        song.genre = result[19];

        string genre = song.genre;
        auto& songList = genreMap[genre];
        size_t n = songList.size();

        vector<float> newRow(n + 1, 0.0f);
        for (size_t i = 0; i < n; ++i) {
            float dist = EuclideanDistance(GetFeatureVector(song), GetFeatureVector(songList[i]));
            adjacencyMatrices[genre][i].push_back(dist);
            newRow[i] = dist;
        }

        adjacencyMatrices[genre].push_back(newRow);
        songList.push_back(song);
    }
}

const vector<vector<float>>& Graph::GetAdjacencyMatrix(const string& genre) const {
    return adjacencyMatrices.at(genre);
}

const vector<Song>& Graph::GetSongsByGenre(const string& genre) const {
    return genreMap.at(genre);
}

vector<string> Graph::GetAllGenres() const {
    vector<string> genres;
    for (const auto& [key, _] : genreMap) {
        genres.push_back(key);
    }
    return genres;
}