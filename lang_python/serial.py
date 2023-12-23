#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Created by panos on 12/10/23
# IDE: PyCharm
class Solution:
    """
    An implementation of the Needleman-Wunsch algorithm
    """

    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        score_matrix = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(1, n + 1):
            score_matrix[i][0] = i

        for j in range(1, m + 1):
            score_matrix[0][j] = j

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if word1[i - 1] == word2[j - 1]:
                    # equal to case when both chars not presented
                    score_matrix[i][j] = score_matrix[i - 1][j - 1]
                else:
                    score_matrix[i][j] = 1 + min(
                        # insert
                        score_matrix[i - 1][j],
                        # delete
                        score_matrix[i][j - 1],
                        # replace
                        score_matrix[i - 1][j - 1],
                    )
        return score_matrix[-1][-1]


if __name__ == '__main__':
    from testcases import testcases
    import time

    for s1, s2, ans in testcases:
        start_time = time.time()
        _ = Solution().minDistance(s1, s2)
        print(_)
        try:
            assert _ == ans
        except AssertionError:
            print(s1, s2)
            raise AssertionError(f"The answer for {s1=} and {s2=} is {ans=}, but got {_=} instead")

        print(
            f'\nFinish with result {_}\n'
            f'time taken to process m={len(s1)}xn={len(s2)} '
            f'{time.time() - start_time}\n'
            f'*****************************************************************************************************'
        )
