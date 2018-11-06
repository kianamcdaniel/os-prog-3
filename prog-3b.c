//
//  prog-3b.c
//  
//
//  Created by Kiana McDaniel on 11/1/18.
//

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

int fund = 4000;
int total_award = 0;
char stu = 'A';

pthread_mutex_t mutex;

void *calc_fund();

int main(){
    
    pthread_t tid[3];
    pthread_setconcurrency(3);
    
    int i;
    for(i = 0; i < 3; i++){
        pthread_create(&tid[i], NULL, (void *(*)(void *))calc_fund, NULL);
    }
    
    for(i = 0; i < 3; i++)
        pthread_join(tid[i], NULL);
    
    printf("TOTAL: $%d\n", total_award);
}

void *calc_fund(){
    
    char stu_id;
    pthread_mutex_lock(&mutex);
    stu_id = stu;
    stu++;
    pthread_mutex_unlock(&mutex);

    while(fund > 0){
        
        pthread_mutex_lock(&mutex);
        
        int award = ceil(fund * 0.25);
        fund -= award;
        printf("%c = %d\n", stu_id, award);
        total_award += award;
        
        pthread_mutex_unlock(&mutex);
        
        sleep(1);
    }
    
    return NULL;
}
