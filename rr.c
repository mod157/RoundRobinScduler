#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rr.h"


typedef struct
{
    char id;
    int remain;
} rr_task;

rr_task *tasks;
int total_task_cnt;
char *queue;
char last_running = 0;


void queue_push(char item)
{
    int i;

    for (i=0; queue[i]; i++);
    queue[i] = item;
}


char queue_pop()
{
    char ret = queue[0];
    int i;

    if (ret)
    {
        for (i=1; queue[i]; i++) queue[i-1] = queue[i];
        queue[i-1] = 0;
    }

    return ret;
}


int rr_init(int total_task)
{
    total_task_cnt = total_task;

    tasks = malloc((total_task + 2) * sizeof(rr_task));
    queue = malloc((total_task + 2) * sizeof(char));
    if (!tasks || !queue) return -1;

    memset(queue, 0, (total_task + 2) * sizeof(char));
    memset(tasks, 0, (total_task + 2) * sizeof(rr_task));
}


char rr_schedule(char new_task, size_t length)
{
    int i, ret_idx;
    char ret;

#ifdef DEBUG
    printf("[+] rr_schedule(%c, %d)\n", new_task, length);
#endif

    if (new_task)
    {
        for (i=0; tasks[i].id; i++);
        tasks[i].id = new_task;
        tasks[i].remain = length;
        queue_push(new_task);
    }

    if (last_running)
    {
        queue_push(last_running);
        last_running = 0;
    }

    ret = queue_pop();
    for (ret_idx=0; tasks[ret_idx].id; ret_idx++)
        if (tasks[ret_idx].id == ret) break;

    tasks[ret_idx].remain--;
    if (tasks[ret_idx].remain == 0)
    {
        for (i=ret_idx+1; tasks[i].id; i++) tasks[i-1] = tasks[i];
        tasks[i-1].id = 0;
        tasks[i-1].remain = 0;
    }
    else
    {
        last_running = ret;
    }

#ifdef DEBUG
    putchar('\n');
#endif

    return ret;
}


void rr_fini()
{
    if (tasks) free(tasks);
    if (queue) free(queue);
}


schedule_t rr = {
    .init = rr_init,
    .schedule = rr_schedule,
    .fini = rr_fini
};