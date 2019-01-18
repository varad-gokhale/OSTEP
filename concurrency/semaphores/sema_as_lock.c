//binary semaphore for critical section

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

volatile int counter = 0;

void* child(void* arg){
	for(int i = 0; i < 10; ++i)
	{
		wait_sema(&s);
		counter += 1;
		signal_sema(&s);
	}
	return NULL;
}

void main(int argc, char** argv)
{
	pthread_t t1, t2;
	semaphore_t s;
	
	init_sema(&s, 1);
	thread_create(&t1, NULL, child, NULL);
	thread_create(&t2, NULL, child, NULL);
	
	thread_join(&t1);
	thread_join(&t2);
	
	printf("counter = %d\n", counter);
	return 0;
}
