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
#include <tuple>


// Create a 2-D vector with n rows and m columns, initializing all values to 0
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        const int m = word1.length();//first word length
        const int n = word2.length();//second word length
        // dp[i][j] := min # of operations to convert word1[0..i) to word2[0..j)
        vector<vector<int> > dp(m + 1, vector<int>(n + 1));

        for (int i = 1; i <= m; ++i)
            dp[i][0] = i;

        for (int j = 1; j <= n; ++j)
            dp[0][j] = j;

        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (word1[i - 1] == word2[j - 1])//same characters
                    dp[i][j] = dp[i - 1][j - 1];//no operation
                else
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;

        //replace       //delete        //insert
        return dp[m][n];
    }
};

int main() {
    Solution solution = Solution();

    vector<tuple<string, string, int> > testcases = {
            {"horse",            "ros",              3},
            {"intention",        "execution",        5},
            {"a",                "a",                0},
            {"a",                "b",                1},
            {"ab",               "b",                1},
            {"ab",               "a",                1},
            {"ab",               "ab",               0},
            {"ab",               "ac",               1},
            {"ab",               "bc",               2},
            {"ab",               "cd",               2},
            {string(4, 'a'),     string(4, 'b'),     4},
            {string(8, 'a'),     string(8, 'b'),     8},
            {string(16, 'a'),    string(16, 'b'),    16},
            {string(32, 'a'),    string(32, 'b'),    32},
            {string(64, 'a'),    string(64, 'b'),    64},
            {string(128, 'a'),   string(128, 'b'),   128},
            {string(256, 'a'),   string(256, 'b'),   256},
            {string(512, 'a'),   string(512, 'b'),   512},
            {string(1000, 'a'),  string(1000, 'b'),  1000},
            {string(10000, 'a'), string(1000, 'b'),  10000},
            {string(10000, 'a'), string(10000, 'b'), 10000},
            // The following case is omitted due to practical memory constraints
//            {string(100000000, 'a'), string(100000000, 'b'), 100000000},
    };
    for (const auto &[word1, word2, expected]: testcases) {
        // current timestamp
        clock_t start = clock();
        int result = solution.minDistance(word1, word2);
        clock_t end = clock();
        double elapsed_time = static_cast<double> (end - start) / CLOCKS_PER_SEC;
        cout << "time cost for " << word1.length() * word2.length() << " : " << elapsed_time * 1000 << " ms" << endl;

    }

    return 0;
}