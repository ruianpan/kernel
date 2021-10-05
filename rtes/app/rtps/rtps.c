#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>

typedef struct mythread_struct{
   pid_t pid;
   pid_t tid;
   unsigned int rt_priority;
   char	comm[16];
} mythread_struct;

int main(void) {
	long num;
	long newn;
	int i,j;
	mythread_struct temp;
	mythread_struct*input;
	while(1){

  num = syscall(376);

	if(num > 0){
		input = (mythread_struct*)malloc(sizeof(mythread_struct)*num);
		newn = syscall(377, input, num);

		for(i = 0; i<num; i++){
			for(j = 0; j<num-i-1; j++){
				if(input[j].rt_priority<input[j+1].rt_priority){
					temp = input[j+1];
					input[j+1] = input[j];
					input[j] = temp;
				}
			}
		}

		for(i = 0; i<num;i++ ){
			printf("pid:%d, tid:%d, priority: %d, %s\n",input[i].pid,input[i].tid,input[i].rt_priority,input[i].comm);

		}
	}

	sleep(2);
}
return 0;
}
