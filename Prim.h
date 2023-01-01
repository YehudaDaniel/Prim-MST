#include <vector>

typedef std::vector<std::vector<int>> Mat;

typedef int (*WeightFunc)(int,int);

class Prim{
private:

public:
    static Mat getMST(Mat& graph, WeightFunc func);
};