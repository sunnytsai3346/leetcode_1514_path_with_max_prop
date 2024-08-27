#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    double maxProbability(int n, std::vector<std::vector<int>>& edges, std::vector<double>& succProb, int start_node, int end_node) {
        std::vector<std::vector<std::pair<int, double>>> graph(n); //adjacency list
        
        // Construct the graph
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i][0], v = edges[i][1];
            double prob = succProb[i];
            graph[u].push_back({v, prob});
            graph[v].push_back({u, prob}); // Since the graph is undirected
        }
        
        // Priority queue for Dijkstra-like traversal (max-heap)
        std::priority_queue<std::pair<double, int>> pq;
        pq.push({1.0, start_node});
        std::vector<double> maxProb(n, 0.0);
        maxProb[start_node] = 1.0;
        
        // Dijkstra's algorithm with probability maximization
        while (!pq.empty()) {
            double prob = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            if (node == end_node) {
                return prob;
            }
            
            for (const auto& neighbor : graph[node]) {
                int next = neighbor.first;
                double nextProb = neighbor.second;
                if (maxProb[next] < prob * nextProb) {
                    maxProb[next] = prob * nextProb;
                    pq.push({maxProb[next], next});
                }
            }
        }
        
        return 0.0;
    }
};

int main() {
    Solution s;
    int numvertex = 3;
    std::vector<std::vector<int>> edges = {{0, 1}, {1, 2}, {0, 2}};
    std::vector<double> succProb = {0.5, 0.5, 0.2};
    int start_node = 0;
    int end_node = 2;
    
    double result = s.maxProbability(numvertex, edges, succProb, start_node, end_node);
    std::cout << result << std::endl;
    
    return 0;
}
