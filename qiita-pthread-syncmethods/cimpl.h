#include "ctest.h"
#include <stdbool.h>

void tcinit(struct tparam *param);
void tpinit(int n);
void consume(int cval);
bool produce(int *pval);
bool qempty();
bool qend();
void qenq(int x);
int qdeq();
void qclose();
