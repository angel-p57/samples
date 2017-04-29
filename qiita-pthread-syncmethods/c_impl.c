#include "ctest.h"
#include <stdlib.h>
#include <time.h>

static pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t cmutex = PTHREAD_MUTEX_INITIALIZER;

static void randsleep(int interval) {
  int64_t r;
  pthread_mutex_lock(&rmutex);
  r=random();
  pthread_mutex_unlock(&rmutex);
  int usec=r*interval/RAND_MAX;
  struct timespec ts={ .tv_sec=usec/1000000,.tv_nsec=usec%1000000*1000 };
  nanosleep(&ts,NULL);
}

static int pcur,plast,pinterval;
void pinit(int n,int tnum) {
  pcur=1;
  plast=n;
  pinterval=300/tnum;
}
bool pend() {
  return pcur>plast;
}
int produce() {
  randsleep(pinterval);
  return pcur++;
}
static __thread int64_t *sp;
const static int cinterval=500;
void cinit(const struct tparam *param) {
  sp=param->sum;
}
void consume(int v) {
  pthread_mutex_lock(&cmutex);
  *sp+=v;
  pthread_mutex_unlock(&cmutex);
  randsleep(cinterval);
}

static int bstate=0; // 0: ready, 1: isset, 2: end
static int buf;
bool bready() {
  return bstate==0;
}
bool bisset() {
  return bstate==1;
}
bool bend() {
  return bstate==2;
}
int bget() {
  int tmp=buf;
  buf=0;
  bstate=0;
  return tmp;
}
void bset(int v) {
  buf=v;
  bstate=1;
}
void bclose() {
  bstate=2;
}

static bool qclosed=false;
static int qhead=1,qtail=0;
bool qempty() {
  return qhead>qtail;
}
bool qend() {
  return qclosed&&qempty();
}
void qclose() {
  qclosed=true;
}
int qdeq() {
  return qhead++;
}
void qenq(int v) {
  qtail=v;
}
