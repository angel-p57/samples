#include "ctest.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t conds = PTHREAD_COND_INITIALIZER;
static pthread_cond_t condr = PTHREAD_COND_INITIALIZER;

void *tcons(void *param) {
  struct thread_param *tparam = param;
  cinit(param);
  for (;;) {
    bool dobreak;
    int v;
    pthread_mutex_lock(&mutex);
    while ( !bisset()&&!bend() ) {
      pthread_cond_wait(&conds,&mutex);
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
    pthread_cond_signal(&condr);
  }
  return NULL;
}

void tprod(int n,int tnum) {
  pinit(n,tnum);
  while ( !pend() ) {
    int v=produce();
    pthread_mutex_lock(&mutex);
    while ( !bready() ) {
      pthread_cond_wait(&condr,&mutex);
    }
    bset(v);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&conds);
  }
  pthread_mutex_lock(&mutex);
  while ( !bready() ) {
    pthread_cond_wait(&condr,&mutex);
  }
  bclose();
  pthread_mutex_unlock(&mutex);
  pthread_cond_broadcast(&conds);
}
