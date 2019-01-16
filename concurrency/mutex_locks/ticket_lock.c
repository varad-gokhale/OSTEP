// advantage of this lock over other locks is that it guarantees that threads will be serviced on a first come first basis
// no thread is starved
// thus, problem one in test_and_set.c is solved, but problem two still remains

typedef struct{
  int ticket;
  int turn;
}mutex_t;

void init(mutex_t* m){
  m->ticket = 0;
  m->turn = 0;
}

int fetch_and_add(int* turn)
{
  int ret = *turn;
  *turn = ret + 1;
  return ret;
}

void lock(mutex_t* m){
  int myturn = fetch_and_add(&m->ticket);
  while(myturn != m->turn)
    ; //spin
}

void unlock(mutex_t* m){
  m->turn += 1;
}
