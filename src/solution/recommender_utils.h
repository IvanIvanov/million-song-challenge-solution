// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef SOLUTION_RECOMMENDER_UTILS_H_
#define SOLUTION_RECOMMENDER_UTILS_H_

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std; // TODO(ivan): remove using directive.

namespace solution {

// Reads the song ID file with mappings from song names to song IDs and stores
// those mappings in the song_ids map.
void ReadSongIds(const string& song_id_file, map <string, int>& song_ids);

// Reads the user file in which the i-th user name is the user with ID i
// and stores the name ID mapping in the user_ids map.
void ReadUserIds(const string& user_file, map <string, int>& user_ids);

// Reads the file containing the songs that the users have listened to,
// uses the mappings from songs_ids (from song name to song ID) and
// user_ids (from user name to user ID) and creates a vector - user_songs
// who's i-th element contains a vector of all the song IDs that the user
// with index i has listened to.
void ReadUserSongs(const string& user_song_file,
                   const map <string, int>& song_ids,
                   const map <string, int>& user_ids,
                   vector <vector <int> >& user_songs);

// Writes one line for each element of recommended_songs to the
// recommendation_file. The i-th line is formatted as a space separated
// list of song IDs that are recommended to the user with ID i.
void WriteRecommendations(const string& recommendation_file,
                          vector <vector <int> >& recommended_songs);

// Takes the union of all song IDs in songs1 and songs2 and stores
// it in result. If the same song appears in both songs1 and songs2
// then it will appear only once in result.
void SongsUnion(const vector <int>& songs1,
                const vector <int>& songs2,
                vector <int>& result);

// Takes the intersection of all song IDs in songs1 and songs2 and
// stores it in result.
void SongsIntersection(const vector <int>& songs1,
                       const vector <int>& songs2,
                       vector <int>& result);

// Computes the Jaccard distance between the sets represented by the
// song IDs in songs1 and songs2. The Jaccard distance between the sets
// A and B is defined as J(A, B) = 1.0 - |intersection(A, B)| / |union(A, B)|.
double JaccardDistance(const vector <int>& songs1,
                       const vector <int>& songs2);

// Finds the k nearest users to a user represented as the vector of
// song IDs called user. The vector user_songs has one entry for every
// user among which the nearest ones have to be found. The users that
// are found are stored in the nearest_users vector.
void NearestKUsers(const vector <vector <int> >& user_songs,
                   const vector <int>& user,
                   int k,
                   vector <int>& nearest_users);

// Collects all the different song IDs that all the users in the users_songs
// vector have listened to and stores them in the all_songs vector.
void AllSongs(const vector <vector <int> >& user_songs,
              vector <int>& all_songs);

// Collects all the different song IDs that only the users with indices given
// in the users vector have listened to and stores them in the result vector.
// The songs that a user with id i has listened to are stored in user_songs[i].
void AllSongsForUsers(const vector <vector <int> >&user_songs,
                      const vector <int>& users,
                      vector <int>& result);

// Creates a mapping from song ID to the number of different users that
// have listened to the song. The mapping is stored in the popularity map.
void ComputeSongPopularity(const vector <vector <int> >&user_songs,
                           map <int, int>& popularity);

// Sorts the vector of songs called songs in-place in descending order
// according to the song popularity given by the popularity map.
void SortSongsByPopularity(const map <int, int>& popularity,
                           vector <int>& songs);

// Recommends exactly "recommendations" number of songs for the user defined
// by the user vector. The song IDs of the recommended songs are stored in
// the recommended_songs vector.
//
// The vector user_songs has one entry for each user that contains the IDs of
// the songs that the user has listened to. The popularity map is a mapping
// from song ID to its popularity and the songs_sorted_by_popularity vector
// contains all the songs sorted by popularity.
void RecommendSongsForUser(const vector <vector <int> >& user_songs,
                           const vector <int>& user,
                           const map <int, int>& popularity,
                           const vector <int>& songs_sorted_by_popularity,
                           int recommendations,
                           vector <int> &recommended_songs);

// Recommends exactly "recommendations" number of songs for the users with
// IDs in the inclusive interval [from_user, to_user]. The recommendations
// are stored in the vector recommended_songs in which the first element
// contains the recommendation for the first user ID (from_user), the second
// element contains the recommendation for the second user id (from_user + 1)
// and so on with the last element containing the recommendation for the user
// with ID to_user.
//
// The user_songs vector has one entry for each user that contains the song IDs
// of all the songs that the user has listened to.
void RecommendSongs(const vector <vector <int> >& user_songs,
                    int from_user,
                    int to_user,
                    int recommendations,
                    vector <vector <int> >& recommended_songs);

}  // solution

#endif  // SOLUTION_RECOMMENDER_UTILS

