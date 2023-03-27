// #include <pthread.h>
//    #include <stdlib.h>
//    #include <unistd.h>
//    #include <stdio.h>
//  void *thread_function(void *arg) {
//   int i;
//   for ( i=0; i<8; i++) {
//     printf("Thread working...! %d \n",i);
//     sleep(1);
//   }
//   return NULL;
// }
// int main(void) {
//   pthread_t mythread;
//   pthread_t mythread2;
  
  
//     pthread_attr_t attr;
//     pthread_attr_init(&attr);
//     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);


//   if ( pthread_create( &mythread, NULL, thread_function, NULL) ) {
//     printf("error creating thread.");
//     abort();
//   }
//   if ( pthread_create( &mythread2, &attr, thread_function, NULL) ) {
//     printf("error creating thread.");
//     abort();
//   }
// //   if ( pthread_join ( mythread, NULL ) ) {
// //     printf("error join thread.");
// //     abort();
// //   }
// sleep(5);
//   printf("thread done! \n");
//   exit(0);
// }



#include <dirent.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
void* thread1(void *arg)
{
    while (1)
    {
        printf("thread1 running...!\n");
        sleep(1);
    }
    printf("Leave thread1!\n");

    return NULL;
}

int main(int argc, char** argv)
{
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // 设置分离属性

    pthread_create(&tid, &attr, thread1, NULL);
    pthread_attr_destroy(&attr);

    sleep(3);
    printf("Leave main thread!\n");

    return 0;
}