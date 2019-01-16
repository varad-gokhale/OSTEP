// This lock makes the thread "sleep" (go from running to runnable) if resource is not available
// gets rid of both problems in test_and_set.c  
// we cannot eliminate spinning completely(as seen by lock/unlocking the guard variable), but since the critical section is really small, it is reasonable to do so

typedef struct{
  int flag;
  int guard;                                //lock to guard flag and q
  queue_t q;
}mutex_t;

void init(mutex_t* m)
{
  m->flag = 0;
  m->guard = 0;  
  queue_init(&q);
}

void lock(mutex_t* m)
{
  while(test_and_set(&m->guard, 1) == 1)    //acquire guard first and enter critical section of modifying q and flag
    ;
  if(m->flag == 0){
    m->flag = 1;
    m->guard = 0;
  }
  else{
    enqueue(m->q, gettid());
    setpark();                              //begin to park
    m->guard = 0;
    park();
  }
}

void unlock(mutex_t* m){
  while(test_and_set(&m->guard, 1) == 1)
    ;
  if(isempty(m->q))
    m->flag = 0;
  else
    unpark(dequeue(m->q));
  m->guard = 0;
}
