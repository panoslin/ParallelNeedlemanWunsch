//
// Created by Panos on 12/24/23.
//

#ifndef LANG_CPP_HELPER_H
#define LANG_CPP_HELPER_H

#include <vector>
#include <map>
#include <tuple>
#include <functional>

// Forward declaration of the hash function struct
struct hash_tuple {
    size_t operator()(const std::tuple<int, int>& key) const noexcept;
};


//extern std::vector<int> &get_or_create_vector(
//        std::map<std::tuple<int, int>, std::vector<int>> &map,
//        std::tuple<int, int> key
//);

#endif //LANG_CPP_HELPER_H
