//
// Created by Panos on 12/21/23.
//
/*
72. Edit Distance
    Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

    You have the following three operations permitted on a word:

    Insert a character
    Delete a character
    Replace a character

    Example 1:

    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation:
    horse -> rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <csignal>
#include "testcases.h"

class Solution {
public:
    static int minDistance(std::string word1, std::string word2) {
        size_t m = word1.length();//first word length
        size_t n = word2.length();//second word length
        // dp[i][j] := min # of operations to convert word1[0..i) to word2[0..j)
        std::vector<std::vector<int> > dp(m + 1, std::vector<int>(n + 1));

        for (int i = 1; i <= m; ++i)
            dp[i][0] = i;

        for (int j = 1; j <= n; ++j)
            dp[0][j] = j;

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (word1[i - 1] == word2[j - 1])//same characters
                    dp[i][j] = dp[i - 1][j - 1];//no operation
                else
                    dp[i][j] = 1 + std::min(
                            {
                                    dp[i - 1][j - 1],
                                    dp[i - 1][j],
                                    dp[i][j - 1]
                            }
                    );

        return dp[m][n];
    }
};

int main() {
    // iterate through the testcases from testcases.h
    for (const auto &[word1, word2, expected]: testcases) {
        // current timestamp
        clock_t start = clock();
        int result = Solution::minDistance(word1, word2);
        clock_t end = clock();
        if (result != expected) {
            std::cout << "Wrong Answer" << std::endl;
            raise(SIGABRT);
        }
        double elapsed_time = static_cast<double> (end - start) / CLOCKS_PER_SEC;
        std::cout << "time cost for "
                  << word1.length() * word2.length()
                  << " : " << elapsed_time * 1000 << " ms"
                  << std::endl;

    }

    return 0;
}