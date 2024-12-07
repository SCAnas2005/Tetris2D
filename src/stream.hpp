
#ifndef __STREAM__CPP__
#define __STREAM__CPP__

    #include "util.hpp"

    #define USERSTATS_FILENAME USERSTATS_FOLDER"stats.txt"
    #define VERSION_FILENAME VERSIONFOLDER"version.txt"

    int SaveUserStats(int BestScore, int time);
    int GetUserStats(int *BestScore, int *BestTime);
    long GetFileSize(FILE *file);

    int GetVersion(char *buffer);

#endif
