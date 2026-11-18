template<typename G>
struct euler_tour{
    private:
    ll n,root,time;

    void dfs(ll now, ll par, ll d){
        in[now] = time++;
        dist[now] = d;
        for(auto next : g[now]){
            if(to(next) == par) continue;
            dfs(to(next),now,d+1);
        }
        out[now] = time;
    }

    static ll to(ll v){
        return v;
    }
    
    template<typename E>
    static ll to(const E& e){
        return e.to;
    }
    
    public:
    G g;
    vector<ll> in,out;
    vector<ll> dist;

    euler_tour(G g, ll r = 0) : n(g.size()), root(r), g(g), in(n), out(n), dist(n) {
        build();
    }
    euler_tour(ll _n, ll r = 0) : n(_n), root(r), g(n), in(n), out(n), dist(n) {}

    void build(){
        time = 0;
        dfs(root,-1,0);
    }

    void add_edge(ll u, ll v){
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
};