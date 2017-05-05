#include "btest.h"
#include <stdio.h>

double trivial_var(int n,int tnum) {
  int64_t tmp=0;
  double sqsum=0.0;
  struct tparam params[tnum];
  pthread_t tids[tnum];

  initialize(tnum);
  for ( int t=0; t<tnum; t++ ) {
    struct tparam tp={.n=n,.min=n*t/tnum+1,.sup=n*(t+1)/tnum+1,.sum1=&tmp,.sum2=&sqsum};
    params[t]=tp;
    pthread_create(&tids[t],NULL,tmain,&params[t]);
  }
  for ( int t=0; t<tnum; t++ ) {
    pthread_join(tids[t],NULL);
  }
  return sqsum/n;
}

int main() {
  int n=10000000;
  int tnum=4;
  printf("for thread num: %d\n  variance of 1 to %d: %e ( expected: %e )\n",
         tnum,n,trivial_var(n,tnum),(((double)n)*n-1)/12);
}
