typedef struct{
  int lock;
}mutex_t;


void init(mutex_t* m){
  m->lock = 0;
}

//whole function is basically an atomic assembly instruction in some architectures
void compare_and_exchange(int* lock, int expected, int new)
{
  int ret = *lock;
  if(*lock == expected)
    *lock = new;
  return ret;
}

void lock(mutex_t* m){
  while(compare_and_exchange(&(m->lock),0,1) == 1)
    ;
}

void unlock(mutex_t* m){
  m->lock = 0;
}
