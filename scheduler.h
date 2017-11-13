#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdlib.h>

typedef struct {
    /**
     * init: 스케줄러 초기화
     *
     * @param total_task: 스케줄러에서 다룰 최대 task 수
     * @return 초기화에 성공하면 0, 아니면 0 이외의 값
     **/
    int (*init)(int total_task);

    /**
     * schedule: 스케줄러 동작. 이 함수는 매 시간마다 호출된다.
     *
     * @param new_task: 새로운 task가 들어왔을 경우 해당 task, 아니면 0
     * @param length: 새로운 task가 들어왔을 경우 해당 task의 수행 시간, 아니면 0
     * @return 현재 시간에 스케줄되어야 하는 task
     **/
    char (*schedule)(char new_task, size_t length);

    /**
     * fini: 스케줄러 정리
     **/
    void (*fini)(void);
} schedule_t;

#endif
