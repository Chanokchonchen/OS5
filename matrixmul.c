#include <stdio.h>
#include <stdlib.h>
#include<pthread.h> 
#include<unistd.h>
#define MAX_THREAD 4 
int **arrayA;
int **arrayB;
int **result;
int n;
int step_i = 0;
void* multi(void* arg) 
{ 
    int core = step_i++; 
  
    // Each thread computes 1/4th of matrix multiplication 
    for (int i = core * n / MAX_THREAD; i < (core + 1) * n / MAX_THREAD; i++)  
        for (int j = 0; j < n; j++)  
            for (int k = 0; k < n; k++)  
                result[i][j] += arrayA[i][k] * arrayB[k][j];

    return 0;

} 

int main() {


    // section I : initialize matrix, do not modifie this section 
	scanf("%d", &n);



	arrayA = malloc(n * sizeof(int *));
    arrayB = malloc(n * sizeof(int *));
    result = malloc(n * sizeof(int *));
    
    int i,j,k;

	if(arrayA == NULL || arrayB == NULL || result == NULL) {
		printf("Out of memory\n");
		exit(1);
	}
	for(i = 0; i < n; i++) {
		arrayA[i] = malloc(n * sizeof(int));
        arrayB[i] = malloc(n * sizeof(int));
        result[i] = malloc(n * sizeof(int));
		if(arrayA[i] == NULL) {
			printf("Out of memory\n");
			exit(1);
		}
	}

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            result[i][j] = 0;
        }
    }


    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arrayA[i][j]);
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            scanf("%d", &arrayB[i][j]);
        }
    }

    // end of section I : initialize matrix, do not modifie this section 




    // section II : matrix multiplication modifie this section 

    // declaring four threads 

    pthread_t threads[MAX_THREAD];

    // Creating four threads, each evaluating its own part
     
    for (int i = 0; i < MAX_THREAD; i++) { 
        int* p; 
        pthread_create(&threads[i], NULL, multi, (void*)(p)); 
    } 
  
    // joining and waiting for all threads to complete 
    for (int i = 0; i < MAX_THREAD; i++)  
        pthread_join(threads[i], NULL);     
  

    // end of section II : matrix multiplication modifie this section 


    //Section III : Visualize 

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%d  ", result[i][j]);
            if (j == n - 1)
                printf("\n");
        }
    }

    // To print the matrix uncomment this section. 

    return 0;

}
