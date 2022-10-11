#include "campanha.hpp"

SAT::SAT(int n){
    this->graph.resize(2*n + 1);
    this->graph_t.resize(2*n + 1);
    this->component.resize(2*n + 1);

    this->visited.assign(2*n + 1, false);

    this->tam = n;
    this->num_components = 0;
}

void SAT::add(int u, bool nu, int v, bool nv){

    // Indexes in the graph for u, v, ¬u and ¬v, respectively

    int pos_u, neg_u, pos_v, neg_v;

    pos_u = (nu ? u + this->tam : u);
    pos_v = (nv ? v + this->tam : v);
    neg_u = (nu ? u : u + this->tam);
    neg_v = (nv ? v : v + this->tam);

    // If a person only makes one choice, then it most be guaranteed that this choice is satisfied.
    // Hence the relation ¬u -> u.

    if(u == 0 && v == 0){
        return;
    }
    else if(u == 0){

        this->graph[neg_v].push_back(pos_v);
        this->graph_t[pos_v].push_back(neg_v);
    }
    else if(v == 0){

        this->graph[neg_u].push_back(pos_u);
        this->graph_t[pos_u].push_back(neg_u);
    }
    else{

        this->graph[neg_u].push_back(pos_v);
        this->graph[neg_v].push_back(pos_u);
        this->graph_t[pos_v].push_back(neg_u);
        this->graph_t[pos_u].push_back(neg_v);
    }
}

void SAT::dfs(int v)
// Runs DFS on the regular graph and stacks the nodes in order of finishing time
{

    this->visited[v] = true;

    for(auto i: this->graph[v]){
        if(!this->visited[i]){
            dfs(i);
        }
    }
    this->finished.push(v);
}

void SAT::dfs_t(int v)
// Runs DFS on the transposed graph and assigns a strolngly connected component to each node
{
    
    this->visited[v] = true;

    for(auto i: graph_t[v]){
        if(!this->visited[i]){
            dfs_t(i);
        }
    }
    this->component[v] = this->num_components;
}

bool SAT::SAT_2()
// Runs the 2-SAT algorithm and decides whether is possible to satisfy all conditions or not
{
    for(int i = 1; i < 2*tam + 1; i++){
        if(!this->visited[i]){
            this->dfs(i);
        }
    }

    this->visited.assign(2*tam + 1, false);

    while(!this->finished.empty()){
        
        int v = this->finished.top();
        this->finished.pop();

        if(!this->visited[v]){
            this->num_components++;
            this->dfs_t(v);
        }
    }

    for(int i = 1; i <= tam; i++){
        if(this->component[i] == this->component[i + tam])
            return false;
    }
    return true;
}