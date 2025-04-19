#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include "Song.h"
using namespace std;


vector<unique_ptr<Song>> GetData(ifstream& file){
    vector<unique_ptr<Song>> songs;
    int i = 0;
    string temp;
    getline(file,temp);
    while(file.is_open()){
        std::unique_ptr<Song> song(new Song);
        getline(file,temp,',');
        bool inQuotes = false;
        string line;
        getline(file,line);
        string current;
        vector<string> result;
        for (size_t i = 0; i < line.length(); ++i)
        {
            char c = line[i];

            if (c == '"')
            {
                if (inQuotes && i + 1 < line.size() && line[i + 1] == '"')
                {
                    // Escaped quote
                    current += '"';
                    ++i; // skip next quote
                } else
                {
                    // Toggle inQuotes
                    inQuotes = !inQuotes;
                }
            } else if (c == ',' && !inQuotes)
            {
                // Field finished
                result.push_back(current);
                current.clear();
            } else
            {
                current += c;
            }
        }
        result.push_back(current);
        song->track_id = result[0];
        song->artists = result[1];
        song->album = result[2];
        song->track_name = result[3];
        song->popularity = stoi(result[4]);
        song->track_length = stoi(result[5]);
        temp = result[6];
        transform(temp.begin(),temp.end(),temp.begin(), ::tolower);
        istringstream(temp) >> boolalpha >> song->potty_words;
        song->danceability = stof(result[7]);
        song->energy = stof(result[8]);
        song->key = stof(result[9]);
        song->loudness = stof(result[10]);
        song->mode = stoi(result[11]);
        song->speechiness = stof(result[12]);
        song->acousticness = stof(result[13]);
        song->instrumentalness = stof(result[14]);
        song->liveness = stof(result[15]);
        song->valence = stof(result[16]);
        song->tempo = stof(result[17]);
        song->time_signature = stoi(result[18]);
        song->genre = result[19];
        songs.push_back(move(song));
        if (songs.size() == 113999)
            break;
    }
    return songs;
}



int main()
{
    cout << "hey buds\n\n";
    ifstream file("dataset.csv");
    vector<unique_ptr<Song>> songs;
    songs = GetData(file);
    cout << songs[1]->track_name << endl;

    return 0;
}