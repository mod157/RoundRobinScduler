#include <stdio.h>

#include "rr.h"
#include "r"


typedef struct
{
    char id;
    int arrival;  // arrival time
    int service;  // service time
} simulate_t;


void simulate(schedule_t sch, size_t total_cnt, simulate_t *sim)
{
    int total_service = 0;
    int i, t;

    for (i=0; i<total_cnt; i++) total_service += sim[i].service;
	
    // simulating
    sch.init(total_cnt);

    for (t=0; t<total_service; t++)
    {
        for (i=0; i<total_cnt; i++)
        {
            if (sim[i].arrival == t) break;
        }

        if (i != total_cnt)
            printf("%c ", sch.schedule(sim[i].id, sim[i].service));
        else
            printf("%c ", sch.schedule(0, 0));
    }

    putchar('\n');
    sch.fini();
}


int main(int argc, char *argv[])
{
	int i;
	schedule_t* schedule[] = {&rr, &hrrn};
    simulate_t test1[] = {
        {'A', 0, 3},
        {'B', 2, 6},
        {'C', 4, 4},
        {'D', 6, 5},
        {'E', 8, 2}
    };
	for (i = 0; i < 2; i++)
	{
		simulate(schedule[i], 5, test1);
	}
	system("pause");
	return 0;

}

