//
// Created by Panos on 12/24/23.
//
#include <vector>
#include <map>
#include <tuple>
#include "helper.h"

// Now define the operator() of the hash_tuple struct
size_t hash_tuple::operator()(const std::tuple<int, int>& key) const noexcept {
    auto [x, y] = key;
    size_t res = 17;
    res = res * 31 + std::hash<int>()(x);
    res = res * 31 + std::hash<int>()(y);
    return res;
}

//// A helper function to get a reference to the vector and create it if it doesn't exist
//std::vector<int> &get_or_create_vector(
//        std::map<std::tuple<int, int>, std::vector<int>> &map,
//        std::tuple<int, int> key
//) {
//    if (map.find(key) == map.end()) {
//        map[key] = std::vector<int>();
//    }
//    return map[key];
//}
