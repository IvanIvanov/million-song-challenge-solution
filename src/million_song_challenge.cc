// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include "million_song_challenge.h"

#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <map>
#include <set>
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
                   const map <string, int>& song_ids,
                   const map <string, int>& user_ids,
                   vector <vector <int> >&user_songs) {
  FILE* file = fopen(user_song_file.c_str(), "r");

  int n = user_ids.size();
  user_songs = vector <vector <int> >(n);
  if (file != NULL) {
    char user[128];
    char song[128];
    int freq;
    while (fscanf(file, " %s %s %d", user, song, &freq) == 3) {
      user_songs[user_ids.find(user)->second].push_back(
          song_ids.find(song)->second);
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

void WriteRecommendations(const string& recommendation_file,
                          vector <vector <int> >& recommended_songs) {
  FILE* file = fopen(recommendation_file.c_str(), "w");

  if (file != NULL) {
    int n = (int) recommended_songs.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < (int) recommended_songs[i].size(); j++) {
        fprintf(file, 
                "%d%c",
                recommended_songs[i][j],
                (j + 1 == (int) recommended_songs[i].size()) ? '\n' : ' ');
      }
    }
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
    //printf("id = %d distance = %lf\n", user_distances[i].second, user_distances[i].first);
    nearest_users.push_back(user_distances[i].second);
  }
}

void AllSongs(const vector <vector <int> >& user_songs,
              vector <int>& all_songs) {
  set <int> songs;
  for (int i = 0; i < (int) user_songs.size(); i++) {
    songs.insert(user_songs[i].begin(), user_songs[i].end());
  }

  all_songs = vector <int>(songs.begin(), songs.end());
}

void AllSongsForUsers(const vector <vector <int> >& user_songs,
                      const vector <int>& users,
                      vector <int>& result) {
  set <int> songs;
  int n = users.size();
  for (int i = 0; i < n; i++) {
    songs.insert(user_songs[users[i]].begin(), user_songs[users[i]].end());
  }

  result = vector <int> (songs.begin(), songs.end());
}

void ComputeSongPopularity(const vector <vector <int> >& user_songs,
                           map <int, int>& popularity) {
  popularity.clear();
  int n = user_songs.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int) user_songs[i].size(); j++) {
      popularity[user_songs[i][j]]++;
    }
  }
}

void SortSongsByPopularity(const map <int, int>& popularity,
                           vector <int>& songs) {
  int n = songs.size();
  vector <pair <int, int> > tmp;
  for (int i = 0; i < n; i++) {
    tmp.push_back(make_pair(popularity.find(songs[i])->second, songs[i]));
  }

  sort(tmp.rbegin(), tmp.rend());
  for (int i = 0; i < n; i++) {
    songs[i] = tmp[i].second;
  }
}

void RecommendSongsForUser(const vector <vector <int> >& user_songs,
                           const vector <int>& user,
                           const map <int, int>& popularity,
                           const vector <int>& songs_sorted_by_popularity,
                           int recommendations,
                           vector <int> &recommended_songs) {
  int k = 1 + recommendations / 5;

  vector <int> nearest_users;
  NearestKUsers(user_songs, user, k, nearest_users);

  vector <int> nearest_user_songs;
  AllSongsForUsers(user_songs, nearest_users, nearest_user_songs);
  SortSongsByPopularity(popularity, nearest_user_songs);

  set <int> used(user.begin(), user.end());

  int left = recommendations;
  for (int i = 0; i < (int) nearest_user_songs.size() && left > 0; i++) {
    if (used.find(nearest_user_songs[i]) == used.end()) {
      left--;
      recommended_songs.push_back(nearest_user_songs[i]);
      used.insert(nearest_user_songs[i]);
    }
  }

  for (int i = 0;
       i < (int) songs_sorted_by_popularity.size() && left > 0; i++) {
    if (used.find(songs_sorted_by_popularity[i]) == used.end()) {
      left--;
      recommended_songs.push_back(songs_sorted_by_popularity[i]);
      used.insert(songs_sorted_by_popularity[i]);
    }
  }
}

void RecommendSongs(const vector <vector <int> >& user_songs,
                    int from_user,
                    int to_user,
                    int recommendations,
                    vector <vector <int> >& recommended_songs) {
  map <int, int> popularity;
  ComputeSongPopularity(user_songs, popularity);
  
  vector <int> all_songs;
  AllSongs(user_songs, all_songs);
  SortSongsByPopularity(popularity, all_songs);

  recommended_songs.clear();
  for (int i = from_user; i <= to_user && i < (int) user_songs.size(); i++) {
    vector <int> songs;
    RecommendSongsForUser(
        user_songs,
        user_songs[i],
        popularity,
        all_songs,
        recommendations,
        songs);
    recommended_songs.push_back(songs);
  }
}

}  // million_song_challenge

