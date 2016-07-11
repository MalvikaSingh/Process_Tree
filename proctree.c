#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int order = 1;

void main(){

	int pid1, pid2, pid;
	int i, level = 0;

	printf("[%d] pid = %d ppid = %d\n",order, getpid(), getppid());

	for(level = 0; level < 2; level++){
	pid1 = fork(); 
	
	if(pid1 == 0) {order*= 2; printf("[%d] pid = %d ppid = %d\n",order, getpid(), getppid());}

	else{		
		printf("[%d] pid %d created left child with pid %d\n",order, getpid(), getppid() );
		
		pid2 = fork(); 
		if(pid2 == 0){ 
			order = 2*order +1;
			printf("[%d] pid = %d ppid = %d\n",order, getpid(), getppid());
		}
		else{
			printf("[%d] pid %d created right child with pid %d\n", order, getpid(), getppid() );
			break;
		}			
	} 

	}	
	while(1){
		int status;
		pid = wait(&status);	
	 	
		if(pid == -1) exit(order);
		else{
			printf("[%d] child %d of %d exited with status %d\n", order, pid, getpid(), WEXITSTATUS(status));
		}	
	}
	
}


