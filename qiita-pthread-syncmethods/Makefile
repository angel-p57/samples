CC=gcc
CFLAGS=-std=gnu99 -O2
LIBS=-lpthread

.PHONY: all clean mtest btest rtest ctest
default: all
all: mtest btest rtest ctest

# mutex tests
M_EXES=m_lock m_nolock m_spin
mtest: $(M_EXES)
$(M_EXES): m_main.o
$(wildcard m_*.o): mtest.h
m_lock: m_lock.o
m_nolock: m_nolock.o
m_spin: m_spin.o

# barrier tests
B_EXES=b_bar b_nobar
btest: $(B_EXES)
$(B_EXES): b_main.o
$(wildcard b_*.o): btest.h
b_bar: b_bar.o
b_nobar: b_nobar.o

# rwlock tests
R_EXES=r_lock r_nolock r_mutex
rtest: $(R_EXES)
$(R_EXES): r_main.o
$(R_EXES): override LIBS+=-lm
r_lock: r_lock.o
r_nolock: r_nolock.o
r_mutex: r_mutex.o

# cond tests
C_EXES=c_busy c_condq c_condqx c_condb c_condbx
ctest: $(C_EXES)
$(C_EXES): c_main.o c_impl.o
$(wildcard c_*.o): ctest.h
c_busy: c_busy.o
c_condb: c_condb.o
c_condbx: c_condbx.o
c_condq: c_condq.o
c_condqx: c_condqx.o

EXES=$(M_EXES) $(B_EXES) $(R_EXES) $(C_EXES)
$(EXES):
	$(CC) -o $@ $^ $(LIBS)
clean:
	rm -f *.o *.s $(EXES)
