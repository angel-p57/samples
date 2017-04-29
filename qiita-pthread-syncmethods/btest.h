#include <pthread.h>
#include <stdint.h>

struct tparam {
  int n,min,sup;
  int64_t *sum1;
  double *sum2;
};

void *tmain(void *param);
void initialize(int tnum);
