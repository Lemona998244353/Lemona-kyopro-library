template<typename G>
struct Euler_tour{
    ll n,root,time;
    struct node{
        ll in,out;
        node() : in(0),out(0) {}
    };
    vector<node> t;
    G graph;
    vector<ll> dist;

    void dfs(ll now, ll par, ll d){
        t[now].in = time++;
        dist[now] = d;
        for(auto to : graph[now]){
            if(to==par) continue;
            dfs(to,now,d+1);
        }
        t[now].out = time;
    }

    void build(){
        dfs(root,-1,0);
    }

    Euler_tour(G g, ll root) : n(g.size()), root(root), graph(g), time(0) {
        dist.assign(n,-1);
        rep(i,n) t.emplace_back(node());
        build();
    }
    node operator[](int k) {return t[k]; }
};