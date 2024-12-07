
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stream.hpp"
#include "globals.hpp"

int WriteUserStats(int BestScore, int time)
{
    char writting_buffer[200];
    FILE *file = fopen(USERSTATS_FILENAME, "w");
    if (file == NULL)
        return 0;
    sprintf(writting_buffer, "BEST: %d\nBEST TIME: %d\n", BestScore, time);
    if (fputs(writting_buffer, file) != 1)
    {
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}

int GetUserStats(int *BestScore, int *BestTime)
{
    char BestScoreText[20], BestTimeText[20];
    char buffer[50];
    FILE *file = fopen(USERSTATS_FILENAME, "r");
    if (file == NULL)
        return 0;

    if (fgets(buffer, 50, file))
    {
        strcpy(BestScoreText, buffer+6);
        *BestScore = atoi(BestScoreText);
        if (fgets(buffer, 50, file))
        {   
            strcpy(BestTimeText, buffer+11);
            *BestTime = atoi(BestTimeText);
        }
    }
    else 
    {
        *BestScore = 0;
        *BestTime = 0;
    }
    

    fclose(file);
    return 1;
}

int SaveUserStats(int BestScore, int BestTime)
{
    return WriteUserStats(BestScore, BestTime);
}


long GetFileSize(FILE *file)
{
    long size;
    fseek(file, SEEK_END, 0);
    size = ftell(file);
    fseek(file, 0, 0);
    
    return size;
}

int GetVersion(char *buffer)
{
    FILE *file = fopen(VERSION_FILENAME, "r");
    if (file == NULL)
        return 0;
    
    fgets(buffer, 10, file);
    printf("version: %s\n", buffer);
    fclose(file);
    return 1;
}