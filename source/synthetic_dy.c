#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <papi.h> 
#include <errno.h>

#include <math.h>
#include <time.h>


#ifndef STEP
	#define STEP 3
#endif

#ifndef M_SIZE
	#define M_SIZE 1000
#endif


#ifndef NUM_ITERATIONS
	#define NUM_ITERATIONS 20
#endif


#ifndef ALPHA // number of iterations on the computer phase
	#define ALPHA 500
#endif

#ifndef TETA // compute Intensive loop
	#define TETA 10000
#endif

#ifndef IO_SIZE // MEGA bytes writen/read 
	#define IO_SIZE 1
#endif


#ifndef MAT_CONTENT
	#define MAT_CONTENT 1
#endif

/*

Allocates the Matrix and writes a integer (512) in each matriz's position

*/
int ** alloc_matrix(int **M, int SIZE){

	M = (int**) malloc (SIZE * sizeof(int*));

	for(int i = 0; i < SIZE; i++){
		M[i] = (int*) malloc(SIZE * sizeof(int));
		for(int j = 0; j < SIZE; j++)
			M[i][j] = MAT_CONTENT;
	}

	return M;
}


void print_info(int SIZE){
	puts("############################################");
	printf("SIZE: %d\n", SIZE);
	printf("NUM_ITERATIONS: %d\n", NUM_ITERATIONS );
	printf("ALPHA: %d\n", ALPHA);
	printf("TETA: %d\n", TETA);
	printf("IO_SIZE: %d\n", IO_SIZE);
	printf("STEP: %d\n\n", STEP);

}

void handle_error(int error_code){
	if(error_code == EINVAL){
		errno = error_code;
		perror("");
	}else{
		printf("Papi error: %d ", error_code);
	}

	exit(1);
}


void mem_info(){
	int retval;
	PAPI_dmem_info_t dmem;
	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT)
		exit(1);
	
	retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT)
		handle_error(retval);

	PAPI_get_dmem_info(&dmem);

	printf("Mem Size kB:\t\t%lld\n",dmem.size);
	// printf("Mem Resident kB:\t\t%lld\n",dmem.resident);
	// printf("Mem High Water Mark kB:\t%lld\n",dmem.high_water_mark);
	// printf("Mem Shared kB:\t\t%lld\n",dmem.shared);
	// printf("Mem Text kB:\t\t%lld\n",dmem.text);
	// printf("Mem Library kB:\t\t%lld\n",dmem.library);
	printf("Mem Heap kB:\t\t%lld\n",dmem.heap);
	// printf("Mem Locked kB:\t\t%lld\n",dmem.locked);
	// printf("Mem Stack kB:\t\t%lld\n",dmem.stack);
	// printf("Mem Pagesize bytes:\t\t%lld\n",dmem.pagesize);	
}


int ** compute(int **M, int SIZE){
	double a = rand();

	
	for(int i = 0; i <= ALPHA; i++){
		// printf("-----------i: %d ------\n", i);
		int j = 0;
		while(j < SIZE){

			// Memory Acess Loop
			for(int l = 0; l < SIZE-2; l+= 3){
				// printf("l:%d j: %d M[l+1][j]: %d M[l+2][j]: %d\n", l, j, M[l+1][j], M[l+2][j]);
				M[l+1][j] = M[l][j] + M[l+2][j]; 
			}			

			j += STEP;
			// Compute Intensive Loop
			for(int k = 0; k < TETA; k++)
				a  = sqrt(a);
		}

	}
	return M;
}

void write_read(int step){
	FILE *fp;

	if(step % 2 == 0)//Write
		fp = fopen("io_file.txt", "w");
	else
		fp = fopen("io_file.txt", "r");
		

	char c;
	for(int i = 0; i < 1024 * 1024 * IO_SIZE; i++){
		if(step % 2 == 0){
			c = 'A' + (random() % 26);
			fprintf(fp, "%c", c);
		}else{
			fscanf(fp, "%c", &c);
		}
	
	}

	fclose(fp);

}


int main(int argc, char **argv){

	int **M;  // The matrix
	int SIZE = M_SIZE;
	
	if(argc == 2){
		SIZE = atoi(argv[1]);
	}

	clock_t begin = clock();

	srand(time(NULL));   // should only be called once

	print_info(SIZE);

	clock_t begin_alloc = clock();
	M = alloc_matrix(M, SIZE);
	clock_t end_alloc = clock();

	double time_spent_alloc = (double)(end_alloc - begin_alloc) / CLOCKS_PER_SEC;	


	double time_spent_comp = 0;
	double time_spent_io = 0;

	for(int i = 0; i < NUM_ITERATIONS; i++){

		clock_t begin_comp = clock();		
		M = compute(M, SIZE);
		clock_t end_comp = clock();

		clock_t begin_io = clock();
		write_read(i);
		clock_t end_io = clock();

		time_spent_comp += (double)(end_comp - begin_comp) / CLOCKS_PER_SEC;
		time_spent_io += (double)(end_io - begin_io) / CLOCKS_PER_SEC;

	}

	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Time Spent: %f\n", time_spent);
	printf("Allocation: %f (%f)\n", time_spent_alloc, 100*(time_spent_alloc/time_spent));
	printf("Compute: %f (%f) IO: %f (%f)\n", time_spent_comp, 100*(time_spent_comp/time_spent), time_spent_io, 100*(time_spent_io/time_spent));


	//Free memory	
	for(int i = 0; i < SIZE; i++)
		free(M[i]);
	free(M);


	return 0;
}














