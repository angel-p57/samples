#include "btest.h"

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void initialize(int tnum) {}

void *tmain(void *param) {
  struct tparam *tp=param;
  int64_t psum1=0;
  for ( int i=tp->min; i<tp->sup; i++ ) {
    psum1+=i;
  }
  pthread_mutex_lock(&mutex);
  *tp->sum1+=psum1;
  pthread_mutex_unlock(&mutex);

  double ave=((double)*tp->sum1)/tp->n;
  double psum2=0.0;
  for ( int i=tp->min; i<tp->sup; i++ ) {
    psum2+=(i-ave)*(i-ave);
  }
  pthread_mutex_lock(&mutex);
  *tp->sum2+=psum2;
  pthread_mutex_unlock(&mutex);

  return NULL;
}
