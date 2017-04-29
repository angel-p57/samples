#include "ctest.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *tcons(void *param) {
  cinit(param);
  for (;;) {
    bool dobreak;
    int v;
    pthread_mutex_lock(&mutex);
    while ( qempty()&&!qend() ) {
      pthread_mutex_unlock(&mutex);
      pthread_mutex_lock(&mutex);
    }
    dobreak=qend();
    if ( !dobreak ) {
      v=qdeq();
    }
    pthread_mutex_unlock(&mutex);
    if ( dobreak ) {
      break;
    }
    consume(v);
  }
  return NULL;
}

void tprod(int n,int tnum) {
  pinit(n,tnum);
  while ( !pend() ) {
    int v=produce();
    pthread_mutex_lock(&mutex);
    qenq(v);
    pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_lock(&mutex);
  qclose();
  pthread_mutex_unlock(&mutex);
}
