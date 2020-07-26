#include "oslabs.h"

static int addRequest(  //we need to clear that if queue is full then what to do.
  struct PCB request_queue[],
  int *queue_cnt,
  struct PCB request );

static BOOL isNullPcb(struct PCB input);

struct PCB handle_process_arrival_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int timestamp)
{
    int iAdded;
    struct PCB result = {0, 0, 0, 0, 0, 0, 0};

    if ( isNullPcb(current_process) )
    {
        memcpy( &result, &new_process, sizeof( result ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
    }
    else if ( new_process.process_priority >= current_process.process_priority )
    {
        memcpy( &result, &current_process, sizeof( result ) );
        iAdded = addRequest( ready_queue, queue_cnt, new_process );
        ready_queue[iAdded].execution_starttime = 0;
        ready_queue[iAdded].execution_endtime = 0;
        ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
        ++(*queue_cnt);
    }
    else
    {
        iAdded = addRequest( ready_queue, queue_cnt, new_process );
        memcpy( &result, &new_process, sizeof( result ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
        ready_queue[iAdded].execution_endtime = 0;
        ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
    }
}

static int addRequest(  //we need to clear that if queue is full then what to do.
  struct PCB request_queue[],
  int *queue_cnt,
  struct PCB request )
{
  int i;
  int result;

  if( ! isNullPcb( request ) )
  {
    for( i = 0; i < QUEUEMAX; ++i )
    {
      if ( isNullPcb( request_queue[ i ] ) )
      {
        ++(*queue_cnt);
        memcpy( &request_queue[ i ], &request, sizeof( request ) );
        result = i;
        i = QUEUEMAX;
      }
    }
  }

  return result;
}

static BOOL isNullPcb(struct PCB input)
{
    BOOL result = FALSE;

    if ( (input.process_id == 0) &&
         (input.arrival_timestamp == 0) &&
         (input.total_bursttime == 0) &&
         (input.execution_starttime == 0) &&
         (input.execution_endtime == 0) &&
         (input.remaining_bursttime == 0) &&
         (input.process_priority == 0) )
    {
        result = TRUE;
    }

    return result;
}
