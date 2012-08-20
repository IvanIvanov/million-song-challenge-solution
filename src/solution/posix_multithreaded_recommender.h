// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef SOLUTION_POSIX_MULTITHREADED_RECOMMENDER_H_
#define SOLUTION_POSIX_MULTITHREADED_RECOMMENDER_H_

#include <vector>

//TODO(ivan): don't do this!
using namespace std;

namespace solution {

void RecommendSongsMultithreaded(int number_of_threads,
                                 vector <vector <int> >&user_songs,
                                 int from_user,
                                 int to_user,
                                 int songs_to_recommend,
                                 vector <vector <int> >& recommended_songs);

}  // solution

#endif

