#pragma once
#include "../template.hpp"

struct scc_graph{
    scc_graph(int _n) : n(_n), built(false), g(n), rg(n), id(n,-1), vis(n,false) {
        ord.reserve(n);
    }

    void add_edge(int from, int to) {
        assert(0<=from && from<n);
        assert(0<=to && to<n);
        g[from].emplace_back(to);
        rg[to].emplace_back(from);
    }

    void build() {
        if(built) return;

        for (int i=0; i<n; i++) dfs(i);
        reverse(nall(ord));
        k = 0;
        for(int i=0; i<n; i++){
            if(id[ord[i]] == -1) rdfs(ord[i], k++);
        }
        built = true;
    }

    int operator [] (int k) const {
        assert(0<=k && k<n);
        assert(built);
        return id[k];
    }

    vector<vector<int>> scc() {
        if(!built) build();
        vector<vector<int>> res(k);
        for(int i=0; i<n; i++){
            res[id[i]].emplace_back(i);
        }
        return res;
    }

    private:
    int n,k;
    bool built;
    vector<vector<int>> g,rg;
    vector<int> id,ord;
    vector<bool> vis;

    void dfs(int u) {
        if(vis[u]) return;
        vis[u] = true;
        for(int to : g[u]) dfs(to);
        ord.emplace_back(u);
    }
    void rdfs(int u, int k){
        if(id[u] != -1) return;
        id[u] = k;
        for(int to : rg[u]) rdfs(to,k);
    }
};