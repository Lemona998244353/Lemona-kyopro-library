#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../template.hpp"
#include "../../graph/scc.hpp"

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
        ll n,m; cin >> n >> m;
    scc_graph scc_graph(n);
    rep(i,m){
        ll u,v; cin >> u >> v;
        scc_graph.add_edge(u,v);
    }
    auto scc = scc_graph.scc();
    cout << scc.size() << endl;
    for(auto v : scc){
        ll k = v.size();
        cout << k << ' ';
        rep(i,k) cout << v[i] << " \n"[i==k-1];
    }
    return 0;
}