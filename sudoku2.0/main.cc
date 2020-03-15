#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include<map>

#include "sudoku2.h"
char puzzle[128];
int total_solved = 0;
int total = 0;
bool (*solve)(int) = solve_sudoku_basic;

std::map<int,char*>map_client;
pthread_mutex_t mutex;
int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}



void* solution(void*args){
  pthread_mutex_lock(&mutex);
  for(int i=0;i<5;i++){
    input(map_client[i]);
    if (solve(0)) {
        ++total_solved;
        if (!solved())
          assert(0);
        for(int i=0;i<N-1;i++)
      printf("%d",board[i]);
    printf("%d\n\n",board[N-1]);
      }
      else {
        printf("No: %s", puzzle);
      }
  }
   pthread_mutex_unlock(&mutex);
}

void* solution1(void*args){
  pthread_mutex_lock(&mutex);
  for(int i=5;i<total;i++){
    input(map_client[i]);
    if (solve(0)) {
        ++total_solved;
        if (!solved())
          assert(0);
        for(int i=0;i<N-1;i++)
      printf("%d",board[i]);
    printf("%d\n\n",board[N-1]);
      }
      else {
        printf("No: %s", puzzle);
      }
  }
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[])
{
  init_neighbors();

  FILE* fp = fopen(argv[1], "r");
  
 // if (argv[2] != NULL)
   // if (argv[2][0] == 'a')
     // solve = solve_sudoku_min_arity;
   // else if (argv[2][0] == 'c')
      //solve = solve_sudoku_min_arity_cache;
    //else if (argv[2][0] == 'd')
    //  solve = solve_sudoku_dancing_links;
  int64_t start = now();
  while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
    if (strlen(puzzle) >= N) {
      map_client[total]=puzzle;
      ++total;
     // input(puzzle);
     // printf("%s\n",puzzle);
     // printf("--------------------------------------------------\n");
      //init_cache();
      //if (solve_sudoku_min_arity_cache(0)) {
      //if (solve_sudoku_min_arity(0))
      //if (solve_sudoku_basic(0)) {
     /* if (solve(0)) {
        ++total_solved;
        if (!solved())
          assert(0);
        output();
      }
      else {
        printf("No: %s", puzzle);
      }*/
     // deal();
    }
  }
  pthread_mutex_init(&mutex, NULL);

  pthread_t th1;
  if(pthread_create(&th1,NULL,solution,NULL)!=0){
     perror("pthread_create failed");
     exit(0);
  }

  pthread_t th2;
  if(pthread_create(&th2,NULL,solution1,NULL)!=0){
     perror("pthread_create failed");
     exit(0);
  }

  pthread_join(th1,NULL); 	
  pthread_join(th2,NULL);
  
  pthread_mutex_destroy(&mutex);

  int64_t end = now();
  double sec = (end-start)/1000000.0;
  printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);

  return 0;
}



