#include "mpi.h"
#include<stdio.h>
#include<math.h>

void BGU_Reduce(void *send_data, void *
recv_data, int count,MPI_Datatype datatype,MPI_Op op, int root,MPI_Comm communicator)
{
	//Here in this assignment I will only do the sum op so I am going to ignore MPI_Op variable otherwise this excercise will be too long	
 
	int rank,size;							//Here I am decairing the rank and size again although it has been declaired in the main function 
									//because I dont want to use the same variables because maybe the user did something wrong and I dont want it to affect my work 
	MPI_Comm_rank(communicator, &rank);				//getting the rank
	MPI_Comm_size(communicator, &size);				//getting the size
	MPI_Status status;	
	*(float*)recv_data = 0;
	//the sending part where all other processes sends to the root
	if (rank != root){
	//Sending from all the ranks (processes except the root)
	MPI_Send(send_data, count, datatype, root, 0, communicator); 

	} else {
		//receiving data from the all senders in case that this process is a root process
		for (int i =0; i<size; i++){
			if (i!=root){
				MPI_Recv(send_data, count, datatype, i, 0, communicator, &status);
				}
			*(double*)recv_data += *(double*)send_data;	//Here I am adding the values together
			}
	}

}

void BGU_Bcast(void* data, int count,MPI_Datatype datatype, int root,MPI_Comm communicator)
{
	int rank,size;
	MPI_Comm_rank(communicator, &rank);				//getting the rank
	MPI_Comm_size(communicator, &size);				//getting the size
	MPI_Status status;	

	//the sender part where you sender sends the data
	if (rank == root)
	{
	for (int i = 0; i<size; i++)					//Sending to all the ranks (proccesses except the current one)
		if (i != rank)
			 MPI_Send(data, count, datatype, i, 0, communicator); 
	
	
	} else {
		//receiving data from the sender in case that this process is a receiver process
		MPI_Recv(data, count, datatype, root, 0, communicator, &status);	
	}

}


 double f(double);
 double f(double a)
 {
     return (4.0 / (1.0 + a*a));
 }
 int main(int argc,char *argv[])
 {
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    fprintf(stdout,"Process %d of %d on %s\n",
            myid, numprocs, processor_name);
    n = 0;
    while (!done)
    {
        if (myid ==  0)
        {
 /*
            printf("Enter the number of intervals: (0 quits) ");
            scanf("%d",&n);
 */
            if (n == 0) n=10000; else n=0;
            startwtime = MPI_Wtime();
        }
        BGU_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
            h   = 1.0 / (double) n;
            sum = 0.0;
            /* A slightly better approach starts from large i and works back */
            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += f(x);
            }
            mypi = h * sum;
            BGU_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            if (myid == 0)
            {
                printf("pi is approximately %.16f, Error is %.16f\n",
                       pi, fabs(pi - PI25DT));
                endwtime = MPI_Wtime();
                printf("wall clock time = %f\n", endwtime-startwtime);
                fflush( stdout );
            }
        }
     }
     MPI_Finalize();
     return 0;
 }
