#ifndef _THREAD_FUNCTIONS_H
#define _THREAD_FUNCTIONS_H

#include <pthread.h>

int Pthread_detach(pthread_t tid){
    int res = pthread_detach(tid);
    if(res>0){
        errno = res;
        perror("creating thread");
        exit(1); 
    }
    return res;
}

int Pthread_join(pthread_t tid, void **status){
    int res = pthread_join(tid, status);
    if(res>0){
        errno = res;
        perror("creating thread");
        exit(1); 
    }
    return res;
}

#endif