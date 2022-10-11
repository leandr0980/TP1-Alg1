#ifndef CAMPANHA_H
#define CAMPANHA_H
 
#include <iostream>
#include <vector>
#include <stack>

class SAT{

    public:

        SAT(int n);

        void add(int u, bool nu, int v, bool nv);

        bool SAT_2();

    private:
        std::vector<std::vector<int>> graph;
        std::vector<std::vector<int>> graph_t;

        void dfs(int v);
        void dfs_t(int v);

        std::stack<int> finished;
        std::vector<bool> visited;

        std::vector<int> component;

        int size;
        int num_components;
};

#endif