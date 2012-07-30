// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#ifndef MILLION_SONG_CHALLENGE_MILLION_SONG_CHALLENGE_H_
#define MILLION_SONG_CHALLENGE_MILLION_SONG_CHALLENGE_H_

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace million_song_challenge {

void ReadSongIds(const string& song_id_file, map <string, int>& song_ids);

void ReadUserIds(const string& user_file, map <string, int>& user_ids);

void ReadUserSongs(const string& user_song_file,
                   map <string, int>& song_ids,
                   map <string, int>& user_ids,
                   vector <vector <int> >&user_songs);
 
}  // million_song_challenge

#endif  // MILLION_SONG_CHALLENGE_MILLION_SONG_CHALLENGE_H_

