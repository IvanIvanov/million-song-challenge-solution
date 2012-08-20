// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef SOLUTION_POSIX_MULTITHREADED_RECOMMENDER_H_
#define SOLUTION_POSIX_MULTITHREADED_RECOMMENDER_H_

#include <vector>

namespace solution {

// Recommends exactly "songs_to_recommend" number of songs for the users with
// IDs in the inclusive interval [from_user, to_user]. The recommendations
// are stored in the vector recommended_songs in which the first element
// contains the recommendation for the first user ID (from_user), the second
// element contains the recommendation for the second user id (from_user + 1)
// and so on with the last element containing the recommendation for the user
// with ID to_user.
//
// The user_songs vector has one entry for each user that contains the song IDs
// of all the songs that the user has listened to.
//
// The computation is split up into multiple, approximately equal, parts where
// each part is assigned to a different thread. The number of threads is given
// by the number_of_threads parameter.
void RecommendSongsMultithreaded(int number_of_threads,
                                 std::vector <std::vector <int> >&user_songs,
                                 int from_user,
                                 int to_user,
                                 int songs_to_recommend,
                                 std::vector <std::vector <int> >& recommended_songs);

}  // solution

#endif

