// https://leetcode.com/problems/search-in-rotated-sorted-array

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <optional>

#include "utils/test_utils.h"

namespace rotated_bin_search {

    // Regular binary search algorithm
    template<typename Vector>
    std::optional<size_t> bin_search(const Vector& nums, size_t low, size_t high, typename Vector::value_type n) {
        while (low <= high) {
            size_t middle = low + ((high - low) / 2);
            int found = nums[middle];
            if (found == n) {
                return middle;
            }

            if (n < found) {
                if (middle == std::numeric_limits<size_t>::min()) { // avoid overflow rotation
                    return std::nullopt;
                }

                high = middle - 1;
            }
            else {
                // n > found
                if (middle == std::numeric_limits<size_t>::max()) { // avoid overflow rotation
                    return std::nullopt;
                }
                low = middle + 1;
            }
        }
        return std::nullopt;
    }
    
    template<typename Vector>
    std::optional<size_t> search(const Vector& nums, typename Vector::value_type target) {
        if (nums.empty()) {
            return std::nullopt;
        }

        return bin_search(nums, 0, nums.size() - 1, target);
    }
    // End of regular binary search algorithm

    template<typename Type>
    struct rotated_vector {
        using value_type = Type;
        const std::vector<value_type>& _internal_vec;
        size_t rotation;

        size_t find_start(const std::vector<int>& nums) const {
            for (size_t i = 1; i < nums.size(); ++i) {
                if (nums[i - 1] > nums[i]) {
                    return i;
                }
            }
            return 0;
        }

        rotated_vector(const std::vector<value_type>& vec) : _internal_vec(vec) {
            rotation = find_start(vec);
        }

        size_t real_pos(size_t virt_pos) const {
            size_t pos = virt_pos + rotation;
            if (pos >= _internal_vec.size()) {
                pos -= _internal_vec.size();
            }
            return pos;
        }

        value_type operator[](size_t virt_pos) const {
            size_t pos = real_pos(virt_pos);
            return _internal_vec[pos];
        }

        size_t size() const {
            return _internal_vec.size();
        }

        bool empty() const {
            return _internal_vec.empty();
        }
    };

    std::optional<size_t> search_rotated(std::vector<int> &v, int target) {
        rotated_vector<int> rv(v);
        auto ret = search(rv, target);
        if (ret) {
            return rv.real_pos(ret.value());
        }
        return std::nullopt;
    }

    void run() {
        std::vector<int> v1 = { 0, 1, 2, 3, 4, 5 };    // even number of items
        std::vector<int> v2 = { 0, 1, 2, 3, 4, 5, 6 };  // odd number of items

        auto mult_vec = [](std::vector<int>& nums, int how_much) {
            std::transform(std::begin(nums), std::end(nums), std::begin(nums), [&how_much](int v) { return v * how_much; });
        };

        for (int i = 0; i < 6; ++i) {
            std::rotate(v1.begin(), v1.begin() + 1, v1.end());
            // As I am rotating for each iteration, the result is always the same
            ENSURE_EQUAL(search_rotated(v1, i), 5);
        }

        for (int i = 0; i < 7; ++i) {
            std::rotate(v2.begin(), v2.begin() + 1, v2.end());
            ENSURE_EQUAL(search_rotated(v2, i), 6);
        }

        mult_vec(v1, 2);
        mult_vec(v2, 2);

        size_t initial_pos = 5;
        for (int i = 0; i < 12; i += 2) {
            std::rotate(v1.begin(), v1.begin() + 1, v1.end());
            ENSURE_EQUAL(search_rotated(v1, i), initial_pos);
            std::rotate(v1.begin(), v1.begin() + 1, v1.end());
            ENSURE_EQUAL(search_rotated(v1, i-1), std::nullopt);

            --initial_pos;
        }

        initial_pos = 6;
        for (int i = 0; i < 14; i += 2) {
            std::rotate(v2.begin(), v2.begin() + 1, v2.end());
            ENSURE_EQUAL(search_rotated(v2, i), initial_pos);
            std::rotate(v2.begin(), v2.begin() + 1, v2.end());
            ENSURE_EQUAL(search_rotated(v2, i - 1), std::nullopt);

            --initial_pos;
        }
    }
}