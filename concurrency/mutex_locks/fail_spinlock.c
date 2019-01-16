typedef struct{
  int lock;
}mutex_t;


void init(mutex_t* m){
  m->lock = 0;
}

void lock(mutex_t* m){
  while(m->lock == 1)
    ;
    //would fail if thread1 goes beyond while and then interrupt triggers for thread2(both would acquire the lock)
   m->lock = 1;
}

void unlock(mutex_t* m){
  m->lock = 0;
}
