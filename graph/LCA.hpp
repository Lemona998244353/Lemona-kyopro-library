template<typename G>
struct LCA{
    ll n,lg,root;
    G g;
    vector<vector<int>> parent;
    vector<int> dist;

    LCA(G g, ll root) : n(g.size()), g(g), root(root), lg(1) {
        while((1<<lg) < n) lg++;
        parent.assign(n,vector<int>(lg,-1));
        dist.assign(n,-1);
        dfs(root,-1,0);

        for(ll k=0; k<lg-1; k++){
            for(ll i=0; i<n; i++){
                if(parent[i][k] < 0){
                    parent[i][k+1] = -1;
                }
                else{
                    parent[i][k+1] = parent[parent[i][k]][k];
                }
            }
        }
    }

    void dfs(ll now, ll par, ll d){
        dist[now] = d;
        parent[now][0] = par;
        for(auto next : g[now]){
            if(next.to==par) continue;
            dfs(next.to,now,d+1);
        }
    }

    int query(int u, int v){
        if(dist[u] < dist[v]) swap(u,v);
        for(ll k=0; k<lg; k++){
            if((dist[u]-dist[v]) >> k & 1){
                u = parent[u][k];
            }
        }

        if(u==v) return u;
        for(ll k=lg-1; k>=0; k--){
            if(parent[u][k] != parent[v][k]){
                u = parent[u][k];
                v = parent[v][k];
            }
        }
        return parent[u][0];
    }
};