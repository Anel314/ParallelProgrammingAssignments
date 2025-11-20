# ParallelProgrammingAssignments

### Code Output:

<img width="1113" height="1444" alt="image" src="https://github.com/user-attachments/assets/742a6d52-cdd5-4067-9856-1b388681d7d9" />


### Explanation
The code itself sums up an array of 10000 elements using parallel code.
```C
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &nprocs);

```
It uses MPI to determine the number of processes (`nprocs`) and their respective ranks (`rank`).


```C
 int nSize;    
    int bSize = ncells / nprocs; 
    int remainder = ncells % nprocs;
    if (rank < remainder) {
        nSize =  bSize + 1;
    }else {
        nSize =  bSize;
    }

  int start_index;
    if (rank < remainder) {
        start_index = rank * ( bSize + 1);
    } else {
        start_index =  remainder * ( bSize + 1) + (rank - remainder) *  bSize;
    }

    int end_index = start_index + nSize - 1;
```
Rank 0 Divides the array into pieces for each process, and calculates the start and end index.

Then the main proccess creates the global array.

```C
    MPI_Allgather(&nSize, 1, MPI_INT, nsizes, 1, MPI_INT, comm);
```
MPI_Allgather: A collective communication routine where every process sends its piece size (nsize) to 
all other processes, and all processes receive the full array of sizes (nsizes). This is needed for the MPI_Scatterv setup.

Standard C signature:
```C
int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, 
                  void *recvbuf, int recvcount, MPI_Datatype recvtype, 
                  MPI_Comm comm)
```
`*senbuf` -> this is the start address of the data to be sent by the calling process.

`sendcount` -> The number of elements

`sendtype` -> The datatype

`recvbuf` -> The start address of the buffer to receive the data from all processes.

`recvcount` -> The number of elements received by each process

`recvtype` -> The datatype of the elements in the receive buffer


```C
 double *a_local = (double *)malloc(nSize * sizeof(double));
```
Here the code allocates a loval array for each process.


```C
    MPI_Scatterv(a_global, nsizes, offsets, MPI_DOUBLE,
                 a_local, nSize, MPI_DOUBLE, 0, comm);
```

MPI_Scatterv is a collective communication routine used to distribute data from the main process,
to the other working processes.
Each process gets a different sized piece.


Standard C signature:
```C
int MPI_Scatterv(const void *sendbuf, const int *sendcounts, const int *displs, 
                 MPI_Datatype sendtype, void *recvbuf, int recvcount, 
                 MPI_Datatype recvtype, int root, MPI_Comm comm)
```


`sendbuf` -> The starting address of the array on the root process containing all the data to be sent.

`sendcounts` -> An array of integers where the i-th element specifies the number of elements to send to process i.

`displs` -> An array of integers where the i-th element specifies the byte offset (or element index) in sendbuf from which the data for process i starts.

`sendtype` -> The data type of the elements in the send buffer (e.g., double).

`root` -> The rank of the process acting as the sender of the data (the source).

`comm` -> The communicator (the group of processes) involved in the collective operation.


```C

    double local_sum = 0.0;
    for (int i = 0; i < nSize; i++) {
        local_sum += a_local[i];
    }
```


After `MPI_Scatterv` distributed the data to each process, they all perform a local_sum on `a_local`. 


After this the last step is to use a reduce collective communication call to get the total sum of all local sums.
```C
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

```

MPI_Reduce is another collective communication routine, this one reduces each local_sum to a single value that is stored in the root proccess in the `total_sum` variable.


Standard C signature:
```C
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, 
               MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)
```

`sendbuf` -> The starting address of the data buffer on the calling process to be contributed to the reduction.

`recvbuf` -> The starting address of the buffer where the final, reduced result will be stored.

`count` -> The number of elements in the send and receive buffers.

`datatype` -> The data type of the elements being sent and received.

`op` -> The reduction operation to be applied (e.g., sum, max, min).

`root` -> The rank of the process where the final result will be stored.

`comm` -> The communicator (the group of processes) involved in the collective operation.


```C
    MPI_Finalize();

```
And finally `MPI_Finalize()` is called which terminates the MPI execution environment.





