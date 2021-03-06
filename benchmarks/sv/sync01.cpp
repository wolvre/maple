/* 
 * File:   sync01.cpp
 * Author: dkeeper
 * 
 * Created on 2014年8月27日, 下午3:01
 */

#include "sync01.h"

#include <stdio.h> 
#include <pthread.h>
#include <assert.h>

int num_sy01;

pthread_mutex_t m_sy01;
pthread_cond_t empty_sy01, full_sy01;

void * thread1_sync01(void * arg) {
    pthread_mutex_lock(&m_sy01);

    while (num_sy01 > 0)
        pthread_cond_wait(&empty_sy01, &m_sy01);

    num_sy01++;

    pthread_mutex_unlock(&m_sy01);
    pthread_cond_signal(&full_sy01);
}

void * thread2_sync01(void * arg) {
    pthread_mutex_lock(&m_sy01);

    while (num_sy01 == 0)
        pthread_cond_wait(&full_sy01, &m_sy01);

    num_sy01--;

    pthread_mutex_unlock(&m_sy01);

    pthread_cond_signal(&empty_sy01);
}

sync01::sync01() {
    pthread_t t1, t2;

    num_sy01 = 1;

    pthread_mutex_init(&m_sy01, 0);
    pthread_cond_init(&empty_sy01, 0);
    pthread_cond_init(&full_sy01, 0);

    pthread_create(&t1, 0, thread1_sync01, 0);
    pthread_create(&t2, 0, thread2_sync01, 0);

    pthread_join(t1, 0);
    pthread_join(t2, 0);

    assert(num_sy01 == 1);
    //    if (num != 1) {
    //ERROR:
    //        goto ERROR;
    //        ;
    //    }
}

sync01::sync01(const sync01& orig) {
}

sync01::~sync01() {
}

