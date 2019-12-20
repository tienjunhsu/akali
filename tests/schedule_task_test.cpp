#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#include <iostream>
#include "gtest/gtest.h"
#include "ppxbase/schedule_task.h"
#include "ppxbase/scoped_com_initializer.h"
#include <strsafe.h>
#include <ShlObj.h>

TEST(ScheduleTaskTest, test1) {
    ppx::base::ScopedCOMInitializer com;
    
    ppx::base::ScheduleTask st;

    TCHAR szProgramPath[MAX_PATH] = { 0 };
    EXPECT_TRUE(st.GetProgramPath(TEXT("Steambox"), 1, szProgramPath));

    TCHAR szParameters[MAX_PATH] = { 0 };
    EXPECT_TRUE(st.GetParameters(TEXT("Steambox"), 1, szParameters));
}

#endif