int load_linked(int* lock){
  return *lock;
}

//whole function is an atomic instruction
int store_conditional(int* lock, int val){
  if(nobody has modified the lock value since load_linked to this address)
  {
    *lock = val;
    return 1; //success
  }
  else
    return 0;
}

typedef struct{
  int lock;
}mutex_t;


void init(mutex_t* m){
  m->lock = 0;
}

void lock(mutex_t* m){
  while(1){
    while(load_linked(&(m->lock))
      ;
    if(store_conditional(&(m->lock), 1) == 1)
      return;
  }
}

void unlock(mutex_t* m){
  m->lock = 0;
}
