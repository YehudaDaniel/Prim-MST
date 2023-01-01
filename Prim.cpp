#include "Prim.h"
#include <queue>
#include <map>


Mat Prim::getMST(Mat& graph, WeightFunc func) {
    std::vector<node> nodes;
    std::priority_queue<node*> pq; // weight, from, to
    std::vector<node*> A;

    std::map<node*,bool> doesExist;
    for(int i = 0; i < graph.size(); i++){
        node n;
        n.key = INT_MAX;
        n.pi = nullptr;
        n.i = i;
        nodes.push_back(n);
    }
    nodes[0].key = 0;

    for (auto &&node : nodes){
        pq.push(&node);
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
            if(func(u->i, j) != INT_MAX){ //if there is an edge
                if(nodes[j].key > func(u->i, j) && doesExist[&nodes[j]]){
                    nodes[j].key = func(u->i, j);
                    nodes[j].pi = u;
                }
            }
        }
    }

    //convert A to matrix
    Mat mst;
    for (size_t i = 0; i < graph.size(); i++)
        mst.push_back(std::vector<int>(graph.size(), 0));
    
    for(int k = 0; k < A.size(); k++) {
        int i = A[k]->pi->i;
        int j = A[k]->i;
        mst[i][j] = A[k]->key;
    }

    return mst;
}