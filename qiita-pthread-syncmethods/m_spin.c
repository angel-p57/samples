#include "mtest.h"

static pthread_spinlock_t spin;

void initialize() {
  pthread_spin_init(&spin,PTHREAD_PROCESS_PRIVATE);
}

void *tmain(void *param) {
  struct tparam *tp=param;
  for ( int i=tp->min; i<tp->sup; i++ ) {
    pthread_spin_lock(&spin);
    *tp->sum+=i;
    pthread_spin_unlock(&spin);
  }
  return NULL;
}
