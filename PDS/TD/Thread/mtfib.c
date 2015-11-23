
/*
 * Struture pour
 */
 struct arg_t{
   int n; /* Le n de fib*/
   int r; /* Le resultat de fib */
 }

int fib(int n){
  if(n<2){
    return n;
  }
  else{
    int x, y;
    x = fib(n-1);
    y = fib(n-2);
    return x+y;
  }
}

/*
 * Pleins de cast !
 */
void* mtfib(void* arg){
  int n = (int)arg; /* Le cast ne marche car le void et le int marche de la même facons */

  if(n<2){
    return (void *)n;
  }
  else{
    int status;
    void* x;
    void* y;

    pthread_t *thread_x;
    pthread_t *thread_y;

    status = pthread_create(&thread_x, NULL, (void *)n-1);
    assert(status == 0);
    status = pthread_create(&thread_y, NULL, (void *)n-2);
    assert(status == 0);

    pthread_join(thread_x, &x);
    pthread_join(thread_y, &y);

    return (void *)((int)x + (int)y);
  }
}

/*
 * Avec une structure
 */
void* mtfib(void* st){
  struct arg_t* a = (struct arg_t *) arg;
  int n = a-> n;

  if(n<2){
    a->r = n;
    return NULL;
  }
  else{
    int status;
    struct arg_t x;
    struct arg_t y;

    x.n = n-1;
    y.n = n-2;

    pthread_t *thread_x;
    pthread_t *thread_y;

    status = pthread_create(&thread_x, NULL, (void *)&x;
    assert(status == 0);
    status = pthread_create(&thread_y, NULL, (void *)&y);
    assert(status == 0);

    pthread_join(thread_x, NULL);
    pthread_join(thread_y, NULL);

    a->r = x.r + y.r;
    return NULL;
  }
}

int main(int argc, char const *argv[]) {
  struct arg_t a;
  a.n = atoi(argv[i]);
  mtfib((void*)a);
  exit(EXIT_SUCCESS);
}
