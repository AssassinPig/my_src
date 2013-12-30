#ifndef __TASK_MGR_H__ 
#define __TASK_MGR_H__

#include <pthread.h>
enum task_status{
    task_status_idle,
    task_status_running,
    task_status_halt,
    task_status_max,
};

enum task_mgr_status {
    task_mgr_status_idle,
    task_mgr_status_exit,
    task_mgr_status_max,
};

typedef struct task_mgr task_mgr_t; 
struct task{
    enum task_status status; 
    int (*task_fun)(void* data);

    pthread_t pid;
    void* task_data;
    pthread_cond_t recv_task_cond;
    pthread_mutex_t recv_task_mutex;
    task_mgr_t* task_mgr;
};
typedef struct task task_t;

struct task_mgr{
    int count; 
    task_t* task_list;
    enum task_mgr_status status;
    pthread_cond_t finish_task_cond;
    int free_task_count;
    pthread_mutex_t free_task_mutex;
    pthread_t admin_pthid;
};

typedef int (*task_fun)(void* data);
typedef void* (*pth_fun)(void* data);

void* task_fun_pth(void* data);

task_mgr_t* create_task_mgr(int count, pth_fun pfun); 

int clear_task_mgr(task_mgr_t* mgr);

void* task_mgr_loop(void* mgr_data);

int task_mgr_add_task(task_mgr_t* mgr, task_fun pfun, void* data);

#endif //__TASK_MGR_H__
