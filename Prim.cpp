#include "Prim.h"
#include <queue>
#include <limits.h>
#include <map>
#include <iostream>

//The algorithm recieves a Mat graph and a weight function
Mat Prim::getMST(Mat& graph, WeightFunc func) {
    std::vector<node> nodes; //key, pi, i
    std::priority_queue<node*> pq; // weight, from, to
    std::vector<node*> A; //edges in the MST

    std::map<node*,bool> doesExist; //A hashMap to check if a node is in the priority queue
    for(int i = 0; i < graph.size(); i++){
        node n;
        n.key = INT_MAX;
        n.pi = nullptr;
        n.i = i;
        nodes.push_back(n);
    }
    nodes[0].key = 0;

    for (auto &&node : nodes){
        pq.push(&node); //pushing the node to the priority queue
        doesExist[&node] = true;
    }
    

    while(!pq.empty()){
        node* u = pq.top();
        pq.pop();
        doesExist[u] = false;

        if(u->pi != nullptr){
            A.push_back(u);
        }
        for(int j = 0; j < graph.size(); j++){
            if(func(graph, u->i, j) != INT_MAX){ //if there is an edge
                if(nodes[j].key > func(graph, u->i, j) && doesExist[&nodes[j]]){
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
    
    for(int k = 0; k < A.size(); k++) {
        int i = A[k]->pi->i;
        int j = A[k]->i;
        mst[i][j] = A[k]->key;
        mst[j][i] = A[k]->key;
    }

    return mst;
}

//This function adds an edge to the graph
void Prim::addEdge(Mat& graph, int i, int j, int weight){
    //finding a cycle in the graph and saving the nodes
    graph[i][j] = weight;
    std::vector<int> cycle = Prim::getCycle(graph, i);

    //checking if the edge is the heaviest in the cycle
    int max = graph[cycle[0]][cycle[1]];
    int maxIndex = 0;
    //finding the heaviest edge in the cycle
    for (size_t i = 1; i < cycle.size() - 1; i++) {
        if (graph[cycle[i]][cycle[i+1]] > max) {
            max = graph[cycle[i]][cycle[i+1]];
            maxIndex = i;
        }
    }
    
    //remove the heaviest edge in the cycle
    if (max > weight)
        graph[cycle[maxIndex]][cycle[maxIndex+1]] = INT_MAX;
    else {
        //restore the graph
        graph[i][j] = INT_MAX;
    }
}   

bool Prim::getCycle(Mat& graph, int start, int current, std::vector<int>& nodes, std::map<int, bool>& visited) {
    for (size_t i = start; i < graph.size(); i++) {
        if (graph[start][i] != INT_MAX && visited.find(i) != visited.end()) {
            visited[i] = true;
            if (start == current && nodes.size() != 1) {
                return true;
            }
            
            if (getCycle(graph, start, i, nodes, visited)) {
                nodes.push_back(i);
                return true;
            }
        }
    }
    return false;
}

std::vector<int> Prim::getCycle(Mat& graph, int start) {
    std::vector<int> res;
    std::map<int, bool> visited;
    Prim::getCycle(graph, start, start, res, visited);
    return res;
}