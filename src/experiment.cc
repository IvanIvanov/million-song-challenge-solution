// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main(void) {
  char user[64];
  char song[64];
  int times;

  int n = 0;
  map <string, int> freq;
  while (scanf(" %s %s %d", user, song, &times) == 3) {
    freq[song]++;
    n++;
  }

  vector <pair <int, string> > songs;
  for (map <string, int>::iterator it = freq.begin(); it != freq.end(); it++) {
    songs.push_back(make_pair(it->second, it->first));
  }

  sort(songs.rbegin(), songs.rend());
  
  int sum = 0;
  for (int i = 0; i < songs.size(); i++) {
    sum += songs[i].first;
    printf("%s: %d\n", songs[i].second.c_str(), songs[i].first);
    if ((double) sum / n > 0.80) {
      printf("i = %d\n", i + 1);
      break;
    }
  }

  return 0;
}

