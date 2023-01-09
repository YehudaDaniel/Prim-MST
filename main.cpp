#include <iostream>
#include "Prim.h"
#include <limits.h>

using namespace std;

struct edge {
    int to, weight;
};

void print_mat(Mat& mat) {
    printf("    ");

    for (size_t i = 0; i < mat.size(); i++)
        printf("%3ld ", i+1);

    printf("\n    ");
    for (size_t i = 0; i < mat.size(); i++)
        printf("----");
    printf("\n");
    
    for (size_t i = 0; i < mat.size(); i++) {
        printf("%2ld| ", i+1);
        for (size_t j = 0; j < mat.size(); j++) {
            if (mat[i][j] == INT_MAX)
                std::cout << "INF ";
            else
                printf("%3d ", mat[i][j]);
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int weight_func(Mat& mat, int i, int j) {
    return mat[i][j];
}

int main(){
    // Mat graph = {
    //     {INT_MAX, 4, 20, 6, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    //     {4, INT_MAX, 20, 6, 11, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX }
    // };
    std::map<int, std::vector<edge>> adj_list;
    adj_list[1] = { {2, 5}, {3, 11}, {4, 13}, {5, 20} };
    adj_list[2] = { {4, 7}, {5, 20}, {8, 6} };
    adj_list[3] = { {4, 90}, {6, 7}, {7, 1}, {20, 15} };
    adj_list[4] = { {5, 4}, {6, 7}, {11,2} };
    adj_list[5] = { {6, 14}, {11, 30}, {9,14}, {8, 20} };
    adj_list[6] = { {7, 12}, {14, 20}, {10,37}, {20,7} };
    adj_list[7] = { {12, 8}, {14, 15}, {10,1} };
    adj_list[8] = { {9,60} };
    adj_list[9] = { {11,70}, {17,15}, {15, 32}, {16,16} };
    adj_list[10] = { {14, 17}, {15, 82}, {17, 3}, {11,45}, {20,21} };
    adj_list[11] = { {20, 48}, {17,3} };
    adj_list[12] = { {13,13}, {14,14} };
    adj_list[13] = { {14, 41}, {15,74}, {16,91}, {18, 4} };
    adj_list[14] = { {17, 15}, {15, 17} };
    adj_list[15] = { {18, 19}, {16, 57}, {17, 33} };
    adj_list[16] = { {18, 82} };
    adj_list[17] = { {19, 51} };
    adj_list[18] = { {19, 12} };
    adj_list[19] = { };
    adj_list[20] = { };

    Mat graph = std::vector<std::vector<int>>(20, std::vector<int>(20, INT_MAX));
    for (auto &&edges : adj_list) {
        for (auto &&edge : edges.second) {
            graph[edges.first - 1][edge.to - 1] = edge.weight;
        }
    }

    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = i + 1; j < graph.size(); j++) {
            graph[j][i] = graph[i][j];
        }
    }
    std::cout << "Printing graph\n";
    print_mat(graph);

    Mat mst = Prim::getMST(graph, weight_func);
    std::cout << "Printing MST\n";
    print_mat(mst);

    int from = 17, to = 20, weight = 2000001;
    std::cout << "Adding edge from " << from << " to " << to << " with weight " << weight << "\n";
    std::cout << "New MST (unchanged)\n";
    Prim::addEdge(mst, from - 1, to - 1, weight);
    print_mat(mst);

    weight = 1;
    std::cout << "New MST\n";
    Prim::addEdge(mst, from - 1, to - 1, weight);
    print_mat(mst);
}