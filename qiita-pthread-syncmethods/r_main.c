#include "rtest.h"
#include <stdio.h>

double trivial_sqrtops(int sec,int tnum) {
  int64_t count;
  struct tparam params[tnum];
  pthread_t tids[tnum];

  for ( int t=0;t<tnum;t++ ) {
    struct tparam tp={.count=&count};
    params[t]=tp;
    pthread_create(&tids[t],NULL,tmain,&params[t]);
  }
  twait(sec);
  for ( int t=0;t<tnum;t++ ) {
    pthread_join(tids[t],NULL);
  }
  return ((double)count)/sec;
}

int main() {
  int sec=3;
  int tnum=4;
  printf("for thread num: %d\n  in %d seconds, sqrt per sec : %e\n",
         tnum,sec,trivial_sqrtops(sec,tnum));
}
