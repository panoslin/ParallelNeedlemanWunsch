#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Created by panos on 12/10/23
# IDE: PyCharm

"""
mpiexec -np 4 python pipeline.py
"""
from collections import defaultdict

import numpy as np
from mpi4py import MPI


def wait_recv_send():
    # while having message to receive
    while True:
        data = np.empty(3, dtype='i')
        comm.Recv(data, source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG)
        target_row, target_col, recv_val = data

        # end condition
        if target_row == -1:
            return recv_val

        # store intermediate results
        recv_msg[(target_row, target_col)].append(recv_val)

        # 3 messages received for a cell
        if len(recv_msg[(target_row, target_col)]) == 3:
            edit_distance = min(recv_msg[(target_row, target_col)]) + (s1[target_row - 1] != s2[target_col - 1])
            msg_sent = 0

            # insertion
            if target_row < n:
                msg_sent += 1
                comm.Isend(
                    [np.array([target_row + 1, target_col, edit_distance], dtype='i'), MPI.INT],
                    dest=(target_row + 1 - target_col) % cpu_count,
                )

            # deletion
            if target_col < m:
                msg_sent += 1
                comm.Isend(
                    [np.array([target_row, target_col + 1, edit_distance], dtype='i'), MPI.INT],
                    dest=(target_row - target_col - 1) % cpu_count,
                )

            # replacement
            if target_row < n and target_col < m:
                msg_sent += 1
                comm.Isend(
                    [np.array([target_row + 1, target_col + 1, edit_distance], dtype='i'), MPI.INT],
                    dest=(target_row - target_col) % cpu_count,
                )

            # release memory
            del recv_msg[(target_row, target_col)]

            # last cell does not send message to descendant cells
            if msg_sent == 0:
                for i in range(cpu_count):
                    # send -1 to end the loop
                    comm.Isend([np.array([-1, -1, edit_distance], dtype='i'), MPI.INT], dest=i)


if __name__ == '__main__':
    import time

    # init MPI communicator
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    cpu_count = comm.Get_size()

    start_time = time.time()

    if rank == 0:
        # import testcase
        from testcases import testcases

        s1, s2, expected = testcases[18]
        n, m = len(s1), len(s2)
        comm.bcast([s1, s2], root=0)

        # build the init dp table
        comm.Isend([np.array([1, 1, 0], dtype='i'), MPI.INT], dest=0)

        # send init msg from first row
        for col in range(1, m + 1):
            # send message to cells below
            comm.Isend([np.array([1, col, col], dtype='i'), MPI.INT], dest=(1 - col) % cpu_count)
            if col != m:
                # send message to cells below-right
                comm.Isend([np.array([1, col + 1, col], dtype='i'), MPI.INT], dest=(-col) % cpu_count)

        # send init msg from first column
        for row in range(1, n + 1):
            # send message to cells right
            comm.Isend([np.array([row, 1, row], dtype='i'), MPI.INT], dest=(row - 1) % cpu_count)
            if row != n:
                # send message to cells below-right
                comm.Isend([np.array([row + 1, 1, row], dtype='i'), MPI.INT], dest=row % cpu_count)
    else:
        s1, s2 = comm.bcast(None, root=0)
        n, m = len(s1), len(s2)

    # (row, col): msg - msg recv for cell (row, col)
    recv_msg = defaultdict(list)
    # filling the dp table
    answer = wait_recv_send()
    if rank == 0:
        print(
            f'\nFinish with result {answer}\n'
            f'time taken to process {m=}x{n=} '
            f'with {cpu_count} processor: '
            f'{time.time() - start_time}\n'
            f'*****************************************************************************************************'
        )
        assert expected == answer
