#ifndef PRIM_H
#define PRIM_H

#include <vector>
#include <map>

struct node {
    int key;
    node* pi;
    int i;
};

typedef std::vector<std::vector<int>> Mat;

typedef int (*WeightFunc)(Mat&, int, int);

class Prim {
private:
    static bool getCycle(Mat& graph, int start, int current, std::vector<int>& nodes, std::map<int, bool>& visited, int depth);
    static std::vector<int> getCycle(Mat& graph, int start);

public:
    static Mat getMST(Mat& graph, WeightFunc func);

    static void addEdge(Mat& graph, int i, int j, int weight);
};

#endif#pragma once
