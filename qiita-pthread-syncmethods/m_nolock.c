#include "mtest.h"

void initialize() {}

void *tmain(void *param) {
  struct tparam *tp=param;
  for ( int i=tp->min; i<tp->sup; i++ ) {
    *tp->sum+=i;
  }
  return NULL;
}
