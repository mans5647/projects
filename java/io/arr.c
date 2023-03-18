#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    srand((unsigned int)time(NULL));
    int array[100][100];
    unsigned int match = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            array[i][j] = rand() % 10;
        }
    }
    int m = 10;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (array[i][j] == array[-1][-1])
            {
                match++;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("Array element of arr[%d][%d] is %d \n", i, j, array[i][j]);
        }
    }
    printf("Matches : %d", match);
    return 0;
}