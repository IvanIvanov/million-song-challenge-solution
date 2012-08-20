// Author: Ivan Ivanov (ivan.vladimirov.ivanov@gmail.com)

#include <pthread.h>

#include <vector>

#include "recommender_utils.h"

using namespace std;

namespace solution {

struct TaskArguments {
  vector <vector <int> >* user_songs;
  int from_user;
  int to_user;
  int songs_to_recommend;
  vector <vector <int> > recommended_songs;

  TaskArguments() {}

  TaskArguments(vector <vector <int> >* user_songs,
                int from_user,
                int to_user,
                int songs_to_recommend)
      : user_songs(user_songs), from_user(from_user),
        to_user(to_user), songs_to_recommend(songs_to_recommend) {
  }
};

static void* TaskRecommendSongs(void* arguments) {
  TaskArguments* task_arguments = (TaskArguments*) arguments;
  vector <vector <int> >& user_songs = *task_arguments->user_songs;
  RecommendSongs(
      user_songs,
      task_arguments->from_user,
      task_arguments->to_user,
      task_arguments->songs_to_recommend,
      task_arguments->recommended_songs);

  return NULL;
}

void RecommendSongsMultithreaded(int number_of_threads,
                                 vector <vector <int> >& user_songs,
                                 int from_user,
                                 int to_user,
                                 int songs_to_recommend,
                                 vector <vector <int> >& recommended_songs) {
  
  int tasks_per_thread = (to_user - from_user) / number_of_threads;
  vector <pthread_t> threads(number_of_threads);
  vector <TaskArguments> task_arguments(number_of_threads);
  for (int i = 0; i < number_of_threads; i++) {
    task_arguments[i] = TaskArguments(
        &user_songs,
        from_user + i * tasks_per_thread,
        (i + 1 == number_of_threads) ? to_user :
            from_user + (i + 1) * tasks_per_thread - 1,
        songs_to_recommend);
    pthread_create(
        &threads[i], NULL, TaskRecommendSongs, (void*) &task_arguments[i]);
  }

  for (int i = 0; i < number_of_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  recommended_songs.clear();
  for (int i = 0; i < number_of_threads; i++) {
    for (int j = 0;
         j < (int) task_arguments[i].recommended_songs.size(); j++) {
      recommended_songs.push_back(task_arguments[i].recommended_songs[j]);
    }
  }
}

}  // solution

