#include <iostream>
#include <algorithm>
#include <utility>
#include <memory>
#include <vector>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

namespace fastest_path {
	
    // from source node to std::get<0>, distance is std::get<1>
    using to_node_distance = pair<int, int>;
    using node_vector = vector<to_node_distance>;

    int64_t dijkstra(std::vector<node_vector> &adjacent, int n) {
        int mod = 1e9 + 7;
        // priority queue for keep track of min distance 
        using node_to_min_dist = pair<int64_t, int64_t>;
        priority_queue<node_to_min_dist, vector<node_to_min_dist>, greater<node_to_min_dist>> pq;

        // store the distance and number of paths
        vector<int64_t> distance(n, std::numeric_limits<int64_t>::max());
        vector<int64_t> path(n, 0);

        // push the initial node and distance to reach start is 0
        pq.push({ 0, 0 });
        // mark the distance to 0
        distance[0] = 0;
        // mark the path number to 1
        path[0] = 1;

        // until queue is not empty
        while (!pq.empty()) {
            // get the top (min distance) element from priority queue and remove
            auto [min_dist, node] = pq.top();
            pq.pop();

            // iterate on its adjacent nodes
            for (auto& child : adjacent[node]) {
                auto [adj_node, weight] = child;

                // if it min distance to reach at a node then update it
                if (min_dist + weight < distance[adj_node]) {
                    distance[adj_node] = min_dist + weight;
                    path[adj_node] = path[node];
                    pq.push({ min_dist + weight, adj_node });
                }
                else if (min_dist + weight == distance[adj_node]) {
                    //if it already visited with the shortest dis then increse the path with the current node path
                    path[adj_node] = (path[node] + path[adj_node]) % mod;
                }
            }
        }

        return path[n - 1];
    }

    int countPaths(int n, vector<vector<int>>& roads) {
        // adjacency list
        std::vector<node_vector> adjacent(n);
        
        // create the graph
        for (auto& v : roads) {
            adjacent[v[0]].push_back({v[1], v[2]});
            adjacent[v[1]].push_back({v[0], v[2]});
        }

        return (int)dijkstra(adjacent, n);
    }

    void find_path(
        vector<node_vector>& adjacent, // IN: list of adjacent nodes
        vector<vector<int>> &paths,    // OUT: paths from source to dest node
        vector<int> &distances,        // OUT: distance from source to dest node, per path
        std::unordered_set<int> &visited, // visited nodes. Temporary for this function
        std::vector<int> &cur_path,    // current path. Temporary for this function
        int64_t &cur_distance,         // distance of current path. Temporary for this function
        int from, int to
    ) {
        visited.insert(from);

        node_vector& nodes = adjacent[from];
        for (to_node_distance& nd : nodes) {
            auto &[node, distance] = nd;

            // Running in circles?
            if (visited.find(node) != visited.end()) {
                continue;
            }

            cur_path.push_back(node);
            cur_distance += distance;
            if (node == to) {
                // found. Not going to its sub-nodes
                paths.push_back(cur_path);
                distances.push_back(cur_distance);
            }
            else {
                find_path(adjacent, paths, distances, visited, cur_path, cur_distance, node, to);
            }
            cur_distance -= distance;
            cur_path.pop_back();
        }
        visited.erase(from);
    }

    int countPaths2(int n, vector<vector<int>>& roads) {
        vector<node_vector> adjacent;
        adjacent.resize(n);
        for (const auto& road : roads) {
            auto node1 = road[0];
            auto node2 = road[1];
            auto distance = road[2];
            adjacent[node1].emplace_back(node2, distance);
            adjacent[node2].emplace_back(node1, distance);
        }

        vector<vector<int>> paths;
        vector<int> distances;
        std::unordered_set<int> visited;
        std::vector<int> cur_path;
        cur_path.push_back(0); // From
        int64_t distance = 0;
        find_path(adjacent, paths, distances, visited, cur_path, distance, 0, 6);

        std::cout << "Result" << std::endl;
        for (size_t i=0; i < paths.size(); ++i) {
            auto& path = paths[i];

            std::cout << "[" << distances[i] << "] ";

            int j = 0;
            for (auto v : path) {
                if (j > 0) {
                    std::cout << " -> ";
                }
                std::cout << v;
                ++j;
            }
            std::cout << std::endl;
        }
        return 1;
    }

	void run() {

        vector<vector<int>> roads = {
            {0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}
        };

        std::cout << countPaths2(7, roads) << std::endl;

	}

}