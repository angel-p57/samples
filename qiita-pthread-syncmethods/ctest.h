#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>

struct tparam {
  int64_t *sum;
};

void *tcons(void *param);
void tprod(int n,int tnum);

bool pend();
void pinit(int n,int tnum);
int produce();
void cinit(const struct tparam *param);
void consume(int v);

bool bend();
void bclose();
bool bready();
bool bisset();
int bget();
void bset(int v);

bool qempty();
bool qend();
void qclose();
int qdeq();
void qenq(int v);
