#include <pthread.h>
#include <stdint.h>

struct tparam {
  int min,sup;
  int64_t *sum;
};

void initialize();
void *tmain(void *param);
