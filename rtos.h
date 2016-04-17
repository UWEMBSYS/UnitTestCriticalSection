#pragma once
#include <stdint.h>

/* These defines would likely be in the rtos headers, putting them here for simplicity in thei exercise */
typedef uint32_t ThreadId_t;
typedef struct {
  ThreadId_t id;
  /* other OS stuff would go here */
} ThreadContext_t;

ThreadId_t GetCurrentThreadId(void);