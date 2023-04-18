/*
Pi value using Leibniz formula */


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

// declaring pi value as global variable 
double PIvalue=0;

struct piVar{
	int start;
	int end;
};

// thread funciton is declared to take void pointer as parameter
void *PIfun(void *arg){
	double calc=0;
	struct piVar* val = (struct piVar*) arg;
	int startPi = val->start;
	int endPi = val->end;
	int n;
	
	for(n=startPi;n<=endPi;n++){ 
		calc += (pow(-1,n)/((2*n)+1));
	}
	PIvalue = calc + PIvalue;
	pthread_exit(0);	
}


void main(){
	long long comp;
	int threadc;
	int remainder,i,m,n,o,p,q;
	
	printf("Enter the number of iteration: ");
	scanf("%lld",&comp);
	
	printf("Enter the number of threads to be used :");
	scanf("%d",&threadc);
	
	//Allocating sliceList dynamically to the number of threads input
	int *sliceList = malloc(threadc*sizeof(int));

	for(i=0;i<threadc;i++){
		sliceList[i] = comp / threadc;
	}
	
	remainder = comp % threadc;
	
	// equally distributing remainder
	for(m=0;m<remainder;m++){
		sliceList[m] = sliceList[m]+1;
	}
	
	int *startList = malloc(threadc*sizeof(int));
	int *endList= malloc(threadc*sizeof(int));
	
	// determine start and end values for each thread
	for(n=0;n<threadc;n++){
		if(n==0){
			startList[n]=0;
		}else{
			startList[n]= endList[n-1]+1;
		}
		endList[n]= startList[n]+sliceList[n]-1;
	}
	
	//assigning start and end to the declared structure
	struct piVar *mainStruct= malloc(threadc*sizeof(struct piVar));
	for(o=0;o<threadc;o++){
		mainStruct[o].start = startList[o];
		mainStruct[o].end = endList[o];
	}
	
	//creating threads 
	pthread_t *threads = malloc(threadc*sizeof(pthread_t));
	for(p=0;p<threadc;p++){
		pthread_create(&threads[p],NULL,PIfun,&mainStruct[p]);
	}
	
	//thread join
	for(q=0;q<threadc;q++){
		pthread_join(threads[q],NULL);
	}
	
	printf("\nThe estimated value of PI is: %lf",PIvalue*4);
	
}

