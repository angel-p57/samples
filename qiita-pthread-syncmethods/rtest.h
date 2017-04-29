#include <pthread.h>
#include <stdint.h>

struct tparam {
  int64_t *count;
  double dummy;
};

void *tmain(void *param);
void twait(int sec);
