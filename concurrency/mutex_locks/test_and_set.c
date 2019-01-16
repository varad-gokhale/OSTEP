//This lock guarantees atomicity but there are two problems:
// 1. a thread can acquire and reacquire the lock indefinitely thus starving other threads(no guarantee of all threads being serviced)
// 2. Performance issue: when the lock is spinning, the whole time slice is spend doing no work(and just spinning)
// Problem 2 can be solved by using yield() system call in case lock is unavailable, but still doesn't solve problem 1

typedef struct{
  int lock;
}mutex_t;


void init(mutex_t* m){
  m->lock = 0;
}

void test_and_set(int* lock, int val)
{
  int ret;
  //atomic assembly instruction which stores current lock value in "ret" and sets lock to "val"(acquires it)
  return ret;
}

void lock(mutex_t* m){
  while(test_and_set(&(m->lock),1) == 1)
    ;
}

void unlock(mutex_t* m){
  m->lock = 0;
}
