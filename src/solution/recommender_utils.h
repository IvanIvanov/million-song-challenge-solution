// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef SOLUTION_RECOMMENDER_UTILS_H_
#define SOLUTION_RECOMMENDER_UTILS_H_

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace solution {

void ReadSongIds(const string& song_id_file, map <string, int>& song_ids);

void ReadUserIds(const string& user_file, map <string, int>& user_ids);

void ReadUserSongs(const string& user_song_file,
                   const map <string, int>& song_ids,
                   const map <string, int>& user_ids,
                   vector <vector <int> >&user_songs);

void WriteRecommendations(const string& recommendation_file,
                          vector <vector <int> >& recommended_songs);
 

void SongsUnion(const vector <int>& songs1,
                const vector <int>& songs2,
                vector <int>& result);

void SongsIntersection(const vector <int>& songs1,
                       const vector <int>& songs2,
                       vector <int>& result);
 
double JaccardDistance(const vector <int>& songs1,
                       const vector <int>& songs2);
 
void NearestKUsers(const vector <vector <int> >& user_songs,
                   const vector <int>& user,
                   int k,
                   vector <int>& nearest_users);

void AllSongs(const vector <vector <int> >& user_songs,
              vector <int>& all_songs);
 
void AllSongsForUsers(const vector <vector <int> >&user_songs,
                      const vector <int>& users,
                      vector <int>& result);

void ComputeSongPopularity(const vector <vector <int> >&user_songs,
                           map <int, int>& popularity);
 
void SortSongsByPopularity(const map <int, int>& popularity,
                           vector <int>& songs);

void RecommendSongsForUser(const vector <vector <int> >& user_songs,
                           const vector <int>& user,
                           const map <int, int>& popularity,
                           const vector <int>& songs_sorted_by_popularity,
                           int recommendations,
                           vector <int> &recommended_songs);

void RecommendSongs(const vector <vector <int> >& user_songs,
                    int from_user,
                    int to_user,
                    int recommendations,
                    vector <vector <int> >& recommended_songs);
 
}  // solution

#endif  // SOLUTION_RECOMMENDER_UTILS

