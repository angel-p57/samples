#include "ctest.h"
#include <stdio.h>
#include <inttypes.h>

int64_t trivial_sum(int n,int tnum) {
  struct tparam tparams[tnum];
  pthread_t tids[tnum];

  int64_t sum=0;
  for ( int t=0; t<tnum; t++ ) {
    struct tparam param={ .sum=&sum };
    tparams[t]=param;
    pthread_create(&tids[t],NULL,tcons,&tparams[t]);
  }
  tprod(n,tnum);
  for ( int t=0; t<tnum; t++ ) {
    pthread_join(tids[t],NULL);
  }
  return sum;
}

int main() {
  const int n=5000, tnum=4;
  printf("for thread num = %d\n  sum of 1 to %d: %"PRId64" ( expected: %"PRId64" )\n",
         tnum,n,trivial_sum(n,tnum),((int64_t)n)*(n+1)/2);
}
