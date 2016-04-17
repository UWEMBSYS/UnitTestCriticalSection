#pragma once
#include <stdio.h>
#include <stdbool.h>


#define UTPRINT printf

#define __utname__ __func__

typedef enum {
    UT_SKIPPED,
    UT_FAILED,
    UT_PASSED,
} UTResult_t;

#define UTGLOBALS()                 static unsigned __UTPassed = 0; static unsigned __UTTestCount=0; static unsigned __UTSkipped=0;
#define UTFAIL()                    { return UT_FAILED; }
#define UTSKIP()                    { ++__UTSkipped; return UT_SKIPPED; }
#define UTFAIL_EQ(e,a)              { UTPRINT("%s:%u Not Equal %x vs %x\r\n", __utname__,__LINE__, (e),(a)); UTFAIL(); }
#define UTFAIL_NE(e,a)              { UTPRINT("%s:%u Equal %x vs %x\r\n", __utname__,__LINE__, (e),(a)); UTFAIL(); }
#define UTFAIL_EQ_BUF(i)            { UTPRINT("%s:%u Buf Not Equal at %x\r\n", __utname__,__LINE__, i); UTFAIL(); }
#define UTFAIL_TRUE(a)              { UTPRINT("%s:%u False %x\r\n", __utname__,__LINE__, (a)); UTFAIL(); }
#define UTFAIL_FALSE(a)             { UTPRINT("%s:%u True %x\r\n", __utname__,__LINE__, (a)); UTFAIL(); }


#define ASSERT_EQ(expected,actual)  { ++__UTTestCount; if (expected!=actual) {UTFAIL_EQ(expected,actual);}              ++__UTPassed; }
#define ASSERT_NE(expected,actual)  { ++__UTTestCount; if (expected==actual) {UTFAIL_NE(expected,actual);}              ++__UTPassed; }
#define ASSERT_TRUE(actual)         { ++__UTTestCount; if (!actual)          {UTFAIL_TRUE(actual);}                     ++__UTPassed; }
#define ASSERT_FALSE(actual)        { ++__UTTestCount; if (actual)           {UTFAIL_FALSE(actual);}                    ++__UTPassed; }
#define ASSERT_BUF_EQ(e,a,len)      { ++__UTTestCount; for(uint8_t __i=0;__i<len;++__i) {\
                                                                             if(e[__i]!=a[__i]) {UTFAIL_EQ_BUF(__i);}}    ++__UTPassed; }


#define UT(testname)                static UTResult_t  ut_##testname(void)
#define UTRUN(testname)             { ut_##testname();}
#define UTTOTALS()                  { printf("\r\n%s:%u %s: Count:%u Passed:%u Skipped:%u\r\n ",__FILE__,__LINE__, (__UTPassed==__UTTestCount) ? "PASS":"FAIL", __UTTestCount, __UTPassed, __UTSkipped);}


