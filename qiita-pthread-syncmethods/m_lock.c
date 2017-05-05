#include "mtest.h"

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void initialize() {}

void *tmain(void *param) {
  struct tparam *tp=param;
  for ( int i=tp->min; i<tp->sup; i++ ) {
    pthread_mutex_lock(&mutex);
    *tp->sum+=i;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
