// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include "million_song_challenge.h"

#include <cstdio>

#include <vector>
#include <map>

using namespace std;
using namespace million_song_challenge;

void testComputationSpeed(int n) {
  map <string, int> song_ids;
  map <string, int> user_ids;
  vector <vector <int> > user_songs;
  ReadSongIds("data/kaggle_songs.txt", song_ids);
  ReadUserIds("data/kaggle_users.txt", user_ids);
  ReadUserSongs("data/kaggle_visible_evaluation_triplets.txt",
                song_ids,
                user_ids, user_songs);

  int m = user_songs.size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      double d = JaccardDistance(user_songs[i], user_songs[j]);
      d++;
    }
  }
}

int main(void) {
  //testComputationSpeed(1000);
  
  
  map <string, int> song_ids;
  map <string, int> user_ids;
  vector <vector <int> > user_songs;
  ReadSongIds("data/kaggle_songs.txt", song_ids);
  ReadUserIds("data/kaggle_users.txt", user_ids);
  ReadUserSongs("data/kaggle_visible_evaluation_triplets.txt",
                song_ids,
                user_ids, user_songs);
  printf("%d\n", (int)song_ids.size());
  printf("%d\n", (int)user_ids.size());
  printf("%d\n", (int)user_songs.size());

  vector <int> nearest_users;
  NearestKUsers(user_songs, user_songs[1050], 100, nearest_users);
  for (int i = 0; i < (int)nearest_users.size(); i++) {
    printf("%d%c",
        nearest_users[i], (i + 1 == (int)nearest_users.size()) ? '\n' : ' ');
  }

/*
  vector <int> v1;
  vector <int> v2;
  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);

  v2.push_back(0);
  v2.push_back(3);
  v2.push_back(4);

  vector <int> v3;
  SongsUnion(v1, v2, v3);
  for (int i = 0; i < (int)v3.size(); i++) {
    printf("%d%c", v3[i], (i + 1 == (int) v3.size()) ? '\n' : ' ');
  }

  SongsIntersection(v1, v2, v3);
  for (int i = 0; i < (int)v3.size(); i++) {
    printf("%d%c", v3[i], (i + 1 == (int) v3.size()) ? '\n' : ' ');
  }

  printf("Distance: %lf\n", JaccardDistance(v1, v2));
  */

  return 0;
}

