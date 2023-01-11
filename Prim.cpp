#include "Prim.h"
#include <queue>
#include <limits.h>
#include <map>
#include <iostream>
#include <algorithm>



//The algorithm recieves a Mat graph and a weight function
struct CompareNode {
bool operator()(const node* a, const node* b) {
    return a->key > b->key;
}
};

Mat Prim::getMST(Mat& graph, WeightFunc func) {
    std::vector<node> nodes; //key, pi, i
    std::vector<node*> copy; //key, pi, i
    std::vector<node*> A; //edges in the MST

    std::map<node*, bool> doesExist; //A hashMap to check if a node is in the priority queue
    for (int i = 0; i < graph.size(); i++) {
        node n;
        n.key = INT_MAX;
        n.pi = nullptr;
        n.i = i;
        nodes.push_back(n);
    }
    //initializing the lightest edge to be key = 0
    nodes[0].key = 0;

    for (auto&& node : nodes) {
        copy.push_back(&node);
        doesExist[&node] = true;
    }
    
    while (!copy.empty()) {
        node* u = *std::min_element(copy.begin(), copy.end(), [](node* a, node* b) { return a->key < b->key; });
        copy.erase(std::find(copy.begin(), copy.end(), u));
        doesExist[u] = false;

        if (u->pi != nullptr) {
            A.push_back(u);
        }
        //for each neighbornode, updating its value key
        for (int j = 0; j < graph.size(); j++) {
            if (func(graph, u->i, j) != INT_MAX) { //if there is an edge
                if (nodes[j].key > func(graph, u->i, j) && doesExist[&nodes[j]] == true) {
                    nodes[j].key = func(graph, u->i, j);
                    nodes[j].pi = u;
                }
            }
        }
    }

    //convert A to matrix
    Mat mst;
    for (size_t i = 0; i < graph.size(); i++)
        mst.push_back(std::vector<int>(graph.size(), INT_MAX));

    for (int k = 0; k < A.size(); k++) {
        int i = A[k]->pi->i;
        int j = A[k]->i;
        mst[i][j] = A[k]->key;
        mst[j][i] = A[k]->key;
    }

    return mst;
}

//This function adds an edge to the graph
void Prim::addEdge(Mat& graph, int i, int j, int weight) {
    //finding a cycle in the graph and saving the nodes
    graph[i][j] = weight;
    graph[j][i] = weight;
    std::vector<int> cycle = Prim::getCycle(graph, i);

    //checking if the edge is the heaviest in the cycle
    int max = graph[cycle[0]][cycle[1]];
    int maxIndex = 0;
    //finding the heaviest edge in the cycle
    for (size_t i = 1; i < cycle.size() - 1; i++) {
        if (graph[cycle[i]][cycle[i + 1]] > max) {
            max = graph[cycle[i]][cycle[i + 1]];
            maxIndex = i;
        }
    }

    //remove the heaviest edge in the cycle
    if (max > weight)
        graph[cycle[maxIndex]][cycle[maxIndex + 1]] = INT_MAX;
    else {
        //restore the graph
        graph[i][j] = INT_MAX;
        graph[j][i] = INT_MAX;
    }
}

bool Prim::getCycle(Mat& graph, int start, int current, std::vector<int>& nodes, std::map<int, bool>& visited, int depth) {
    if (start == current && depth != 0) {
        return true;
    }
    visited[current] = true;
    for (size_t i = 0; i < graph.size(); i++) {
        if (graph[current][i] != INT_MAX && (visited.find(i) == visited.end() || i == start)) {
            if (getCycle(graph, start, i, nodes, visited, depth + 1)) {
                nodes.push_back(current);
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Prim::getCycle(Mat& graph, int start) {
    std::vector<int> res;
    std::map<int, bool> visited;
    Prim::getCycle(graph, start, start, res, visited, 0);
    return res;
}