#include "philo.h"

// pthread_mutex_t lock;
// int counter = 0;

// void* increment(void *arg)
// {
//     for(int i = 0; i < 100000; i++)
//     {
//         pthread_mutex_lock(&lock);
//         counter++;
//         pthread_mutex_unlock(&lock);
//     }
//     return NULL;
// }

// int main()
// {
//     pthread_t t1, t2;
//     pthread_mutex_init(&lock, NULL);
//     pthread_create(&t1, NULL, increment, NULL);
//     pthread_create(&t2, NULL, increment, NULL);
    
//     pthread_join(t1 , NULL);
//     pthread_join(t2 , NULL);

//     pthread_mutex_destroy(&lock);

//     printf("counter = %d \n", counter);
//     return 0;
// }


void *thread_function(void *arg) {
    printf("Thread is running...\n");
    // sleep(2);
    printf("Thread finished!\n");
    return NULL;
}

int main() {
    pthread_t thread;
    
    // إنشاء Thread جديد
    pthread_create(&thread, NULL, thread_function, NULL);

    // فصل الـ Thread باش يخدم بلا `pthread_join`
    pthread_detach(thread);

    printf("Main thread is done.\n");

    // sleep(3); // ننتظر قليلا حتى يظهر خروج الـ Thread
    return 0;
}