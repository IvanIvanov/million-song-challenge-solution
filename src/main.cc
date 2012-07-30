// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include "million_song_challenge.h"

#include <cstdio>

#include <vector>
#include <map>

using namespace std;
using namespace million_song_challenge;

int main(void) {
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
  return 0;
}

