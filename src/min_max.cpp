// https://www.hackerrank.com/challenges/angry-children/problem?isFullScreen=true&h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=greedy-algorithms

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace min_max {

    /*
     * Complete the 'maxMin' function below.
     *
     * The function is expected to return an INTEGER.
     * The function accepts following parameters:
     *  1. INTEGER k
     *  2. INTEGER_ARRAY arr
     */

    int maxMin(int k, vector<int> arr) {
        //arr.size() is always >= 2
        sort(begin(arr), end(arr));

        int result = std::numeric_limits<int>::max();

        size_t left = 0;
        size_t right = k - 1; // Count to index

        for (; right < arr.size(); ++left, ++right) {
            int diff = arr[right] - arr[left];
            if (diff < result) {
                result = diff;
            }
        }

        return result;
    }

    void run()
    {
        std::vector<int> v = {
            10,
            100,
            300,
            200,
            1000,
            20,
            30
        };
        std::cout << maxMin(3, v) << std::endl;

        v = { 1, 2, 1, 2, 1 };
        std::cout << maxMin(2, v) << std::endl;
    }

}
