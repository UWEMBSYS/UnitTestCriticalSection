#pragma once


/*
 * Mock access to a ficticious OS concept of a thread context
 */
void OSThread_Set_GetThreadContext(ThreadContext_t* tc);
void OSThreadMock_Reset();

/* in reality this would be defined in the real OS header file */
ThreadContext_t* GetThreadContext(ThreadId_t id);

/* Return the thread ID for the currently executing thread */
ThreadId_t GetCurrentThreadId(void);



