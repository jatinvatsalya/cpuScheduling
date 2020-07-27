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
        memcpy( &result, &new_process, sizeof( struct PCB ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
    }
    else if ( new_process.process_priority >= current_process.process_priority )
    {
        memcpy( &result, &current_process, sizeof( struct PCB ) );
        iAdded = addRequest( ready_queue, queue_cnt, new_process );
        ready_queue[iAdded].execution_starttime = 0;
        ready_queue[iAdded].execution_endtime = 0;
        ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
    }
    else
    {
        iAdded = addRequest( ready_queue, queue_cnt, current_process );
        memcpy( &result, &new_process, sizeof( struct PCB ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
        ready_queue[iAdded].execution_endtime = 0;
    //    ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
    }

    return result;
}

struct PCB handle_process_completion_pp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp)
{
    int i;
    int iHigh;
    int initialized = 0;
    struct PCB result = {0, 0, 0, 0, 0, 0, 0};

    if ( *queue_cnt )
    {
        for ( i = 0; i < QUEUEMAX; ++i )
        {
            if ( ! initialized )
            {
                initialized = 1;
                iHigh = i;
            }
            if ( ready_queue[ i ].process_priority < ready_queue[ iHigh ].process_priority )
            {
                iHigh = i;
            }
        }
        memcpy( &result, &ready_queue[ iHigh ], sizeof(struct PCB) );
        memset( &ready_queue[ iHigh ], 0, sizeof( struct PCB ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.remaining_bursttime;
        --(*queue_cnt);
    }

    return result;
}

struct PCB handle_process_arrival_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    struct PCB current_process,
    struct PCB new_process,
    int time_stamp)
{
    int iAdded;
    struct PCB result = {0, 0, 0, 0, 0, 0, 0};

    if ( isNullPcb(current_process) )
    {
        memcpy( &result, &new_process, sizeof( struct PCB ) );
        result.execution_starttime = time_stamp;
        result.execution_endtime = time_stamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
    }
    else if ( current_process.remaining_bursttime < new_process.total_bursttime )
    {
        memcpy( &result, &current_process, sizeof( struct PCB ) );
        iAdded = addRequest( ready_queue, queue_cnt, new_process );
        ready_queue[iAdded].execution_starttime = 0;
        ready_queue[iAdded].execution_endtime = 0;
        ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
    }
    else
    {
        iAdded = addRequest( ready_queue, queue_cnt, current_process );
        memcpy( &result, &new_process, sizeof( struct PCB ) );
        result.execution_starttime = time_stamp;
        result.execution_endtime = time_stamp + result.total_bursttime;
        result.remaining_bursttime = result.total_bursttime;
        ready_queue[iAdded].execution_starttime = 0;
        ready_queue[iAdded].execution_endtime = 0;
        ready_queue[iAdded].remaining_bursttime = ready_queue[iAdded].total_bursttime;
    }
}

struct PCB handle_process_completion_srtp(
    struct PCB ready_queue[QUEUEMAX],
    int *queue_cnt,
    int timestamp)
{
    int i;
    int iLow;
    int initialized = 0;
    struct PCB result = {0, 0, 0, 0, 0, 0, 0};

    if ( *queue_cnt )
    {
        for ( i = 0; i < QUEUEMAX; ++i )
        {
            if ( ! initialized )
            {
                initialized = 1;
                iLow = i;
            }
            if ( ready_queue[ i ].remaining_bursttime < ready_queue[ iLow ].remaining_bursttime )
            {
                iLow = i;
            }
        }
        memcpy( &result, &ready_queue[ iLow ], sizeof(struct PCB) );
        memset( &ready_queue[ iLow ], 0, sizeof( struct PCB ) );
        result.execution_starttime = timestamp;
        result.execution_endtime = timestamp + result.remaining_bursttime;
        --(*queue_cnt);
    }

    return result;
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
        memcpy( &request_queue[ i ], &request, sizeof( struct PCB ) );
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
