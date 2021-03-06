#include <pthread.h>  
#include <iostream> 
#include <stdlib.h>
#include <assert.h>

#include "sync01.h"
#include "sync02.h"
#include "stateful001.h"
#include "stateful002.h"

int inputX = 0;
int inputY = 0;
int data1 = -1, data2 = -1, data3 = -1, data4 = -1;
pthread_mutex_t m;

void add1()
{
    data1++;
    sync01();
}
void add2()
{
    data2++;
    sync02();
}
void add3()
{
    data3++;
    stateful001();
}
void add4()
{
    data4++;
    stateful002();
}
void lock()
{
    pthread_mutex_lock(&m);
}
void unlock()
{
    pthread_mutex_unlock(&m);
}

void *thread1(void *arg){
    data1++;
    data2++;
    data3++;
    data4++;
}
void *thread2(void *arg){
    if(inputX > 0 && inputY > 0)
    {
        add1();
        add3();
    }
    else if(inputX > 0 && inputY <= 0)
    {
        add1();
        add4();
    }
    else if(inputX <= 0 && inputY > 0)
    {
        add2();
        add3();
    }
    else
    {
        add2();
        add4();
    }
}

int main(int argc, char ** argv) {

    inputX = atoi(argv[1]);
    inputY = atoi(argv[2]);
    
    pthread_t t1,t2;
    
    pthread_create(&t1, 0, thread1, 0);
    pthread_create(&t2, 0, thread2, 0);
    
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    
    int sum = data1+data2+data3+data4;
    std::cout << "sum = " << sum << std::endl;
    
    return 0;
} 
