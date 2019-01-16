// pseudo-code for correct usage of CVs
// some incorrect usages(except for number 4) ==> http://pages.cs.wisc.edu/~remzi/Classes/537/Spring2018/Discussion/Handout-CVDef+ForkJoinProblem.pdf

mutex_t m;
cond_t c;
volatile int done = 0;

void* child(void* arg){
  printf("child\n");
  
  //the important stuff
  mutex_lock(&m);             //remember to acquire the mutex before doing stuff and signalling
  done = 1;
  cond_signal(&c);
  mutex_unlock(&m);
  
  return NULL;
}

int main(int argc, char** argv){
  thread_t p;
  printf("parent begin\n");
  Pthread_create(&p, 0, child, 0);

//the important stuff
  mutex_lock(&m);             //always remember to acquire mutex before waiting on CV
  while(done == 0)
    wait(&c,&m);
  mutex_unlock(&m);           //do this too
  
  printf("parent_end\n");
  return 0;
}
