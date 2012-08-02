// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <vector>

#include "million_song_challenge.h"
#include "posix_multithreaded_recommender.h"

using namespace std;
using namespace million_song_challenge;

const static char* kDefaultSongsFile = "data/kaggle_songs.txt";

const static char* kDefaultUsersFile = "data/kaggle_users.txt";

const static char* kDefaultUserSongsFile =
    "data/kaggle_visible_evaluation_triplets.txt";

const static char* kDefaultRecommendationFile =
    "recommendations.txt";

const static int kDefaultSongsToRecommend = 500;

const static int kDefaultThreads = 4;

int main(int argc, char** argv) {
  string songs_file = kDefaultSongsFile;
  string users_file = kDefaultUsersFile;
  string user_songs_file = kDefaultUserSongsFile;
  string recommendation_file = kDefaultRecommendationFile;
  int songs_to_recommend = kDefaultSongsToRecommend;
  int from_user = -1;
  int to_user = -1;
  int number_of_threads = kDefaultThreads;

  for (int i = 1; i + 1 < argc; i += 2) {
    if (!strcmp("--songs_file", argv[i])) {
      songs_file = argv[i + 1];
    } else if (!strcmp("--users_file", argv[i])) {
      users_file = argv[i + 1];
    } else if (!strcmp("--user_songs_file", argv[i])) {
      users_file = argv[i + 1];
    } else if (!strcmp("--recommendation_file", argv[i])) {
      recommendation_file = argv[i + 1];
    } else if (!strcmp("--songs_to_recommend", argv[i])) {
      songs_to_recommend = atoi(argv[i + 1]);
    } else if (!strcmp("--from_user", argv[i])) {
      from_user = atoi(argv[i + 1]);
    } else if (!strcmp("--to_user", argv[i])) {
      to_user = atoi(argv[i + 1]);
    } else if (!strcmp("--number_of_threads", argv[i])) {
      number_of_threads = atoi(argv[i + 1]);
    }
  }

  map <string, int> song_ids;
  map <string, int> user_ids;
  vector <vector <int> > user_songs;
  ReadSongIds(songs_file, song_ids);
  ReadUserIds(users_file, user_ids);
  ReadUserSongs(user_songs_file,
                song_ids,
                user_ids,
                user_songs);

  if (from_user == -1 || to_user == -1) {
    from_user = 0;
    to_user = (int) user_songs.size() - 1;
  }

  vector <vector <int> > recommended_songs;
  RecommendSongsMultithreaded(
      number_of_threads,
      user_songs,
      from_user,
      to_user,
      songs_to_recommend,
      recommended_songs);

  WriteRecommendations(recommendation_file, recommended_songs); 
  
  return 0;
}

