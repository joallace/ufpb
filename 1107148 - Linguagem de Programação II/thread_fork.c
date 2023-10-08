#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t idLock = PTHREAD_MUTEX_INITIALIZER;
int tId = 1;

void* useThread(void* param){
	int n = (int) param;
	char dest[50];

	pthread_mutex_lock(&idLock);
	sprintf(dest, "thread%d.txt", tId++);
	pthread_mutex_unlock(&idLock);
	FILE *fp = fopen(dest, "w");

	for(int j = 0; j < n; j++)
		fprintf(fp,"%d\n", rand()%100);

	fclose(fp);
	pthread_exit(NULL);
}

void useFork(int nInstances, int n){
	char dest[50];
	FILE *fp;

	for(int j = 0; j < nInstances; j++){
		if(fork() == 0){
			srand(time(NULL)^getpid());
			sprintf(dest, "fork%d.txt", (int)getpid());
			fp = fopen(dest, "w");
			for(int j = 0; j < n; j++)
				fprintf(fp,"%d\n", rand()%100);
			fclose(fp);
			exit(0);
		}
	}
}

int main(int argc, char** argv){
	int nInstances, nNumbers;
	
	if(argc == 4){
		nInstances = atoi(argv[1]);
		nNumbers = atoi(argv[2]);
	}
	else{
		printf("Missing parameters!\n./exec [nInstances] [nNumbers] [execution mode: (-t or -f)]\n");
		exit(-1);
	}

	pthread_t t[nInstances];

	srand(time(NULL));

	if(argc > 2){	//Checks execution method (thread(-t) or fork(-f))
		switch(argv[3][1]){
			case 'f':
				useFork(nInstances, nNumbers);
				break;

			case 't':
				for(int i = 0; i < nInstances; i++)
					pthread_create(&t[i], NULL, useThread, (void*) nNumbers);
				for(int i = 0; i < nInstances; i++)
					pthread_join(t[i], NULL);
				break;

			default:
				printf("Wrong execution flag! Use -f or -t instead\n");
				exit(-1);
		}
	}
	return 0;
}
