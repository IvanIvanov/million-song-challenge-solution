solution:
	g++ -Wall -lpthread -I"src/" src/million_song_challenge.cc src/posix_multithreaded_recommender.cc src/main.cc -O2 -o bin/main

experiment:
	g++ src/experiment.cc -o bin/main

