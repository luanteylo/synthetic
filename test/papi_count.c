#include <papi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int Events[2] = { PAPI_TOT_CYC, PAPI_TOT_INS };
	int num_hwcntrs = 0;

	/* Initialize the PAPI library and get the number of counters available */
	if ((num_hwcntrs = PAPI_num_counters()) <= PAPI_OK){  
		puts("error");
	    return 1;
	}

	printf("This system has %d available counters.", num_hwcntrs);

	if (num_hwcntrs > 2)
	    num_hwcntrs = 2;
	/* Start counting events */
    if (PAPI_start_counters(Events, num_hwcntrs) != PAPI_OK){
    	puts("error");
    	return 1;
    }

    int retval;
	PAPI_dmem_info_t dmem;

	PAPI_get_dmem_info(&dmem);
	printf("Mem Size:\t\t%lld\n",dmem.size);
	printf("Mem Resident:\t\t%lld\n",dmem.resident);
	printf("Mem High Water Mark:\t%lld\n",dmem.high_water_mark);
	printf("Mem Shared:\t\t%lld\n",dmem.shared);
	printf("Mem Text:\t\t%lld\n",dmem.text);
	printf("Mem Library:\t\t%lld\n",dmem.library);
	printf("Mem Heap:\t\t%lld\n",dmem.heap);
	printf("Mem Locked:\t\t%lld\n",dmem.locked);
	printf("Mem Stack:\t\t%lld\n",dmem.stack);
	printf("Mem Pagesize:\t\t%lld\n",dmem.pagesize);


    return 0;
}
 