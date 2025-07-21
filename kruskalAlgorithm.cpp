#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
    vector<int>parent, rank;
    public:
    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1,1);
        
        for(int node = 0; node <= n; node++) {
            parent[node] = node;
        }
    }

    int findParent(int node) {
        if(node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    void uniteNodes(int node1, int node2) {
        int parent_of_node1 = findParent(node1);
        int parent_of_node2 = findParent(node2);
        if(parent_of_node1 == parent_of_node2) return;
        if(rank[parent_of_node1] > rank[parent_of_node2]) {
            parent[node2] = parent_of_node1;
        }
        else if(rank[parent_of_node2] > rank[parent_of_node1]) {
            parent[node1] = parent_of_node2;
        }
        else {
            parent[parent_of_node2] = parent_of_node1;
            rank[parent_of_node1]++;
        }

    }
};

int kruskalAlgorithm(int n, vector<vector<int>>&graph) {
    //graph : {weight, u, v} where u-v

    sort(graph.begin(),graph.end());
    DSU dsu(n);
    int mstWeight = 0;
    
    for(auto &edge : graph) {
        int wt = edge[0];
        int u = edge[1], v = edge[2];
        if(dsu.findParent(u) != dsu.findParent(v)) {
            dsu.uniteNodes(u, v);
            mstWeight += wt;
            cout << "Edge added: " << u << " - " << v << " with weight " << wt << endl;
        }
    }
    return mstWeight;
}

int main() {
    int no_of_nodes = 5;
    vector<vector<int>>graph = {
        {1,0,1},
        {3,0,2},
        {4,1,2},
        {2,1,3},
        {5,2,3},
        {7,3,4}
    };

    int totalMSTWeight = kruskalAlgorithm(no_of_nodes, graph);

    cout << "Total weight of MST: " << totalMSTWeight << endl;
    
    return 0;
}

