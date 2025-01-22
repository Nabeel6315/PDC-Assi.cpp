#include <mpi.h>
#include <iostream>
#include <cstdio>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    int size;     // Total number of processes
    int myid;     // Rank of the current process
    int tag = 0;  // Tag for communication
    MPI_Status status; // Status object for MPI communication

    char message_send[50]; // Message to send
    char message_recv[50]; // Message to receive

    // Get the total number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Get the rank (ID) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    if (myid != 0) {
        // Not the designated process (process 0), send data to process 0
        sprintf(message_send, "Hello from process id: %d", myid);
        MPI_Send(message_send, 50, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
    } else {
        // Only for process 0: receive messages from all other processes
        for (int i = 1; i < size; ++i) {
            MPI_Recv(message_recv, 50, MPI_CHAR, i, tag, MPI_COMM_WORLD, &status);
            printf("Process 0 received: %s\n", message_recv);
        }

        // Process 0 sends an acknowledgment message
        sprintf(message_send, "Hello from process id: %d", myid);
        printf("Process 0: %s\n", message_send);
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}
