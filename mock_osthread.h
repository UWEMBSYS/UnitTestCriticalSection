#pragma once

/*
 * Mock access to a ficticious OS concept of a thread context
 */
void OSThread_Set_GetThreadContext(ThreadConext_t* tc);
void OSThreadMock_Reset();

/* in reality this would be defined in the real OS header file */
Thread_context_t* GetThreadContext(ThreadId_t id);



