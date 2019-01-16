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
