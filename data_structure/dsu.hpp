struct dsu{
    private:
        int _n;
        bool track_members;
        vector<int> p_or_s;
        vector<vector<int>> members;

        int _leader(int x){
            if(p_or_s[x]<0) return x;
            else{
                return p_or_s[x]=_leader(p_or_s[x]);
            }
        }

    public:
        explicit dsu(int n, bool track = false) : _n(n), track_members(track), p_or_s(n,-1) {
            if(track_members){
                members.resize(_n);
                for(int i=0; i<_n; i++) members[i].emplace_back(i);
            }
        };

        int leader(int x){
            assert(0<=x&&x<_n);
            return _leader(x);
        }

        int size(int x){
            assert(0<=x&&x<_n);
            return -p_or_s[_leader(x)];
        }

        int merge(int x, int y){
            assert(0<=x&&x<_n);
            assert(0<=y&&y<_n);
            int lx=_leader(x), ly=_leader(y);
            if(lx==ly) return lx;
            if(-p_or_s[lx]<-p_or_s[ly]) swap(lx,ly);
            p_or_s[lx] += p_or_s[ly];
            p_or_s[ly] = lx;

            if(track_members){
                for(auto e : members[ly]) members[lx].emplace_back(e);
                members[ly].clear();
            }
            return lx;
        }

        bool same(int x, int y){
            assert(0<=x&&x<_n);
            assert(0<=y&&y<_n);
            return _leader(x)==_leader(y);
        }

        const vector<int>& component(int x){
            assert(track_members);
            assert(0<=x && x<_n);
            return members[_leader(x)];
        }
};
