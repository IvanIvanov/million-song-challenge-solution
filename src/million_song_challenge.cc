// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include "million_song_challenge.h"

#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <map>
#include <vector>

using namespace std;

namespace million_song_challenge {

void ReadSongIds(const string& song_id_file, map <string, int>& song_ids) {
  FILE* file = fopen(song_id_file.c_str(), "r");

  song_ids.clear();
  if (file != NULL) {
    int id;
    char song[128];
    while (fscanf(file, " %s %d", song, &id) == 2) {
      song_ids[song] = id;
    }
  }

  fclose(file);
}

void ReadUserIds(const string& user_file, map <string, int>& user_ids) {
  FILE* file = fopen(user_file.c_str(), "r");

  user_ids.clear();
  if (file != NULL) {
    int id = 0;
    char user[128];
    while (fscanf(file, " %s", user) == 1) {
      user_ids[user] = id++;
    }
  }

  fclose(file);
}

void ReadUserSongs(const string& user_song_file,
                   map <string, int>& song_ids,
                   map <string, int>& user_ids,
                   vector <vector <int> >&user_songs) {
  FILE* file = fopen(user_song_file.c_str(), "r");

  int n = user_ids.size();
  user_songs = vector <vector <int> >(n);
  if (file != NULL) {
    char user[128];
    char song[128];
    int freq;
    while (fscanf(file, " %s %s %d", user, song, &freq) == 3) {
      user_songs[user_ids[user]].push_back(song_ids[song]);
    }
  }

  for (int i = 0; i < n; i++) {
    sort(user_songs[i].begin(), user_songs[i].end());
  }

  fclose(file);
}

}  // million_song_challenge

