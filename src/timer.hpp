
#ifndef __TIMER__CPP__
#define __TIMER__CPP__

    #include <stdio.h>

    struct TimeShow
    {
        int s1;
        int s2;
        int m1;
        int m2;
    };

    class Timer
    {
    private:
        int ms;
        struct TimeShow ts;
    public:
        void InitTimer();
        void UpdateTimer(int loop_time);
        void ConvertTime();
        int MsToS();
        void ResetTimer();
        void PrintConsoleTime();
    };

    void Timer::ResetTimer()
    {
        ms = 0;
    }

    void Timer::InitTimer()
    {
        ts = {0,0,0,0};
        ms = 0;
    }   

    void Timer::UpdateTimer(int loop_time)
    {
        if (loop_time > 60)
            ms += loop_time;
        else 
            ms += 60 - loop_time;
    }

    void Timer::ConvertTime()
    {
        int seconds = ms/1000;    // ms -> s
        int minuts = seconds/60;  // s -> m

        ts.m1 = minuts/10;
        ts.m2 = minuts%10;

        ts.s1 = seconds/10;
        ts.s2 = seconds%10;
    }      

    int Timer::MsToS()
    {
        return ms/1000;
    } 

    void Timer::PrintConsoleTime()
    {
        ConvertTime();
        printf("Game time : %d%d:%d%d\n", ts.m1, ts.m2, ts.s1, ts.s2);
    }

#endif