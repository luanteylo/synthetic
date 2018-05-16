#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <papi.h> 
#include <errno.h>

#define STEP_SCALE 512


int ** start_matrix(int **mat, int mat_size){
	mat = (int**) malloc (mat_size * sizeof(int*));

	for(int i = 0; i < mat_size; i++){
		mat[i] = (int *) malloc(mat_size * sizeof(int));

		for(int j = 0; j < mat_size; j++) 
			mat[i][j] = STEP_SCALE;			
		
	}

	return mat;
}


void print_matrix(int **mat, int mat_size){
	printf("#### Matrix %d x %d ####\n", mat_size, mat_size);

	// for(int i = 0; i < mat_size; i++){
	// 	for(int j = 0; j < mat_size; j++){
	// 		printf("%d ", mat[i][j]);
	// 	}
	// 	printf("\n");
	// }
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
	printf("Mem Heap GB:\t\t%f\n",((dmem.heap/1024.0)/1024.0));
	// printf("Mem Locked kB:\t\t%lld\n",dmem.locked);
	// printf("Mem Stack kB:\t\t%lld\n",dmem.stack);
	// printf("Mem Pagesize bytes:\t\t%lld\n",dmem.pagesize);
	
}


int main(int argc, char **argv){
	int **mat; 
	int mat_size;
	int sleep_time;

	if(argc < 3){
		handle_error(EINVAL);
	}else{
		mat_size = atoi(argv[1]);
		sleep_time = atoi(argv[2]);
	}

	

	mat = start_matrix(mat, mat_size);

	print_matrix(mat, mat_size);

	mem_info();


	sleep(sleep_time);
	

	//Free memory	
	for(int i = 0; i < mat_size; i++)
		free(mat[i]);
	free(mat);






	return 0;
}













