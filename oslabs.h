#ifndef OSLABS_H_INCLUDED
#define OSLABS_H_INCLUDED

#define QUEUEMAX 10

typedef enum {
   FALSE, TRUE
}BOOL;

struct PCB {
        int process_id;
        int arrival_timestamp;
        int total_bursttime;
        int execution_starttime;
        int execution_endtime;
        int remaining_bursttime;
        int process_priority;
    };

struct PCB handle_process_arrival_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int timestamp);

struct PCB handle_process_completion_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp);

struct PCB handle_process_arrival_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int time_stamp);

struct PCB handle_process_completion_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp);

#endif // OSLABS_H_INCLUDED
