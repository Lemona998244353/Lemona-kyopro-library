template<typename G>
struct HLD{

    ll n,root;
    G g;
    vector<ll> head,in,out,rev,par,dis,sub;

    HLD(G &g, ll r=0) : n(g.size()), root(r), g(g), head(n), in(n), out(n), rev(n), par(n), dis(n), sub(n) {
        build();
    }

    void build(){
        ll t = 0;
        head[root] = root;
        dfs1(root,root,0);
        dfs2(root,root,t);
    }

    ll dfs1(ll now, ll p, ll d){
        dis[now] = d;
        par[now] = p;
        sub[now] = 1;
        if(!g[now].empty() && g[now][0].to == p){
            swap(g[now][0],g[now].back());
        }
        for(auto &next : g[now]){
            if(next.to == p) continue;
            sub[now] += dfs1(next.to,now,d+1);
            if(sub[g[now][0].to] < sub[next.to]) swap(g[now][0], next);
        }
        return sub[now];
    }

    void dfs2(ll now, ll p, ll &t){
        in[now] = t++;
        rev[in[now]] = now;

        for(auto &next : g[now]){
            if(next.to == p) continue;
            head[next.to] = (g[now][0].to == next.to) ? head[now] : next.to;
            dfs2(next.to,now,t);
        }

        out[now] = t;
    }

    ll lca(ll u, ll v){
        while(1){
            if(in[u] > in[v]) swap(u,v);
            if(head[u] == head[v]) return u;

            v = par[head[v]];
        }
    }

    ll dist(ll u, ll v){
        return dis[u] + dis[v] - 2*dis[lca(u,v)];
    }

    ll la(ll v, ll k){
        assert(0<=k && k<=dis[v]);
        while(1){
            ll u = head[v];
            if(in[v] - k >= in[u]) return rev[in[v] - k];
            k -= in[v] - in[u] + 1;
            v = par[u];
        }
    }

    template<typename T, typename Q, typename F>
    T query(int u, int v, const T &e, const Q &q, const F &f, bool edge=false) {
        T l = e, r = e;
        for( ; ; v = par[head[v]]){
            if(in[u]>in[v]) swap(u,v), swap(l,r);
            if(head[u] == head[v]) break;

            l = f(q(in[head[v]], in[v]+1), l);
        }
        return f(f(q(in[u] + edge, in[v]+1), l), r);
    }
};