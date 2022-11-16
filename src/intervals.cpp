// https://leetcode.com/problems/merge-intervals/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

namespace intervals_ns {

    bool between(const vector<int>& interval, int val) {
        return val >= interval[0] && val <= interval[1];
    }

    bool connected(const vector<int>& i1, const vector<int>& i2) {
        return between(i1, i2[0]) || between(i1, i2[1]);
    }

    void merge_intervals(vector<int>& dest, const vector<int>& src) {
        int l = std::min(dest[0], src[0]);
        int h = std::max(dest[1], src[1]);
        dest[0] = l;
        dest[1] = h;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty() || intervals.size() == 1) {
            return intervals;
        }
        
        std::sort(begin(intervals), end(intervals));
        
        vector<vector<int>> result;
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i) {
            size_t last = result.size() - 1;
            if (connected(result[last], intervals[i])) {
                merge_intervals(result[last], intervals[i]);
            }
            else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }

    void print(const vector<vector<int>> &vs) {
        for (auto& v : vs) {
            std::cout << "( ";
            for (auto& i : v) {
                std::cout << i << " ";
            }
            std::cout << ") ";
        }
        std::cout << std::endl;
    }

    void run() {
        vector<vector<int>> intervals;
        
        //intervals = { {1, 3}, {2, 6}, {8, 10}, {15, 18} };
        //print(merge(intervals));

        intervals = { {0,0},{1,2},{5,5},{2,4},{3,3},{5,6},{5,6},{4,6},{0,0},{1,2},{0,2},{4,5} };
        // [[0, 6]] - Mine: ( 0 6 ) ( 5 6 )
        print(merge(intervals));

    }

}