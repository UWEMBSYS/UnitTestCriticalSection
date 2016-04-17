/*
 * Unit tests for critical section code
 *
 */
#include "cs.h"
#include "unittest.h"
#include "mock_osthread.h"

UTGLOBALS();

UT(VerifyUninitializedCSFailedEnter)
{
  CriticalSection_t cs;

  ASSERT_EQ(ERR_UNINIT, EnterCriticalSection(&cs));
  return UT_PASSED;
}

/*
<insert lots more tests here, fixing the implementation of the critical section as you go to get them going>

<how are you going to test different threads, e.g. thread 1 holds the lock, thread 2 should not be able to take it?>
 (think about mocking the OS concept of a thread)
*/
void ut_cs(void)
{
 UTRUN(VerifyUninitializedCSFailedEnter);

 UTTOTALS();
}

