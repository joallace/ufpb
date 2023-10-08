#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

typedef struct{
    int sum;
    float mean;
    int mode[2];        //index 0 = mode, index 1 = number of times it appeared
    char path[100];     //path to group, e.g. "dir/a"
}tMeasures;

pthread_barrier_t barrier;

void* getMeasures(void* data){
    char file[150];
    FILE *fp;

    int x;    
    char groupMode[10] = {0};
    tMeasures* result = (tMeasures*) data;
    result->sum = 0;

    for(int i = 0; i < NUM_THREADS; i++){
        sprintf(file, "%s%d.txt", result->path, i);     //getting a file from the path, e.g. "dir/a0.txt"
        if((fp = fopen(file, "r")) == NULL){
            printf("Could not open file or directory!\n");
            exit(-1);
        }

        for(int j = 0; j < NUM_THREADS; j++){
            fscanf(fp, "%d", &x);
            result->sum += x;
            groupMode[x]++;
        }

        fclose(fp);
    }

    result->mean = (float)result->sum/100;

    //Calculating group mode
    result->mode[0] = 0;
    result->mode[1] = groupMode[0];
    for(int i = 1; i < NUM_THREADS; i++){
        if(result->mode[1] < groupMode[i]){
            result->mode[0] = i;
            result->mode[1] = groupMode[i];
        }
    }

    pthread_barrier_wait (&barrier);
	pthread_exit(NULL);
}

int main(int argc, char** argv){
    pthread_t t[NUM_THREADS];

    const char* dir;
    char currentGroup[100];

    tMeasures results[10];

    //Total 
    int sum = 0;
    float mean = 0;
    int mode[11] = {0}; //Last index(10) is the total mode

    if(argc == 2){
        dir = argv[1];
        printf("Chosen directory: %s\n", dir);
    }
    else if(argc < 2)
    {
        printf("Missing parameters!\n./exec [file_dir/]\n");
        return -1;
    }else
    {
        printf("Too many parameters!\n./exec [file_dir/]\n");
        return -1;
    }

    pthread_barrier_init (&barrier, NULL, NUM_THREADS+1);
    
    for(int i = 0; i < NUM_THREADS; i++){
        sprintf(currentGroup, "%s%c", dir, 'a'+i);
        strcpy(results[i].path, currentGroup);
        pthread_create(&t[i], NULL, getMeasures, (void*) &results[i]);
    }

    pthread_barrier_wait (&barrier);

    for(int i = 0; i < NUM_THREADS; i++){
        printf("Group %c: sum= %d; mean= %f; mode= %d\n", 'A'+i, results[i].sum, results[i].mean, results[i].mode[0]);
        sum += results[i].sum;
        mean += results[i].mean;
        mode[results[i].mode[0]]++;
    }

    for(int i = 0, biggest = 0; i < NUM_THREADS; i++){
        if(biggest < mode[i]){
            mode[10] = i;
            biggest = mode[i];
        }
    }

    puts("------------------------------------------------------");
    printf("TOTAL: sum= %d; mean= %f; mode= %d\n", sum, mean/10, mode[10]);
}