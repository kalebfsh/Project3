#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
using namespace std;
struct Song { // we could use a class to store songs and all their data when the csv file is read and have some storage for all of these
    //these are really just placeholders these are all the diff data points they got, prob won't need all of them
    int serial, popularity, track_length, key, time_signature;
    string track_id, artists, album, track_name, genre;
    bool potty_words, mode;
    float danceability, energy, loudness, speechiness, acousticness, liveness, valence, tempo;
    double instrumentalness;


};
