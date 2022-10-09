#include "campanha.hpp"

SAT::SAT(int n){
    this->graph.resize(2*n + 1);
    this->graph_t.resize(2*n + 1);

    this->visited.assign(2*n + 1, false);
    this->component.assign(2*n + 1, -1);

    this->tam = n;
    this->num_components = 0;
}

void SAT::add(int u, bool nu, int v, bool nv){

    if(!u && !v){
        return;
    }
    else if(!u){

        v = (nv ? v + tam : v);
        int neg_v = (nv ? v - tam : v + tam);

        this->graph[neg_v].push_back(v);
        this->graph_t[v].push_back(neg_v);

        return;
    }
    else if(!v){

        u = (nu ? u + tam : u);
        int neg_u = (nu ? u - tam : u + tam);

        this->graph[neg_u].push_back(u);
        this->graph_t[u].push_back(neg_u);

        return;
    }

    u = (nu ? u + tam : u);
    v = (nv ? v + tam : v);
    int neg_u = (nu ? u - tam : u + tam);
    int neg_v = (nv ? v - tam : v + tam);

    this->graph[neg_u].push_back(v);
    this->graph[neg_v].push_back(u);
    this->graph_t[v].push_back(neg_u);
    this->graph_t[u].push_back(neg_v);
}

void SAT::dfs(int v){

    this->visited[v] = true;

    for(auto i: graph[v]){
        if(!this->visited[i]){
            dfs(i);
        }
    }
    this->finished.push(v);
}

void SAT::dfs_t(int v){
    
    this->visited[v] = true;

    for(auto i: graph_t[v]){
        if(!this->visited[i]){
            dfs_t(i);
        }
    }
    this->component[v] = this->num_components;
}

bool SAT::SAT_2(){
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
        if(this->component[i] == this->component[i + tam]) return false;
    }
    return true;
}