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
extern std::vector<std::tuple<std::string, std::string, int>> testcases;

#endif