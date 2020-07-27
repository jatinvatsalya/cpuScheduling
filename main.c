#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"

struct PCB readyQueue[ 10 ] = {{0}};
int queue_count = 0;

int main()
{
    struct PCB currentProcess = {1, 1, 4, 1, 5, 4, 8};
    struct PCB newProcess = {2, 2, 3, 0, 0, 3, 6};
    struct PCB result;

    printf("Hello world!\n");
    printf( "\ncount = %d, pid = %d\n arrival_timestamp = %d\n total_bursttime= %d\n, execution_starttime = %d\n, execution_endtime = %d \n, remaining_bursttime = %d \n process_priority = %d\n\n",
           queue_count, readyQueue[0].process_id, readyQueue[0].arrival_timestamp, readyQueue[0].total_bursttime, readyQueue[0].total_bursttime, readyQueue[0].execution_starttime, readyQueue[0].execution_endtime,
           readyQueue[0].remaining_bursttime, readyQueue[0].process_priority );
    result = handle_process_arrival_pp( readyQueue, &queue_count, currentProcess, newProcess, 2);
    printf( "\ncount = %d, pid = %d\n arrival_timestamp = %d\n total_bursttime= %d\n, execution_starttime = %d\n, execution_endtime = %d \n, remaining_bursttime = %d \n process_priority = %d\n\n",
           queue_count, readyQueue[0].process_id, readyQueue[0].arrival_timestamp, readyQueue[0].total_bursttime, readyQueue[0].execution_starttime, readyQueue[0].execution_endtime,
           readyQueue[0].remaining_bursttime, readyQueue[0].process_priority );
    printf( "\ncount = %d, pid = %d\n arrival_timestamp = %d\n total_bursttime= %d\n, execution_starttime = %d\n, execution_endtime = %d \n, remaining_bursttime = %d \n process_priority = %d\n\n",
           queue_count, result.process_id, result.arrival_timestamp, result.total_bursttime, result.execution_starttime, result.execution_endtime,
           result.remaining_bursttime, result.process_priority );


    return 0;
}
