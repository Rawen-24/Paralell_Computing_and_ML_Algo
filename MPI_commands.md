# MPI Commands Reference

This README provides a comprehensive overview of common MPI commands, functions, and usage examples for C, C++, and Fortran.

---

## 1. MPI Initialization and Finalization

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Init(int *argc, char ***argv)` | Initializes the MPI environment | Must be called before any other MPI function. Sets up communication infrastructure. |
| `MPI_Finalize()` | Terminates the MPI environment | Must be the last MPI call. Cleans up resources and shuts down MPI. |

---

## 2. Process Information

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Comm_size(MPI_Comm comm, int *size)` | Get total number of processes | `comm` is usually `MPI_COMM_WORLD`. Returns number of processes in the communicator. |
| `MPI_Comm_rank(MPI_Comm comm, int *rank)` | Get the rank of current process | `rank` is the unique ID of the process in `comm`. Ranks are 0 to size-1. |
| `MPI_Get_processor_name(char *name, int *resultlen)` | Get the processor name | Useful for debugging or understanding node distribution. |

---

## 3. Point-to-Point Communication

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)` | Send data to another process | Blocking send. `dest` is destination rank, `tag` identifies message type. |
| `MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)` | Receive data from another process | Blocking receive. Can use `MPI_ANY_SOURCE` or `MPI_ANY_TAG` for flexibility. |
| `MPI_Isend(...)` | Non-blocking send | Returns immediately. Use with `MPI_Wait` or `MPI_Test` to ensure completion. |
| `MPI_Irecv(...)` | Non-blocking receive | Returns immediately. Use with `MPI_Wait` or `MPI_Test`. |
| `MPI_Sendrecv(...)` | Send and receive simultaneously | Useful for exchanging data between two processes. |

---

## 4. Collective Communication

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)` | Broadcast data from root to all processes | All processes in `comm` receive the data from `root`. |
| `MPI_Reduce(void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)` | Reduce data across processes | Common operations: `MPI_SUM`, `MPI_MAX`, `MPI_MIN`. Result stored at root. |
| `MPI_Allreduce(...)` | Like `MPI_Reduce`, but result goes to all processes | Each process gets the reduced value. |
| `MPI_Gather(void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)` | Gather data from all processes to root | Root collects data in `recvbuf`. |
| `MPI_Scatter(...)` | Scatter data from root to all processes | Opposite of gather. Each process gets a piece. |
| `MPI_Allgather(...)` | Gather and distribute to all | Each process receives the gathered array from all processes. |
| `MPI_Barrier(MPI_Comm comm)` | Synchronize processes | Blocks until all processes in `comm` reach the barrier. |

---

## 5. Derived Data Types and Operations

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Type_contiguous`, `MPI_Type_vector`, `MPI_Type_struct` | Create custom MPI data types | Useful when sending non-contiguous memory or structs. Must commit with `MPI_Type_commit`. |
| `MPI_Op_create` | Create custom reduction operations | Defines new operations beyond `MPI_SUM`, etc. |

---

## 6. Error Handling

| Function | Purpose | Usage / How it works |
|----------|---------|--------------------|
| `MPI_Errhandler_set` | Set error handler for a communicator | Default is `MPI_ERRORS_ARE_FATAL`. |
| `MPI_Error_string(int errorcode, char *string, int *resultlen)` | Translate error codes to messages | Useful for debugging. |

---

## 7. MPI Runtime Commands (Terminal)

| Command | Purpose | Usage / How it works |
|---------|---------|--------------------|
| `mpicc` | Compile MPI C programs | Example: `mpicc program.c -o program` |
| `mpicxx` / `mpiCC` | Compile MPI C++ programs | Example: `mpicxx program.cpp -o program` |
| `mpifort` | Compile MPI Fortran programs | Example: `mpifort program.f90 -o program` |
| `mpirun -np <N> ./program` | Run MPI program with N processes | Can also specify hostfile or node distribution. |
| `mpiexec -np <N> ./program` | Same as mpirun | Platform-dependent, sometimes preferred on clusters. |

---

## 8. Useful Tips

- Always call **`MPI_Init` first** and **`MPI_Finalize` last**.  
- Use **`MPI_Barrier`** for debugging to synchronize outputs.  
- Non-blocking communication (`MPI_Isend`, `MPI_Irecv`) helps **overlap computation with communication**.  
- **Ranks** are crucial: rank 0 is typically used as the "master" process.  
- Collective functions are **optimized for performance**, prefer them over manual loops of `MPI_Send`/`MPI_Recv`.