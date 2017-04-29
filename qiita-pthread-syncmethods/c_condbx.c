#include "ctest.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *tcons(void *param) {
  struct thread_param *tparam = param;
  cinit(param);
  for (;;) {
    bool dobreak;
    int v;
    pthread_mutex_lock(&mutex);
    while ( !bisset()&&!bend() ) {
      pthread_cond_wait(&cond,&mutex);
    }
    dobreak=bend();
    if ( !dobreak ) {
      v=bget();
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
    bset(v);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  pthread_mutex_lock(&mutex);
  bclose();
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}
