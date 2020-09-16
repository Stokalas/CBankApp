#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"
void clrscr()
{
    /*clearing everything in the console*/
    system("@cls||clear");
}

void delay(int number_of_seconds)
{
    /* Converting time into milli_seconds*/
    int milli_seconds = 1000 * number_of_seconds;
    /* Storing start time*/
    clock_t start_time = clock();
     /*looping till required time is not achieved*/
    while (clock() < start_time + milli_seconds);
}
