#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdio.h>
int main(void) {
	long pt;
	while(1){

  pt = syscall(376);
	printf("%d\n",pt);
	sleep(1);
}
return 0;
}
