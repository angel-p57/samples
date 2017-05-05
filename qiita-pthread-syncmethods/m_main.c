#include "mtest.h"
#include <stdio.h>
#include <inttypes.h>

int64_t trivial_sum(int n,int tnum) {
  int64_t ret=0;
  struct tparam params[tnum];
  pthread_t tids[tnum];

  initialize();
  for ( int t=0; t<tnum; t++ ) {
    struct tparam tp={.min=n*t/tnum+1,.sup=n*(t+1)/tnum+1,.sum=&ret};
    params[t]=tp;
    pthread_create(&tids[t],NULL,tmain,&params[t]);
  }
  for ( int t=0; t<tnum; t++ ) {
    pthread_join(tids[t],NULL);
  }
  return ret;
}

int main() {
  int n=10000000;
  int tnum=4;
  printf("for thread num: %d\n  sum of 1 to %d: %"PRId64" ( expected: %"PRId64" )\n",
         tnum,n,trivial_sum(n,tnum),((int64_t)n)*(n+1)/2);
}
