//
//  prog-3b.c
//  
//
//  Created by Kiana McDaniel on 11/1/18.
//

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

int fund = 4000;
int award = 0;
int total_award = 0;

pthread_mutex_t mutex;

void *calc_fund();

int main(){
    
    pthread_t tid[3];
    pthread_setconcurrency(3);
    
    for(int i = 0; i < 3; i++){
        pthread_create(&tid[i], NULL, (void *(*)(void *))calc_fund, NULL);
        sleep(1);
    }
    
    for(int i = 0; i < 3; i++)
        pthread_join(tid[i], NULL);
    
    printf("TOTAL: $%d\n", total_award);
}

void *calc_fund(){
    
    pthread_mutex_lock(&mutex);
    
    while(fund != 0){
        award = ceil(fund * 0.25);
        fund = fund - award;
        printf("%d\n", award);
        total_award += award;
    }
    
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}
