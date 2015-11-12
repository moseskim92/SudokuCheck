
#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 9
#define NUM_THREADSA 27	
/* this data is shared by the thread(s) */
int a[9][9]={
		{6,2,9,/**/3,5,4,/**/8,1,7},
		{4,1,5,/**/9,8,7,/**/3,6,2},
		{8,3,7,/**/6,1,2,/**/5,9,4},
		{1,5,6,/**/1,2,9,/**/7,4,3},
		{2,7,4,/**/1,3,5,/**/9,8,6},
		{9,8,3,/**/4,7,6,/**/1,2,5},
		{3,6,1,/**/5,4,8,/**/2,7,9},
		{7,4,8,/**/2,9,3,/**/6,5,1},
		{5,9,2,/**/7,6,1,/**/4,3,8}
	};
int b[3][3]={{1,2,3},{4,5,6},{7,8,9}};

int i, u, p, err=0;
void *runner(); /* the thread */
void *runner1();
void *runner2();
int main()
{
pthread_attr_t attr[NUM_THREADS];//, attr1[NUM_THREADS], attr2[NUM_THREADS]; /* set of attributes for the thread */
pthread_t workers[NUM_THREADS];//, workers1[NUM_THREADS], workers2[NUM_THREADS]; //thread identifier
int count=0;

int i,j=0;
/* get the default attributes */
	for (i=0; i<NUM_THREADS; i++)
	{
		pthread_attr_init(&attr[i]);
		pthread_create(&workers[i],&attr[i],runner,(void *)count);
		pthread_create(&workers[i],&attr[i],runner1,(void *)count);
		pthread_create(&workers[i],&attr[i],runner2,(void *)count);
		count++;
	}

/* now wait for the thread to exit */
	for (i=0; i<NUM_THREADS; i++)
	{
		pthread_join(workers[i], NULL);
		//pthread_join(workers1[i], NULL);
		//pthread_join(workers2[i], NULL);
	}		

	//Correct or incorrect
	if (err>0)
		printf("\nThis Sudoku puzzle is incorrect\n");
	else
		printf("\nThis Sudoku puzzle is correct\n");	
}


//row check
void *runner(void *param) 
{	
	int count = (int) param;
	int row_check[9];
	//printf("\n row count is %d \n", count);
	//put row into array
	for (i=0; i<9; i++)
	{
		row_check[i]=a[count][i];
	}
	//print row array, check if printed row is correct
	/*
	for(i=0;i<9;i++)
		printf(" %d ", row_check[i]);
	*/
	int j,k;
	//sory array
	for(j=1;j<9;j++)
	{
		int tmp=row_check[j];
		for(k=j;k>=1 && tmp<row_check[k-1];k--)
			row_check[k]=row_check[k-1];
		row_check[k]=tmp;
	}
	//Check if row is correct/incorrect
	for(i=0;i<9;i++)
	{
		if (row_check[i]==(i+1))
			continue;
		else
		{
			printf("\nrow %d is incorrect\n",count);
			err++;
			break;
		}
	}
	
	pthread_exit(0);
}

//Column check
void *runner1(void *param) 
{	
	int count = (int) param;
	int column_check[9];
	//printf("\n column count is %d \n", count);
	//put column into array
	for (i=0; i<9; i++)
	{
		column_check[i]=a[i][count];
	}
	//print column array, check if correct column is printed
	/*for(i=0;i<9;i++)
		printf(" %d ", column_check[i]);
	*/	
	int j,k;
	//Sort	
	for(j=1;j<9;j++)
	{
		int tmp=column_check[j];
		for(k=j;k>=1 && tmp<column_check[k-1];k--)
			column_check[k]=column_check[k-1];
		column_check[k]=tmp;
	}
	//Check if correct/incorrect
	for(i=0;i<9;i++)
	{
		if (column_check[i]==(i+1))
			continue;
		else
		{
			printf("\ncolumn %d is incorrect\n",count);
			err++;
			break;
		}
	}
	
	pthread_exit(0);
}

//Box check
void *runner2(void *param) 
{	
	int count = (int) param;
	int box_check[9];
	//printf("\n box count is %d \n", count);
	//Create array for box
	for (i=0; i<9; i++)
	{
		u=i%3;
		p=i/3;
		box_check[i]=a[p+(count/3)*3][u+(count%3)*3];
	}

	//Print box array, check if correct box is printed
	/*
	for(i=0;i<9;i++)
		printf(" %d ", box_check[i]);
	*/	
	int j,k;
	//Sort
	for(j=1;j<9;j++)
	{
		int tmp=box_check[j];
		for(k=j;k>=1 && tmp<box_check[k-1];k--)
			box_check[k]=box_check[k-1];
		box_check[k]=tmp;
	}
	
	//Check if correct or incorrect
	for(i=0;i<9;i++)
	{
		if (box_check[i]==(i+1))
			continue;
		else
		{
			printf("\nbox %d is incorrect\n",count);
			err++;
			break;
		}
	}
	
	pthread_exit(0);
}
