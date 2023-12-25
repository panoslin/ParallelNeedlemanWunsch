#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <tuple>
#include <csignal>
#include "helper.h"
#include "testcases.h"


int wait_recv_send(std::string s1, std::string s2, int cpu_count) {
    size_t n = s1.length(), m = s2.length();
    MPI_Request request;
    int DEFAULT_TAG = 0;
    std::map<std::tuple<int, int>, std::vector<int>> recv_msg;

    while (true) {
        int data[3];
        MPI_Recv(data, 3, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int target_row = data[0], target_col = data[1], recv_val = data[2];

        // end condition
        if (target_row == -1 && target_col == -1) {
            return recv_val;
        }

        // store intermediate results
        std::tuple<int, int> key = std::make_tuple(target_row, target_col);
        get_or_create_vector(recv_msg, key).push_back(recv_val);
        if (recv_msg[key].size() == 3) {
            auto edit_distance = std::min_element(recv_msg[key].begin(), recv_msg[key].end());
            int minValue = *edit_distance;
            if (s1[target_row - 1] != s2[target_col - 1]) {
                minValue++;
            }
            int msg_sent = 0;

            // insertion
            if (target_row < n) {
                msg_sent++;
                int array[3] = {target_row + 1, target_col, minValue};
                int dest = (((target_row + 1 - target_col) % cpu_count) + cpu_count) % cpu_count;
                MPI_Isend(array, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
            }

            // deletion
            if (target_col < m) {
                msg_sent++;
                int array[3] = {target_row, target_col + 1, minValue};
                int dest = (((target_row - 1 - target_col) % cpu_count) + cpu_count) % cpu_count;
                MPI_Isend(array, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
            }

            // replacement
            if (target_row < n && target_col < m) {
                msg_sent++;
                int array[3] = {target_row + 1, target_col + 1, minValue};
                int dest = (((target_row - target_col) % cpu_count) + cpu_count) % cpu_count;
                MPI_Isend(array, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
            }

            // release memory
            recv_msg[key].clear();

            // last cell does not send message to descendant cells
            if (msg_sent == 0) {
                int array[3] = {-1, -1, minValue};
                for (int i = 0; i < cpu_count; i++) {
                    MPI_Isend(array, 3, MPI_INT, i, DEFAULT_TAG, MPI_COMM_WORLD, &request);
                }
            }
        }
    }
}


int main(int argc, char *argv[]) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int cpu_count;
    MPI_Comm_size(MPI_COMM_WORLD, &cpu_count);

    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int DEFAULT_TAG = 0;
    int ROOT_RANK = 0;

    if (rank == 0) {
        for (auto &[s1, s2, expected]: testcases) {
            clock_t start_time = clock();
            size_t n = s1.length() + 1, m = s2.length() + 1;
            // broadcast the string s1 to all processes
            MPI_Bcast(&n, 1, MPI_INT, ROOT_RANK, MPI_COMM_WORLD);
            MPI_Bcast(&m, 1, MPI_INT, ROOT_RANK, MPI_COMM_WORLD);
            MPI_Bcast(&s1[0], n, MPI_CHAR, ROOT_RANK, MPI_COMM_WORLD);
            MPI_Bcast(&s2[0], m, MPI_CHAR, ROOT_RANK, MPI_COMM_WORLD);

            MPI_Request request;

            // MPI_Isend int array [1, 1, 0] to rank 0
            int arr[] = {1, 1, 0};
            MPI_Isend(arr, 3, MPI_INT, ROOT_RANK, DEFAULT_TAG, MPI_COMM_WORLD, &request);


            for (int col = 1; col < m; col++) {
                int array[] = {1, col, col};
                int dest = (((1 - col) % cpu_count) + cpu_count) % cpu_count;
                MPI_Isend(array, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
                if (col != m - 1) {
                    int array2[] = {1, col + 1, col};
                    dest = ((-col % cpu_count) + cpu_count) % cpu_count;
                    MPI_Isend(array2, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
                }
            }

            for (int row = 1; row < n; row++) {
                int array[] = {row, 1, row};
                int dest = (((row - 1) % cpu_count) + cpu_count) % cpu_count;
                MPI_Isend(array, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);
                if (row != n - 1) {
                    int array2[] = {row + 1, 1, row};
                    dest = row % cpu_count;
                    MPI_Isend(array2, 3, MPI_INT, dest, DEFAULT_TAG, MPI_COMM_WORLD, &request);

                }
            }


            int answer = wait_recv_send(s1, s2, cpu_count);
            if (answer != expected) {
                std::cout << "Wrong Answer" << std::endl;
                raise(SIGABRT);
            }
            std::cout << "Finish with result " << answer << std::endl
                      << "time taken to process m=" << m << " n=" << n << std::endl
                      << "with " << cpu_count << " processors" << std::endl
                      << (clock() - start_time) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl
                      << std::string(120, '*') << std::endl;
        }

    } else {
        for (int _ = 0; _ < testcases.size(); _++) {

            std::string s1, s2;
            size_t n = s1.length() + 1, m = s2.length() + 1;
            // recv the string s1 and s2 from process 0
            MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
            MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
            s1.resize(n - 1);
            s2.resize(m - 1);
            MPI_Bcast(&s1[0], n, MPI_CHAR, 0, MPI_COMM_WORLD);
            MPI_Bcast(&s2[0], m, MPI_CHAR, 0, MPI_COMM_WORLD);

            wait_recv_send(s1, s2, cpu_count);


        }


        // Finalize the MPI environment.
        MPI_Finalize();
    }