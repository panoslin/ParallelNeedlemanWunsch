#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Created by panos on 12/10/23
# IDE: PyCharm
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        n, m = len(word1), len(word2)
        dp = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(1, n + 1):
            dp[i][0] = i

        for j in range(1, m + 1):
            dp[0][j] = j

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if word1[i - 1] == word2[j - 1]:
                    # equal to case when both chars not presented
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    dp[i][j] = 1 + min(
                        # insert
                        dp[i - 1][j],
                        # delete
                        dp[i][j - 1],
                        # replace
                        dp[i - 1][j - 1],
                    )
        return dp[-1][-1]


if __name__ == '__main__':
    from testcases import testcases

    for s1, s2, ans in testcases:
        _ = Solution().minDistance(s1, s2)
        print(_)
        try:
            assert _ == ans
        except AssertionError:
            print(s1, s2)
            raise AssertionError(f"The answer for {s1=} and {s2=} is {ans=}, but got {_=} instead")
