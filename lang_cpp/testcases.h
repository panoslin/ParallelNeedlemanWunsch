//
// Created by Panos on 12/21/23.
//
#ifndef TESTCASE_H   // If TESTCASE_H is not defined,
#define TESTCASE_H   // define TESTCASE_H, and then compile the following code.

#include <vector>
#include <tuple>
#include <string>

// Declare the variable as extern to let the linker know
// it will be defined elsewhere
std::vector<std::tuple<std::string, std::string, int>> testcases = {
        {"horse",                 "ros",                   3},
        {"intention",             "execution",             5},
        {"a",                     "a",                     0},
        {"a",                     "b",                     1},
        {"ab",                    "b",                     1},
        {"ab",                    "a",                     1},
        {"ab",                    "ab",                    0},
        {"ab",                    "ac",                    1},
        {"ab",                    "bc",                    2},
        {"ab",                    "cd",                    2},
        {std::string(4, 'a'),     std::string(4, 'b'),     4},
        {std::string(8, 'a'),     std::string(8, 'b'),     8},
        {std::string(16, 'a'),    std::string(16, 'b'),    16},
        {std::string(32, 'a'),    std::string(32, 'b'),    32},
        {std::string(64, 'a'),    std::string(64, 'b'),    64},
        {std::string(128, 'a'),   std::string(128, 'b'),   128},
        {std::string(256, 'a'),   std::string(256, 'b'),   256},
        {std::string(512, 'a'),   std::string(512, 'b'),   512},
        {std::string(1000, 'a'),  std::string(1000, 'b'),  1000},
        {std::string(10000, 'a'), std::string(1000, 'b'),  10000},
        {std::string(10000, 'a'), std::string(10000, 'b'), 10000},
};

#endif