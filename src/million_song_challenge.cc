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
    user_songs[i].erase(
        unique(user_songs[i].begin(), user_songs[i].end()),
        user_songs[i].end());
  }

  fclose(file);
}

void SongsUnion(const vector <int>& songs1,
                const vector <int>& songs2,
                vector <int>& result) {
  int n = songs1.size();
  int m = songs2.size();

  int i = 0;
  int j = 0;
  result.clear();
  while (i < n && j < m) {
    if (songs1[i] < songs2[j]) {
      result.push_back(songs1[i++]);
    } else if (songs1[i] > songs2[j]) {
      result.push_back(songs2[j++]);
    } else {
      j++;
      result.push_back(songs1[i++]);
    }
  }
  while (i < n) result.push_back(songs1[i++]);
  while (j < m) result.push_back(songs2[j++]);
}

void SongsIntersection(const vector <int>& songs1,
                       const vector <int>& songs2,
                       vector <int>& result) {
  int n = songs1.size();
  int m = songs2.size();

  int i = 0;
  int j = 0;
  result.clear();
  while (i < n && j < m) {
    if (songs1[i] < songs2[j]) {
      i++;
    } else if (songs1[i] > songs2[j]) {
      j++;
    } else {
      j++;
      result.push_back(songs1[i++]);
    }
  }
}

double JaccardDistance(const vector <int>& songs1,
                       const vector <int>& songs2) {
  vector <int> songs_union;
  vector <int> songs_intersection;
  SongsUnion(songs1, songs2, songs_union);
  SongsIntersection(songs1, songs2, songs_intersection);

  if (songs_union.empty()) return 0.0;

  return 1.0 - ((double) songs_intersection.size() / songs_union.size());
}

void NearestKUsers(const vector <vector <int> >& user_songs,
                   const vector <int>& user,
                   int k,
                   vector <int>& nearest_users) {
  int n = user_songs.size();
  vector <pair <double, int> > user_distances;
  for (int i = 0; i < n; i++) {
    double d = JaccardDistance(user, user_songs[i]);
    user_distances.push_back(make_pair(d, i));
  }

  sort(user_distances.begin(), user_distances.end());
  
  nearest_users.clear();
  for (int i = 0; i < k && i < n; i++) {
    printf("id = %d distance = %lf\n", user_distances[i].second, user_distances[i].first);
    nearest_users.push_back(user_distances[i].second);
  }
}

}  // million_song_challenge

