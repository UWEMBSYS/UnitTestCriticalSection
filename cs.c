#pragma once
#include <string.h>
#include "errcode.h"
#include "cs.h"
#include <intrinsics.h>
#include "rtos.h"


ErrCode_t InitializeCriticalSection(CriticalSection_t* pCS)
{
    ErrCode_t err = ERR_PARAM;
    
    if (NULL == pCS) {
      /* How should an already initialized CS be detected? Can it? Is it worthwhile? */
      
      pCS->count = 0;
      pCS->id    = 0;
      err = ERR_SUCCESS;
    }
    
    return err;
}

ErrCode_t EnterCriticalSection(CriticalSection_t* pCS)
{
    ErrCode_t err = ERR_PARAM;

    if (pCS) {
      /* Is it locked? */
      uint32_t locked;
      ThreadId_t id = GetCurrentThreadId();
      
      err = ERR_BUSY;
      
      locked = __LDREX(&pCS->count);
      if (locked != 0) {
        /* Is it locked by this thread? */
        if (pCS->id == id) {
          /* yes this thread has the lock, increment the count */
          /*  if the value got changed somewhere else, try again later to avoid a race */
          if (0 == __STREX(pCS->count+1, &pCS->count)) {
            err = ERR_SUCCESS;
          }
        } else {
          /* release the exclusive tracking */
          __CLREX();
        }
      } else if (0 == __STREX(1, &pCS->count)) {
          /* The CS is taken in this thread */
          /* Update the thread id here (should this be atomic, ie using ldrexr/strex??) */
          pCS->id = id;
          err = ERR_SUCCESS;
      } else {
        __CLREX();
      }
    }
    
    
    return err;
}


ErrCode_t LeaveCriticalSection(CriticalSection_t* pCS)
{
    ErrCode_t err = ERR_PARAM;
    if (pCS) {
      /* Is it locked? */
      uint32_t locked;
      ThreadId_t id = GetCurrentThreadId();
      
      
      locked = __LDREX(&pCS->count);
      if (locked != 0) {
        /* It is locked, is it this thread? */
        if (id == pCS->id) {
          /* Yes, this thread has the lock, decrement the count */
          if (pCS->count > 0) {
            __STREX(locked - 1, &pCS->count);
   
            /* shouldn't this be a loop to ensure that the lock gets released eventually? */
            /* it doesn't as this thread ID would be the same thread that would change the count */
            err = ERR_SUCCESS;
          }
        } else {
          err = ERR_BUSY;
        }
      } else {
        __CLREX();
        /* it wasn't locked, coding problem */
        err = ERR_UNINIT;
      }
    }
    return err;
}

ErrCode_t DeleteCriticalSection(CriticalSection_t* pCS)
{
    ErrCode_t err = ERR_UNIMPLEMENTED;

    /* Nothing really to do here */
    
    return err;
}




