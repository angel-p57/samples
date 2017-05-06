#include "rtest.h"
#include <stdbool.h>
#include <math.h>

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static bool doquit=false;

void *tmain(void *param) {
  struct tparam *tp=param;
  int64_t count=0,i=0;

  for (;;) {
    bool dobreak;
    pthread_mutex_lock(&mutex);
    dobreak=doquit;
    pthread_mutex_unlock(&mutex);
    if ( dobreak ) {
      break;
    }
    tp->dummy+=sqrt(++i);
    count++;
  }
  pthread_mutex_lock(&mutex);
  *tp->count+=count;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void twait(int sec) {
  struct timespec ts={.tv_sec=sec,.tv_nsec=0 };
  nanosleep(&ts,NULL);
  pthread_mutex_lock(&mutex);
  doquit=true;
  pthread_mutex_unlock(&mutex);
}
