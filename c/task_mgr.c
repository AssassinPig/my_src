#include <stdio.h>
#include <pthread.h>
#include "task_mgr.h"

void* task_fun_pth(void* data)
{
    task_t* task = (task_t*)data;
    task_mgr_t* task_mgr = task->task_mgr;
    while(task->status != task_status_halt) {
        pthread_mutex_lock(&task->recv_task_mutex);

        while(task->status == task_status_idle){
           pthread_cond_wait(&task->recv_task_cond, &task->recv_task_mutex);   
        }
       
        if(task->status == task_status_running) {
            //excute process funcation
            printf("task_fun_pth\n");
            task->task_fun(task->task_data);

            pthread_mutex_lock(&task_mgr->free_task_mutex);
            task_mgr->free_task_count++;
            pthread_cond_signal(&task_mgr->finish_task_cond);
            pthread_mutex_unlock(&task_mgr->free_task_mutex);

            task->status = task_status_idle;
            pthread_mutex_unlock(&task->recv_task_mutex);
            continue;
        }

    }

    return NULL;
}

task_mgr_t* create_task_mgr(int count, pth_fun pfun) 
{
    task_mgr_t* mgr = (task_mgr_t*)malloc(sizeof(task_mgr_t));
    mgr->count = count;
    mgr->free_task_count = count;
    mgr->task_list = calloc(count, sizeof(task_t));
    mgr->status = task_mgr_status_idle;
    mgr->free_task_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    mgr->finish_task_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    pthread_create(&mgr->admin_pthid, NULL, task_mgr_loop, mgr); 
    for(int i=0; i<mgr->count; ++i) {
        mgr->task_list[i].task_mgr = mgr;
        mgr->task_list[i].recv_task_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
        mgr->task_list[i].recv_task_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        mgr->task_list[i].task_data = NULL;
        mgr->task_list[i].task_fun = pfun;
        pthread_create(&(mgr->task_list[i].pid), NULL, task_fun_pth, (void*)&(mgr->task_list[i]));  
    }

    return mgr;
} 

int clear_task_mgr(task_mgr_t* mgr)
{
    return 0;
}

void* task_mgr_loop(void* mgr_data)
{   task_mgr_t* mgr = (task_mgr_t*)mgr_data;
    while(mgr->status != task_mgr_status_exit) {
        //wait end all         
        printf("task_mgr_loop\n");
        sleep(1);
    } 

    return NULL;
}

int task_mgr_add_task(task_mgr_t* mgr, task_fun pfun, void* data)
{
    while(mgr->status != task_mgr_status_exit) {
        pthread_mutex_lock(&mgr->free_task_mutex); 

        while(!mgr->free_task_count) {
            pthread_cond_wait(&mgr->finish_task_cond, &mgr->free_task_mutex);
        }

        for(int i=0; i<mgr->count; ++i) {
            if(mgr->task_list[i].status == task_status_idle) {
                mgr->task_list[i].task_fun = pfun;
                mgr->task_list[i].task_data = data;              
                mgr->task_list[i].status = task_status_running;
                mgr->free_task_count--;
                pthread_cond_signal(&mgr->task_list[i].recv_task_cond);
                pthread_mutex_unlock(&mgr->task_list[i].recv_task_mutex); 
                pthread_mutex_unlock(&mgr->free_task_mutex); 
                break;
            }        
        }

    }

    return 0;
}

int db_query_task_fun(void* data)
{
    printf("db_quer_task_fun excuting ...\n");
    return 0;
}

int main(int argc, char **argv)
{
    task_mgr_t* task_mgr = create_task_mgr(10, task_fun_pth); 
    int i=10;
    while(i>0) {
        task_mgr_add_task(task_mgr, db_query_task_fun, NULL); 
        --i;
    }

    return 0;
}
