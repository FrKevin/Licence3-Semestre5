/* Exo 4*/

int count_me(int i){
  static int count = 0;
  int c;
  static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_lock(&mutex);
  count += i;
  c = count;
  pthread_mutex_unlock(&mutex);
  return c;
}
