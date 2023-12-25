//
// Created by Panos on 12/24/23.
//
#include <vector>
#include <map>
#include <tuple>

// A helper function to get a reference to the vector and create it if it doesn't exist
std::vector<int> &get_or_create_vector(
        std::map<std::tuple<int, int>, std::vector<int>> &map,
        std::tuple<int, int> key
) {
    if (map.find(key) == map.end()) {
        map[key] = std::vector<int>();
    }
    return map[key];
}