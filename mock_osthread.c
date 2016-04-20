#pragma once
#include "rtos.h"
#include <string.h>

/*
 * Mock access to a ficticious OS concept of a thread context
 * The first block contains the methods to manipulate the data used in the mock.
 * the second block contains the mock implementation of the OSThread "class"
 */

/* Setup initial state to be reasonable */
static ThreadContext_t mock_thread_context = {0};
static ThreadContext_t* pmock_thread_context = &mock_thread_context;
void OSThread_Set_GetThreadContext(ThreadContext_t* tc)
{
    /* copy the thread context or set to null */
    if (tc) {
        memcpy(&mock_thread_context, tc, sizeof(mock_thread_context));
        pmock_thread_context = &mock_thread_context;
    } else {
        pmock_thread_context = NULL;
    }
}


ThreadId_t mock_current_threadid = 1;
void OSThread_Set_GetCurrentThreadId(ThreadId_t id)
{
  mock_current_threadid = id;
}

void OSThreadMock_Reset()
{
 /* set all globals to some reasonable default */
    memset(&mock_thread_context,0,sizeof(mock_thread_context));
    pmock_thread_context = &mock_thread_context;
    mock_current_threadid = 0;
}



/*********************************************************************/

/*
 * The implementation of the OSThread class's GetThreadContext method
 */
ThreadContext_t* GetThreadContext(ThreadId_t id)
{
 return pmock_thread_context;
}

ThreadId_t GetCurrentThreadId(void)
{
  return mock_current_threadid;
}


