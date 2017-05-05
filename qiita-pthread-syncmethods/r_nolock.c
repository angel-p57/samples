#include "rtest.h"
#include <math.h>

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static int doquit=0;

void *tmain(void *param) {
  struct tparam *tp=param;
  int64_t count=0,i=0;

  while ( !doquit ) {
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
  doquit=1;
}
