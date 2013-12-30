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

int db_query_task_fun(void* data)
{
    return 0;
}

task_mgr_t* create_task_mgr(int count, task_fun fun) 
{
    task_mgr_t* ret_mgr = (task_mgr_t*)malloc(sizeof(task_mgr_t));
    ret_mgr->count = count;
    ret_mgr->free_task_count = count;
    ret_mgr->task_list = calloc(count, sizeof(task_t));
    ret_mgr->status = task_mgr_status_idle;
    ret_mgr->free_task_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    ret_mgr->finish_task_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    return ret_mgr;
} 

int clear_task_mgr(task_mgr_t* mgr)
{
    return 0;
}

void task_mgr_loop(task_mgr_t* mgr)
{
    for(int i=0; i<mgr->count; ++i) {
        mgr->task_list[i].task_mgr = mgr;
        mgr->task_list[i].recv_task_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
        mgr->task_list[i].task_data = NULL;
        pthread_create(&(mgr->task_list[i].pid), NULL, task_fun_pth, (void*)&(mgr->task_list[i]));  
    }

    while(mgr->status != task_mgr_status_exit) {
        //wait end all         
    } 
}

int task_mgr_add_task(task_mgr_t* mgr, void* data)
{
    while(mgr->status != task_mgr_status_exit) {
        pthread_mutex_lock(&mgr->free_task_mutex); 

        while(!mgr->free_task_count) {
            pthread_cond_wait(&mgr->finish_task_cond, &mgr->free_task_mutex);
        }

        for(int i=0; i<mgr->count; ++i) {
            if(mgr->task_list[i].status == task_status_idle) {

                mgr->task_list[i].task_data = data;              
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

int main(int argc, char **argv)
{
    return 0;
}
