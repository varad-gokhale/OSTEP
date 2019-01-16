typedef struct{
  int flag;
  int guard;
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
  while(test_and_set(&m->guard, 1) == 1)
    ;
  if(m->flag == 0){
    m->flag = 1;
    m->guard = 0;
  }
  else{
    enqueue(m->q, gettid());
    setpark();
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
