//binary semaphore for critical section

//consider the below three methods as atmoic operations
void init_sema(semaphore_t* s, int val){
  s->val = val;
}

void wait_sema(semaphore_t* s){
  while(s->val <= 0)
    put_thread_to_sleep();
  s->val -= 1;
}

void signal_sema(semaphore_t* s){
  s->val += 1;
  wake_one_thread();
}
//--------------------------------------------//
void* child(void* arg){
  printf("child\n");
  signal_sema(&s);
  return NULL;
 }

int main(int argc, char** argv){
  pthread_t p;
  semaphore_t s;
  printf("Parent\n);
  
  init_sema(&s, 0);
  thread_create(&p, NULL, child, NULL);
  wait_sema(&s);
  printf("Parent ends");
  
  return -0;
}
