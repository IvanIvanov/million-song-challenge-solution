// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef MILLION_SONG_CHALLENGE_POSIX_MULTITHREADED_RECOMMENDER_H_
#define MILLION_SONG_CHALLENGE_POSIX_MULTITHREADED_RECOMMENDER_H_

#include <vector>

//TODO(ivan): don't do this!
using namespace std;

namespace million_song_challenge {

void RecommendSongsMultithreaded(int number_of_threads,
                                 vector <vector <int> >&user_songs,
                                 int from_user,
                                 int to_user,
                                 int songs_to_recommend,
                                 vector <vector <int> >& recommended_songs);

}  // million_songs_challenge

#endif

